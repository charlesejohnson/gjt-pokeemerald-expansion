#!/usr/bin/env python3
"""Find which trainers are unavoidable ("mandatory") between a map's entrances and exits.

For every pair of endpoints (connection edges and warps) of a map, we search for a walking
route that never steps into a trainer's line of sight. A trainer is MANDATORY for that pair if
blocking their sight tiles (and their own tile) disconnects the pair.

Usage:
  python3 wow-tools/mandatory_trainers.py MAP_ROUTE104         # one map, detailed
  python3 wow-tools/mandatory_trainers.py --all                # writes wow-docs/design/mandatory-trainers.md
Options: --surf (water is walkable), --hm (cut trees/rocks/boulders are passable)

Approximations (see wow-docs/design/mandatory-trainers.md): elevation/bridges ignored, wandering
trainers use all four directions, sight stops at the first blocked tile, NPCs block their tile.
"""
import json, re, os, sys, struct, collections

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)
SURF = '--surf' in sys.argv
HM = '--hm' in sys.argv

# ---- metatile behaviours
MB = {}
txt = open('include/constants/metatile_behaviors.h').read()
body = txt[txt.index('enum {') + 6: txt.index('};')]
i = 0
for line in body.split('\n'):
    m = re.match(r'\s*(MB_\w+)', line)
    if m:
        MB[m.group(1)] = i; i += 1
def mb(n): return MB[n]
WATER = {mb(n) for n in ['MB_POND_WATER', 'MB_SEMI_DEEP_WATER', 'MB_DEEP_WATER', 'MB_WATERFALL', 'MB_OCEAN_WATER',
                          'MB_INTERIOR_DEEP_WATER', 'MB_SOOTOPOLIS_DEEP_WATER', 'MB_NO_SURFACING', 'MB_EASTWARD_CURRENT',
                          'MB_WESTWARD_CURRENT', 'MB_NORTHWARD_CURRENT', 'MB_SOUTHWARD_CURRENT', 'MB_FAST_WATER',
                          'MB_CYCLING_ROAD_WATER'] if n in MB}
IMPASS = {mb(n) for n in MB if n.startswith('MB_IMPASSABLE_')}
JUMP = {mb('MB_JUMP_EAST'): (1, 0), mb('MB_JUMP_WEST'): (-1, 0), mb('MB_JUMP_NORTH'): (0, -1), mb('MB_JUMP_SOUTH'): (0, 1)}
DIRS = {'up': (0, -1), 'down': (0, 1), 'left': (-1, 0), 'right': (1, 0)}

def snake(n):
    return re.sub(r'(?<!^)(?=[A-Z])', '_', n).lower()

_tile_cache = {}
def tileset_attrs(sym, primary):
    key = sym
    if key in _tile_cache: return _tile_cache[key]
    name = sym.replace('gTileset_', '')
    d = f"data/tilesets/{'primary' if primary else 'secondary'}/{snake(name)}"
    attrs = []
    f = d + '/metatile_attributes.bin'
    if os.path.exists(f):
        b = open(f, 'rb').read()
        attrs = [struct.unpack_from('<H', b, k)[0] & 0xFF for k in range(0, len(b) - 1, 2)]
    _tile_cache[key] = attrs
    return attrs

layouts = {l['id']: l for l in json.load(open('data/layouts/layouts.json'))['layouts'] if 'id' in l}
_maps = {}
def load_map(mid):
    if mid in _maps: return _maps[mid]
    d = 'data/maps/' + ''.join(w.capitalize() if False else w for w in [''])  # placeholder
    return None

# map id -> dir via map_groups.json
groups = json.load(open('data/maps/map_groups.json'))
map_dir = {}
for g in groups['group_order']:
    for name in groups[g]:
        j = json.load(open(f'data/maps/{name}/map.json')) if os.path.exists(f'data/maps/{name}/map.json') else None
        if j: map_dir[j['id']] = (name, j)

def grid_for(j):
    lay = layouts[j['layout']]
    w, h = lay['width'], lay['height']
    b = open(lay['blockdata_filepath'], 'rb').read()
    prim = tileset_attrs(lay['primary_tileset'], True)
    sec = tileset_attrs(lay['secondary_tileset'], False)
    beh = {}; blocked = set(); jumps = {}
    for y in range(h):
        for x in range(w):
            v = struct.unpack_from('<H', b, (y * w + x) * 2)[0]
            mt, col = v & 0x3FF, (v >> 10) & 3
            attr = prim[mt] if mt < 512 and mt < len(prim) else (sec[mt - 512] if 0 <= mt - 512 < len(sec) else 0)
            beh[(x, y)] = attr
            if col or attr in IMPASS or (attr in WATER and not SURF):
                blocked.add((x, y))
            if attr in JUMP: jumps[(x, y)] = JUMP[attr]
    return w, h, blocked, jumps

def trainer_ids(name):
    p = f'data/maps/{name}/scripts.inc'
    out = {}
    if not os.path.exists(p): return out
    cur = None
    for line in open(p):
        m = re.match(r'^(\w+)::', line)
        if m: cur = m.group(1)
        m = re.search(r'trainerbattle_\w+\s+(TRAINER_\w+)', line)
        if m and cur and cur not in out: out[cur] = m.group(1)
    return out

