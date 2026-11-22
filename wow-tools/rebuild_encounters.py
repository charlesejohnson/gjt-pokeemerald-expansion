#!/usr/bin/env python3
"""Rebuild Hoenn wild encounter tables from wow-docs/data/pokemon-stages.csv.

Run from the repo root:  python3 wow-tools/rebuild_encounters.py [--dry]
Reads src/data/wild_encounters.json, rewrites the Emerald land/water/fishing tables for the maps in
THEMES below, adds "_Night" variants (time-of-day encounters, Day table is the fallback), and
writes the JSON back. Deterministic (fixed seed). Species rarity -> slot: common = top slots,
uncommon = middle, rare = 4%/4%, extremely rare = the single 1% slot (only where placed by hand).
"""
import json, csv, re, glob, random, sys, collections, os
os.chdir(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
random.seed(1121)
DRY = '--dry' in sys.argv

# ---- species name -> constant (first definition wins = base form)
names = {}
for f in sorted(glob.glob('src/data/pokemon/species_info/gen_*_families.h')):
    for m in re.finditer(r'\[(SPECIES_\w+)\] =\s*\{(.*?)\n    \},', open(f).read(), re.S):
        n = re.search(r'speciesName = _\("([^"]*)"', m.group(2))
        if n and n.group(1) not in names: names[n.group(1)] = m.group(1)
SPECIES_H = open('include/constants/species.h').read()
def const_for(name):
    c = 'SPECIES_' + re.sub(r'[^A-Z0-9]+', '_', name.upper()).strip('_')
    if re.search(r'\b%s\b' % c, SPECIES_H): return c
    return names.get(name)
rows = []
for r in csv.DictReader(open('wow-docs/data/pokemon-stages.csv')):
    nm = r['name']
    if not const_for(nm):
        print('MISSING species', nm); continue
    rows.append(dict(sp=const_for(nm), name=nm, ty_list=r['types'].split('/'), types=set(r['types'].split('/')), stage=r['stage'], rar=r['rarity']))
RANK = {'common': 0, 'uncommon': 1, 'rare': 2, 'extremely rare': 3}

D, N = 'day', 'night'
def T(s): return set(s.split())
# map -> (stage, day types, night types, keep existing day species (0 = leave Day table as is), rebuild Day?)
E, M, L = 'early', 'mid', 'late'
THEMES = {
 # early routes: Day stays as Charlie edited it; only a Night table is added
 'ROUTE101': (E, T('Bug Normal'), T('Dark Bug Poison Normal'), 99),
 'ROUTE102': (E, T('Grass Normal'), T('Dark Poison Psychic Fairy Normal'), 99),
 'ROUTE103': (E, T('Electric Normal'), T('Dark Electric Ghost Normal'), 99),
 'ROUTE104': (E, T('Water Flying Grass'), T('Dark Water Flying Poison'), 99),
 'ROUTE116': (E, T('Fairy Normal Psychic'), T('Ghost Psychic Fairy Dark'), 99),
 'ROUTE117': (E, T('Grass Fairy Bug'), T('Ghost Poison Grass Fairy'), 99),
 'PETALBURG_WOODS': (E, T('Grass Bug'), T('Ghost Dark Bug Poison Psychic'), 99),
 'RUSTURF_TUNNEL': (E, T('Ice Ground'), T('Dark Ghost Ice'), 99),
 'GRANITE_CAVE_1F': (E, T('Rock Ground Fighting'), T('Dark Ghost Rock Steel'), 99),
 'GRANITE_CAVE_B1F': (E, T('Rock Steel'), T('Dark Ghost Steel'), 99),
 'GRANITE_CAVE_B2F': (E, T('Rock Dark'), T('Dark Ghost Steel'), 99),
 'GRANITE_CAVE_STEVENS_ROOM': (E, T('Steel Rock'), T('Steel Psychic Ghost Dark'), 99),
 # mid game: Day rebuilt keeping a few of the existing commons
 'ROUTE110': (M, T('Electric Fire Normal Bug'), T('Dark Ghost Poison Fire'), 3),
 'ROUTE111': (M, T('Ground Rock Fire Normal'), T('Dark Ghost Psychic Poison'), 3),
 'ROUTE112': (M, T('Fire Fighting Ground Rock Electric'), T('Dark Fire Poison Ghost Ice'), 3),
 'ROUTE113': (M, T('Fire Flying Normal Ground'), T('Dark Ghost Fire Steel Ice'), 3),
 'ROUTE114': (M, T('Grass Bug Normal Flying Fairy'), T('Dark Ghost Poison Psychic Ice'), 3),
 'ROUTE115': (M, T('Flying Normal Fairy Psychic'), T('Psychic Dark Ghost Fairy'), 3),
 'ROUTE118': (M, T('Electric Normal Grass'), T('Dark Poison Ghost Electric'), 3),
 'ROUTE119': (M, T('Grass Bug Poison Flying Electric Fairy'), T('Ghost Dark Bug Poison'), 3),
 'ROUTE120': (M, T('Grass Normal Poison Bug Fairy'), T('Dark Ghost Poison Psychic'), 3),
 'ROUTE121': (M, T('Normal Flying Grass Electric'), T('Ghost Dark Poison'), 3),
 'ROUTE123': (M, T('Normal Flying Grass Electric'), T('Ghost Dark Poison'), 3),
 'JAGGED_PASS': (M, T('Fire Fighting Rock'), T('Dark Ghost Fire Ice'), 3),
 'FIERY_PATH': (M, T('Fire Ground Rock Poison'), T('Dark Fire Ghost Poison'), 3),
 'MT_PYRE_1F': (M, T('Ghost Flying Fairy'), T('Ghost Dark Poison'), 1),
 'MT_PYRE_2F': (M, T('Ghost Flying Fairy'), T('Ghost Dark Poison'), 1),
 'MT_PYRE_3F': (M, T('Ghost Flying Fairy'), T('Ghost Dark Poison'), 1),
 'MT_PYRE_4F': (M, T('Ghost Flying Fairy'), T('Ghost Dark Poison'), 2),
 'MT_PYRE_5F': (M, T('Ghost Flying Fairy'), T('Ghost Dark Poison'), 2),
 'MT_PYRE_6F': (M, T('Ghost Flying Fairy'), T('Ghost Dark Poison'), 2),
 'MT_PYRE_EXTERIOR': (M, T('Ghost Flying Fairy'), T('Ghost Dark Poison'), 2),
 'MT_PYRE_SUMMIT': (L, T('Ghost Psychic Fairy'), T('Ghost Dark Poison'), 2),
 'NEW_MAUVILLE_ENTRANCE': (M, T('Electric Steel'), T('Electric Steel Ghost'), 2),
 'NEW_MAUVILLE_INSIDE': (M, T('Electric Steel'), T('Electric Steel Ghost'), 2),
 'MIRAGE_TOWER_1F': (M, T('Ground Rock Psychic'), T('Ghost Dark Psychic'), 2),
 'MIRAGE_TOWER_2F': (M, T('Ground Rock Psychic'), T('Ghost Dark Psychic'), 2),
 'MIRAGE_TOWER_3F': (M, T('Ground Rock Psychic'), T('Ghost Dark Psychic'), 2),
 'MIRAGE_TOWER_4F': (M, T('Ground Rock Psychic'), T('Ghost Dark Psychic'), 2),
 'MAGMA_HIDEOUT_1F': (M, T('Fire Rock Ground'), T('Dark Fire Ghost'), 2),
 'MAGMA_HIDEOUT_2F_1R': (M, T('Fire Rock Ground'), T('Dark Fire Ghost'), 2),
 'MAGMA_HIDEOUT_2F_2R': (M, T('Fire Rock Ground'), T('Dark Fire Ghost'), 2),
 'MAGMA_HIDEOUT_2F_3R': (M, T('Fire Rock Ground'), T('Dark Fire Ghost'), 2),
 'MAGMA_HIDEOUT_3F_1R': (M, T('Fire Rock Ground'), T('Dark Fire Ghost'), 2),
 'MAGMA_HIDEOUT_3F_2R': (M, T('Fire Rock Ground'), T('Dark Fire Ghost'), 2),
 'MAGMA_HIDEOUT_3F_3R': (M, T('Fire Rock Ground'), T('Dark Fire Ghost'), 2),
 'MAGMA_HIDEOUT_4F': (M, T('Fire Rock Ground'), T('Dark Fire Ghost'), 2),
 'METEOR_FALLS_1F_1R': (M, T('Rock Dragon Flying Psychic'), T('Dark Dragon Ghost Psychic'), 2),
 'SAFARI_ZONE_SOUTH': (M, T('Normal Grass Psychic Bug'), T('Psychic Ghost Dark Poison'), 2),
 'SAFARI_ZONE_SOUTHWEST': (M, T('Normal Grass Psychic Bug'), T('Psychic Ghost Dark Poison'), 2),
 'SAFARI_ZONE_NORTH': (M, T('Normal Grass Psychic Bug Ground'), T('Psychic Ghost Dark Poison'), 2),
 'SAFARI_ZONE_NORTHWEST': (M, T('Normal Grass Bug Ground'), T('Psychic Ghost Dark Poison'), 2),
 # late game
 'METEOR_FALLS_1F_2R': (L, T('Rock Dragon Flying Psychic'), T('Dark Dragon Ghost Psychic'), 2),
 'METEOR_FALLS_B1F_1R': (L, T('Rock Dragon Flying Psychic'), T('Dark Dragon Ghost Psychic'), 2),
 'METEOR_FALLS_B1F_2R': (L, T('Rock Dragon Flying Psychic'), T('Dark Dragon Ghost Psychic'), 2),
 'METEOR_FALLS_STEVENS_CAVE': (L, T('Rock Dragon Flying Steel'), T('Dark Dragon Ghost Steel'), 2),
 'SAFARI_ZONE_SOUTHEAST': (L, T('Normal Grass Bug Psychic'), T('Psychic Ghost Dark Poison'), 2),
 'SAFARI_ZONE_NORTHEAST': (L, T('Normal Grass Bug Ground Fighting'), T('Psychic Ghost Dark Poison'), 2),
 'VICTORY_ROAD_1F': (L, T('Fighting Rock Ground Steel'), T('Dark Ghost Poison Psychic'), 2),
 'VICTORY_ROAD_B1F': (L, T('Fighting Rock Ground Steel'), T('Dark Ghost Poison Psychic'), 2),
 'VICTORY_ROAD_B2F': (L, T('Fighting Rock Ground Steel'), T('Dark Ghost Poison Psychic'), 2),
 'SHOAL_CAVE_LOW_TIDE_ENTRANCE_ROOM': (M, T('Water Ice Poison Rock'), T('Dark Ghost Ice Psychic'), 2),
 'SHOAL_CAVE_LOW_TIDE_INNER_ROOM': (M, T('Water Ice Poison Rock'), T('Dark Ghost Ice Psychic'), 2),
 'SHOAL_CAVE_LOW_TIDE_STAIRS_ROOM': (M, T('Water Ice Poison Rock'), T('Dark Ghost Ice Psychic'), 2),
 'SHOAL_CAVE_LOW_TIDE_LOWER_ROOM': (M, T('Water Ice Poison Rock'), T('Dark Ghost Ice Psychic'), 2),
 'SHOAL_CAVE_LOW_TIDE_ICE_ROOM': (M, T('Water Ice Poison Rock'), T('Dark Ghost Ice Psychic'), 2),
 'SKY_PILLAR_1F': (L, T('Flying Psychic Dragon Steel'), T('Ghost Dark Psychic'), 2),
 'SKY_PILLAR_3F': (L, T('Flying Psychic Dragon Steel'), T('Ghost Dark Psychic'), 2),
 'SKY_PILLAR_5F': (L, T('Flying Psychic Dragon Steel'), T('Ghost Dark Psychic'), 2),
 'DESERT_UNDERPASS': (L, T('Ground Normal Rock'), T('Dark Ghost Psychic'), 2),
}
# hand-placed extremely rare species (map, time, species name)
SPECIAL = {
 ('PETALBURG_WOODS', N): 'Mew', ('METEOR_FALLS_B1F_2R', N): 'Jirachi', ('ROUTE111', D): 'Landorus',
 ('ROUTE118', N): 'Thundurus', ('ROUTE113', D): 'Tornadus', ('FIERY_PATH', N): 'Chi-Yu',
}
# sea routes: water/fishing refresh (stage by position along the coast)
SEA = {m: (M if int(m[5:]) <= 124 else L) for m in [f'ROUTE{n}' for n in range(105, 135)]
       if m not in ('ROUTE110', 'ROUTE111', 'ROUTE112', 'ROUTE113', 'ROUTE114', 'ROUTE115', 'ROUTE116', 'ROUTE117',
                    'ROUTE118', 'ROUTE119', 'ROUTE120', 'ROUTE121', 'ROUTE123', 'ROUTE101', 'ROUTE102', 'ROUTE103', 'ROUTE104')}
SEA.update({'ROUTE104': E, 'ROUTE105': E, 'ROUTE106': E, 'ROUTE107': E, 'ROUTE108': M, 'ROUTE109': M})
for m in ('ROUTE110', 'ROUTE118', 'ROUTE119', 'ROUTE120', 'ROUTE121', 'ROUTE123'): SEA[m] = M
SEA.update({'LILYCOVE_CITY': L, 'MOSSDEEP_CITY': L, 'PACIFIDLOG_TOWN': L, 'EVER_GRANDE_CITY': L})

USE = collections.Counter()
ALL_TYPES = set('Normal Fire Water Electric Grass Ice Fighting Poison Ground Flying Psychic Bug Rock Ghost Dragon Dark Steel Fairy'.split())
CUR = ['']
LAND_RATES = [20, 20, 10, 10, 10, 10, 5, 5, 4, 4, 1, 1]
LAND_CLASS = [0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2]          # rarity class wanted per slot
WATER_CLASS = [0, 0, 1, 2, 2]
FISH_CLASS = [0, 0, 0, 1, 1, 1, 1, 2, 2, 2]

def pool_for(stage, types, kind):
    allowed = {E: {'early'}, M: {'mid', 'early'}, L: {'late', 'mid'}}[stage]
    out = []
    for r in rows:
        if r['stage'] not in allowed or r['rar'] == 'extremely rare': continue
        ty = r['types']; prim = r['ty_list'][0]
        if not (ty & types): continue
        if kind == 'water' and 'Water' not in ty: continue
        if kind == 'land' and prim == 'Water': continue
        if r['sp'] == 'SPECIES_UNOWN' and not CUR[0].startswith(('MIRAGE_TOWER', 'ROUTE111')): continue
        # the earlier stage is a filler: bump its rarity one step so the newer stage dominates
        rar = RANK[r['rar']] + (1 if r['stage'] != {E: 'early', M: 'mid', L: 'late'}[stage] else 0)
        if prim not in types: rar += 1          # secondary-type match only: a bit rarer
        out.append((r, min(rar, 2)))
    return out

def modal_levels(mons):
    c = collections.Counter((m['min_level'], m['max_level']) for m in mons)
    return c.most_common(1)[0][0]

def fill(n, classes, stage, types, existing, keep, kind, special=None):
    """Pick n species for slots; returns species constants."""
    pool = pool_for(stage, types, kind)
    random.shuffle(pool)
    pool.sort(key=lambda t: USE[t[0]['sp']])   # spread species across maps
    slots = [None] * n
    used = set()
    ex = []
    for m in existing:
        if m['species'] not in used and (kind != 'land' or True):
            used.add(m['species']); ex.append(m['species'])
    # keep the first `keep` existing species in the common slots
    for i, sp in enumerate(ex[:keep]):
        if i < n: slots[i * 2 if i * 2 < n else i] = sp
    cands_left = list(ex[keep:])
    if special:
        slots[n - 1] = special; used.add(special)
    for i in range(n):
        if slots[i] is not None: continue
        want = classes[i]
        pick = None
        for d in (0, 1, -1, 2, -2):
            for r, rar in pool:
                if r['sp'] in used: continue
                if rar == want + d if 0 <= want + d <= 2 else False:
                    pick = r['sp']; break
            if pick: break
        if not pick:
            loose = [r for r, rar in pool_for(stage, ALL_TYPES, kind) if r['sp'] not in used]
            loose.sort(key=lambda r: (USE[r['sp']], random.random()))
            if loose: pick = loose[0]['sp']
        if not pick and cands_left:
            pick = cands_left.pop(0)
        if not pick: pick = ex[0] if ex else None
        slots[i] = pick; used.add(pick); USE[pick] += 1
    return slots

d = json.load(open('src/data/wild_encounters.json'))
enc = d['wild_encounter_groups'][0]['encounters']
out = []; report = []
for x in enc:
    label = x['base_label']; mp = x['map'].replace('MAP_', '')
    if 'FireRed' in label or 'LeafGreen' in label: out.append(x); continue
    th = THEMES.get(mp)
    CUR[0] = mp
    sea = SEA.get(mp)
    ent = json.loads(json.dumps(x))
    changed = False
    if th and 'land_mons' in ent:
        stage, dt, nt, keep = th
        mons = ent['land_mons']['mons']
        lv = modal_levels(mons)
        if keep < 99:      # rebuild day
            sp = fill(12, LAND_CLASS, stage, dt, mons, keep, 'land')
            sd = SPECIAL.get((mp, D))
            if sd: sp[11] = const_for(sd)
            ent['land_mons']['mons'] = [{'min_level': lv[0], 'max_level': lv[1], 'species': s} for s in sp]
            changed = True
        night = json.loads(json.dumps(ent)); night['base_label'] = label + '_Night'
        dayspecies = [m['species'] for m in ent['land_mons']['mons']]
        nk = 1
        nsp = fill(12, LAND_CLASS, stage, nt, [{'species': s} for s in dayspecies[:1]], nk, 'land')
        sn = SPECIAL.get((mp, N))
        if sn: nsp[11] = const_for(sn)
        night['land_mons'] = {'encounter_rate': ent['land_mons']['encounter_rate'] if mp not in ('ROUTE101',) else ent['land_mons']['encounter_rate'],
                              'mons': [{'min_level': lv[0], 'max_level': lv[1], 'species': s} for s in nsp]}
        for k in ('water_mons', 'fishing_mons', 'rock_smash_mons'): night.pop(k, None)
        report.append((mp, 'day', [s.replace('SPECIES_', '') for s in dayspecies]))
        report.append((mp, 'night', [s.replace('SPECIES_', '') for s in nsp]))
        out.append(ent); out.append(night); continue
    if sea and ('water_mons' in ent or 'fishing_mons' in ent):
        for k, cls in (('water_mons', WATER_CLASS), ('fishing_mons', FISH_CLASS)):
            if k not in ent: continue
            mons = ent[k]['mons']; n = len(mons)
            sp = fill(n, cls, sea, T('Water'), mons, 1 if k == 'water_mons' else 2, 'water')
            # keep the last (rarest) slot of the original (Sharpedo, Wailmer, ...)
            sp[-1] = mons[-1]['species']
            ent[k]['mons'] = [{'min_level': mons[i]['min_level'], 'max_level': mons[i]['max_level'], 'species': sp[i]} for i in range(n)]
        report.append((mp, 'sea', [m['species'].replace('SPECIES_', '') for m in ent.get('fishing_mons', ent.get('water_mons'))['mons']]))
    out.append(ent)
d['wild_encounter_groups'][0]['encounters'] = out
for r in report: print(r[0], r[1], ','.join(r[2]))
if not DRY:
    json.dump(d, open('src/data/wild_encounters.json', 'w'), indent=2, ensure_ascii=False)
    open('src/data/wild_encounters.json', 'a').write('\n')