FACE = {'FACE_UP': ['up'], 'FACE_DOWN': ['down'], 'FACE_LEFT': ['left'], 'FACE_RIGHT': ['right'],
        'FACE_UP_AND_DOWN': ['up', 'down'], 'FACE_LEFT_AND_RIGHT': ['left', 'right'],
        'FACE_DOWN_AND_UP': ['up', 'down'], 'FACE_RIGHT_AND_LEFT': ['left', 'right'],
        'FACE_UP_AND_LEFT': ['up', 'left'], 'FACE_UP_AND_RIGHT': ['up', 'right'],
        'FACE_DOWN_AND_LEFT': ['down', 'left'], 'FACE_DOWN_AND_RIGHT': ['down', 'right'],
        'FACE_LEFT_AND_UP': ['up', 'left'], 'FACE_RIGHT_AND_UP': ['up', 'right']}
def dirs_for(mt):
    k = mt.replace('MOVEMENT_TYPE_', '')
    if k in FACE: return FACE[k], False
    return ['up', 'down', 'left', 'right'], True   # looks around / wanders / walks a sequence

SOFT_GFX = ('CUTTABLE_TREE', 'BREAKABLE_ROCK', 'PUSHABLE_BOULDER')

def analyse(mid):
    name, j = map_dir[mid]
    w, h, blocked, jumps = grid_for(j)
    tids = trainer_ids(name)
    trainers = []; npc_block = set()
    for o in j.get('object_events', []):
        pos = (o['x'], o['y'])
        if o.get('trainer_type', 'TRAINER_TYPE_NONE') in ('TRAINER_TYPE_NORMAL', 'TRAINER_TYPE_BURIED', 'TRAINER_TYPE_SEE_ALL_DIRECTIONS'):
            ds, wanders = dirs_for(o['movement_type'])
            if o['trainer_type'] == 'TRAINER_TYPE_SEE_ALL_DIRECTIONS': ds, wanders = ['up', 'down', 'left', 'right'], wanders
            r = int(o.get('trainer_sight_or_berry_tree_id', '0') or 0)
            trainers.append(dict(pos=pos, dirs=ds, wander=wanders, radius=r, script=o.get('script', ''),
                                 trainer=tids.get(o.get('script', ''), '?'), flag=o.get('flag', '0'), gfx=o['graphics_id']))
        elif any(s in o['graphics_id'] for s in SOFT_GFX):
            if not HM: npc_block.add(pos)
        elif o.get('flag', '0') not in ('0', '', 'FLAG_0x000') and 'BERRY' not in o['movement_type']:
            pass   # story NPC that appears/disappears with a flag: don't treat as a permanent wall
        else:
            npc_block.add(pos)
    solid = blocked | npc_block | {t['pos'] for t in trainers}
    for t in trainers:
        cone = set()
        for d in t['dirs']:
            dx, dy = DIRS[d]
            for k in range(1, t['radius'] + 1):
                p = (t['pos'][0] + dx * k, t['pos'][1] + dy * k)
                if not (0 <= p[0] < w and 0 <= p[1] < h) or p in blocked or p in npc_block: break
                cone.add(p)
        t['cone'] = cone
    # endpoints
    ends = collections.defaultdict(set)   # label -> tiles
    for k, wp in enumerate(j.get('warp_events', [])):
        p = (wp['x'], wp['y']); ends[f"warp {k}->{wp['dest_map'].replace('MAP_', '')}"].add(p)
    for c in j.get('connections') or []:
        if c['direction'] not in DIRS: continue   # dive/emerge
        dx, dy = DIRS[c['direction']]
        edge = []
        if c['direction'] == 'up': edge = [(x, 0) for x in range(w)]
        elif c['direction'] == 'down': edge = [(x, h - 1) for x in range(w)]
        elif c['direction'] == 'left': edge = [(0, y) for y in range(h)]
        elif c['direction'] == 'right': edge = [(w - 1, y) for y in range(h)]
        for p in edge:
            if p not in solid: ends[f"edge {c['direction']}->{c['map'].replace('MAP_', '')}"].add(p)
    info = dict(name=name, j=j, w=w, h=h, blocked=blocked, jumps=jumps, solid=solid, trainers=trainers, ends=dict(ends))
    # merge endpoints that lead to the same map and can reach each other freely (e.g. two doors of one cave)
    merged = {}
    bydest = collections.defaultdict(list)
    for lab, tiles in ends.items():
        bydest[lab.split('->')[1]].append((lab, tiles))
    for dest, items in bydest.items():
        clusters = []
        for lab, tiles in items:
            for c in clusters:
                if reach(info, [next(iter(c[1]))], set()) & tiles:
                    c[1].update(tiles); c[0].append(lab); break
            else:
                clusters.append([[lab], set(tiles)])
        for n, c in enumerate(clusters):
            kind = 'edge' if c[0][0].startswith('edge') else 'door'
            merged[f"{kind}->{dest}" + (f"#{n + 1}" if len(clusters) > 1 else '')] = c[1]
    info['ends'] = merged
    info['dead'] = {k: dead_end('MAP_' + k.split('->')[1].split('#')[0]) for k in merged
                    if ('MAP_' + k.split('->')[1].split('#')[0]) in map_dir}
    return info

def reach(info, starts, extra_block):
    w, h, solid, jumps = info['w'], info['h'], info['solid'], info['jumps']
    seen = set(); st = [s for s in starts if s not in extra_block and (s not in solid or True)]
    for s in st: seen.add(s)
    while st:
        x, y = st.pop()
        for dx, dy in DIRS.values():
            p = (x + dx, y + dy)
            if not (0 <= p[0] < w and 0 <= p[1] < h): continue
            if p in extra_block: continue
            if p in jumps:
                if jumps[p] != (dx, dy): continue
                q = (p[0] + dx, p[1] + dy)   # hop over the ledge
                if q in seen or q in solid or q in extra_block or not (0 <= q[0] < w and 0 <= q[1] < h): continue
                seen.add(q); st.append(q); continue
            if p in solid or p in seen: continue
            seen.add(p); st.append(p)
    return seen

def pair_results(info):
    res = {}
    labels = sorted(info['ends'])
    for a in labels:
        for b in labels:
            if a >= b or info['dead'].get(a) or info['dead'].get(b): continue
            A, B = info['ends'][a], info['ends'][b]
            base = reach(info, A, set())
            if not (base & B): res[(a, b)] = None; continue   # not connected at all (surf/HM/elevation/etc.)
            mand = []
            for t in info['trainers']:
                blk = t['cone'] | {t['pos']}
                r = reach(info, A, t['cone'])
                if not (r & B) and not (A & B): mand.append(t)
            res[(a, b)] = mand
    return res

def dead_end(mid):
    name, j = map_dir[mid]
    nb = {c['map'] for c in j.get('connections') or []} | {w['dest_map'] for w in j.get('warp_events', [])}
    return len(nb) <= 1

def report(mid):
    info = analyse(mid)
    res = pair_results(info)
    print(f"{mid}: {len(info['trainers'])} trainer(s)")
    for t in info['trainers']:
        print(f"  {t['trainer']:<28} at {t['pos']} facing {'/'.join(t['dirs'])}{'*' if t['wander'] else ''} sight {t['radius']}")
    through = collections.defaultdict(list)
    for (a, b), m in res.items():
        if m is None: print(f"  {a} <-> {b}: not connected (needs surf/HM/other)"); continue
        names = [t['trainer'] for t in m]
        print(f"  {a} <-> {b}: mandatory {names if names else 'none'}")
    return info, res

def all_report():
    lines = ['# Mandatory trainers by map', '',
             'Generated by `wow-tools/mandatory_trainers.py --all`. A trainer is **mandatory** if every walking route between '
             'some pair of entrances/exits of the map crosses their line of sight. `*` = wanders or looks around (all four '
             'directions assumed). Dead-end maps (one neighbor) are skipped. Ledges are one-way, water and NPC tiles block, '
             'cut trees/rocks/boulders block unless `--hm`. Elevation and bridges are ignored, so verify bridge maps by hand.', '']
    total = mand_total = 0
    for mid in sorted(map_dir):
        name, j = map_dir[mid]
        if not any(o.get('trainer_type', 'TRAINER_TYPE_NONE') != 'TRAINER_TYPE_NONE' and
                   o['graphics_id'] != 'x' and o.get('trainer_type') in ('TRAINER_TYPE_NORMAL', 'TRAINER_TYPE_BURIED', 'TRAINER_TYPE_SEE_ALL_DIRECTIONS')
                   for o in j.get('object_events', [])):
            continue
        if dead_end(mid): continue
        try:
            info = analyse(mid); res = pair_results(info)
        except Exception as e:
            lines.append(f'## {mid}\n- error: {e}\n'); continue
        mand = {}
        for (a, b), m in res.items():
            for t in m or []:
                mand.setdefault(t['trainer'], []).append(f'{a} <-> {b}')
        lines.append(f"## {mid}")
        for t in info['trainers']:
            tag = 'MANDATORY' if t['trainer'] in mand else 'optional'
            lines.append(f"- `{t['trainer']}` ({t['gfx'].replace('OBJ_EVENT_GFX_', '')}) at {t['pos']} facing {'/'.join(t['dirs'])}{'*' if t['wander'] else ''}, sight {t['radius']}: **{tag}**"
                         + (f" ({len(set(mand[t['trainer']]))} route pair(s))" if t['trainer'] in mand else ''))
            total += 1; mand_total += tag == 'MANDATORY'
        lines.append('')
    lines.insert(2, f'**{mand_total} mandatory / {total} trainers** on scanned maps.\n')
    open('wow-docs/design/mandatory-trainers.md', 'w').write('\n'.join(lines))
    print(f'wrote wow-docs/design/mandatory-trainers.md: {mand_total}/{total} mandatory')

if __name__ == '__main__':
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    if '--all' in sys.argv: all_report()
    elif args: report(args[0])
    else: print(__doc__)
