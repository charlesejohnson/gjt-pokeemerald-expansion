import json,re,csv,math
B=json.load(open('/tmp/base.json'))
B['SPECIES_GENESECT']=[71,120,95,99,120,95]
def key(n): return 'SPECIES_'+re.sub(r'[^A-Z0-9]+','_',n.upper().replace("'","").replace('.','')).strip('_')
def stats(b,L,ev=0,iv=31,nat=None,evs=None):
    hp,at,df,sp,sa,sd=b
    e=evs or [ev]*6
    def f(base,i,isHP=False,nm=1.0):
        v=((2*base+iv+e[i]//4)*L)//100
        return v+L+10 if isHP else int((v+5)*nm)
    nm=nat or {}
    return dict(hp=f(hp,0,True),atk=f(at,1,nm=nm.get('atk',1)),df=f(df,2),spe=f(sp,3,nm=nm.get('spe',1)),spa=f(sa,4,nm=nm.get('spa',1)),spd=f(sd,5))
ITEMOFF={'Life Orb':1.25,'Choice Specs':1.3,'Choice Band':1.3,'Razor Claw':1.05,'Black Glasses':1.1,'Spell Tag':1.1,'Lustrous Orb':1.1,'Lustrous Globe':1.1,'Weakness Policy':1.05,'Mewtwonite Y':1.0}
ITEMDEF={'Leftovers':1.06,'Black Sludge':1.06,'Sitrus Berry':1.05,'Focus Sash':1.08,'Assault Vest':1.25,'Lum Berry':1.03,'Chople Berry':1.04,'Froslassite':1.0}
SETUP={'Swords Dance','Dragon Dance','Calm Mind','Nasty Plot','Trick Room'}
CTRL={'Taunt','Thunder Wave','Will O Wisp','Encore','Toxic','Dark Void','Protect','Aurora Veil','Topsy-Turvy','Trick Room'}
def cr(st,off_m=1.0,def_m=1.0,utility=1.0):
    O=max(st['atk'],st['spa'])*off_m
    Bk=st['hp']*math.sqrt(st['df']*st['spd'])*def_m
    return math.sqrt(O*Bk/1000)*(1+0.1*(st['spe']-200)/100)*utility
# --- enemy teams ---
T={
'Sidney':(60,'N\'Zoth',1.08,[('MALAMAR',58,'Leftovers',['Trick Room','Knock Off','Psycho Cut','Superpower'],1.10,{'spe':0}),('TENTACRUEL',58,'Black Sludge',['Surf','Sludge Bomb','Knock Off','Protect'],1,{}),('OCTILLERY',59,'Choice Specs',['Octazooka','Ice Beam','Flamethrower','Surf'],1,{}),('DHELMISE',59,'Life Orb',['Anchor Shot','Power Whip','Shadow Claw','Protect'],1,{}),('DARKRAI',60,'Life Orb',['Dark Void','Nasty Plot','Dark Pulse','Sludge Bomb'],1,{}),('PALKIA_ORIGIN',60,'Lustrous Globe',['Spacial Rend','Hydro Pump','Thunder','Protect'],1,{})]),
'Phoebe':(60,"Y'shaarj",1.10,[('MESPRIT',58,'Sitrus Berry',['Psychic','Thunderbolt','Dazzling Gleam','Calm Mind'],1,{}),('KLEAVOR',58,'Focus Sash',['Stone Axe','X-Scissor','Close Combat','Swords Dance'],1.05,{}),('SCIZOR',59,'Choice Band',['Bullet Punch','U-turn','Knock Off','Superpower'],1.05,{}),('GENESECT',59,'Life Orb',['U-turn','Iron Head','Ice Beam','Thunder Wave'],1,{}),('HYDREIGON',60,'Life Orb',['Dark Pulse','Draco Meteor','Earth Power','Taunt'],1,{}),('YVELTAL',60,'Black Glasses',['Oblivion Wing','Dark Pulse','Foul Play','Will O Wisp'],1,{})]),
'Glacia':(60,'Yogg-Saron',1.08,[('FROSLASS_MEGA',58,'Froslassite',['Aurora Veil','Blizzard','Shadow Ball','Taunt'],1,{}),('ZOROARK_HISUI',58,'Life Orb',['Shadow Ball','Flamethrower','Hyper Voice','Encore'],1,{}),('MIMIKYU_DISGUISED',59,'Leftovers',['Play Rough','Shadow Sneak','Shadow Claw','Swords Dance'],1.08,{}),('WEAVILE',59,'Razor Claw',['Triple Axel','Knock Off','Ice Shard','Low Kick'],1,{}),('KYUREM',60,'Leftovers',['Ice Beam','Draco Meteor','Earth Power','Toxic'],1,{}),('GUZZLORD',60,'Assault Vest',['Dark Pulse','Draco Meteor','Fire Blast','Gunk Shot'],1,{})]),
'Drake':(60,"Xal'atath",1.12,[('GOTHITELLE',58,'Leftovers',['Psychic','Thunderbolt','Shadow Ball','Taunt'],1.05,{}),('SABLEYE',58,'Sitrus Berry',['Will O Wisp','Knock Off','Foul Play','Taunt'],1,{}),('KARTANA',59,'Life Orb',['Leaf Blade','Sacred Sword','Smart Strike','Night Slash'],1,{}),('TYRANITAR',59,'Chople Berry',['Stone Edge','Crunch','Earthquake','Dragon Dance'],1,{}),('MEWTWO_MEGA_Y',60,'Mewtwonite Y',['Psychic','Shadow Ball','Fire Blast','Aura Sphere'],1,{}),('GIRATINA_ALTERED',60,'Lum Berry',['Shadow Ball','Dragon Claw','Will O Wisp','Shadow Sneak'],1,{})]),
'Dimensius':(60,'Dimensius',1.15,[('DUSKNOIR',58,'Leftovers',['Shadow Sneak','Poltergeist','Will O Wisp','Trick Room'],1,{}),('DEOXYS_NORMAL',58,'Life Orb',['Psycho Boost','Superpower','Ice Beam','Thunder Wave'],1,{}),('DIALGA',59,'Lustrous Orb',['Draco Meteor','Flash Cannon','Thunder','Roar of Time'],1,{}),('LUNALA',59,'Spell Tag',['Moongeist Beam','Psyshock','Moonblast','Calm Mind'],1,{}),('NECROZMA',60,'Weakness Policy',['Photon Geyser','Prismatic Laser','Earthquake','Thunder Wave'],1,{}),('ETERNATUS',60,'Life Orb',['Dynamax Cannon','Sludge Bomb','Flamethrower','Toxic'],1,{})]),
}
def mon_cr(sp,L,item,mv,extra=1.0,nat=None):
    b=B.get('SPECIES_'+sp)
    if not b: return None,None
    st=stats(b,L,nat=None)
    om=ITEMOFF.get(item,1.0)*extra
    dm=ITEMDEF.get(item,1.0)
    ut=1+0.03*len(set(mv)&CTRL)+0.06*len(set(mv)&SETUP)
    return cr(st,om,dm,ut),sum(b)
res={}
for n,(cap,boss,hz,team) in T.items():
    rows=[];tot=0
    for sp,L,item,mv,ex,nt in team:
        c,bst=mon_cr(sp,L,item,mv,ex)
        if c is None: print('missing',sp);continue
        rows.append((sp,bst,round(c,1)));tot+=c
    res[n]=(tot,tot*hz,rows,hz)
    print(n,'raw',round(tot),'w/hazard',round(tot*hz),'avg BST',round(sum(r[1] for r in rows)/len(rows)))
json.dump({k:[v[0],v[1]] for k,v in res.items()},open('/tmp/enemy.json','w'))

# ---------- fix Genesect + player side ----------
B['SPECIES_GENESECT']=[71,120,95,99,120,95]
rows_all=list(csv.DictReader(open('wow-docs/data/pokemon-stages.csv')))
pool=[]
miss=[]
for r in rows_all:
    if r['rarity']=='extremely rare': continue
    k=key(r['name'])
    b=B.get(k)
    if not b: miss.append(r['name']);continue
    pool.append((r['name'],r['stage'],r['rarity'],b))
print('pool',len(pool),'missing',miss[:15])
classes={n:B['SPECIES_'+n] for n in ['DEATHKNIGHT_FROST','DEATHKNIGHT_BLOOD','DEATHKNIGHT_UNHOLY','MAGE_FROST','MAGE_FIRE','MAGE_ARCANE','WARRIOR_ARMS','WARRIOR_FURY','WARRIOR_PROTECTION','SHAMAN_RESTORATION','SHAMAN_ENHANCEMENT','SHAMAN_ELEMENTAL','DRUID_RESTORATION','DRUID_FERAL','DRUID_GUARDIAN','DRUID_BOOMY','MONK_MISTWEAVER','MONK_BREWMASTER','MONK_WINDWALKER','PALADIN_PROTECTION','PALADIN_HOLY','PALADIN_RETRIBUTION','HUNTER_BEAST_MASTERY','HUNTER_MARKSMANSHIP','HUNTER_SURVIVAL']}
print({k:sum(v) for k,v in classes.items()})
def player_cr(b,L,scn):
    off_phys=b[1]>=b[4]
    if scn=='casual':
        st=stats(b,L,iv=22); return cr(st,1.0,1.06,1.0)
    iv=31 if scn=='optimized' else 28
    evs=[252,0,0,0,0,0] ; 
    # invest 252 hp + 252 offense stat, nature +10% on offense
    idx=1 if off_phys else 4
    evs=[252,0,0,0,0,0]; evs[idx]=252
    nat={'atk':1.1} if off_phys else {'spa':1.1}
    st=stats(b,L,iv=iv,evs=evs,nat=nat)
    om=1.25 if scn in('informed','optimized') else 1.0
    ut=1.0 if scn=='informed' else 1.06
    return cr(st,om,1.0,ut)
import statistics
out={}
for L in (58,60):
    for scn in ('casual','informed','optimized'):
        sc=sorted(((player_cr(b,L,scn),n,sum(b)) for n,s,r,b in pool if sum(b)>=470),reverse=True)
        top6=sc[:6]
        cls=sorted(((player_cr(b,L,scn),n,sum(b)) for n,b in classes.items()),reverse=True)
        out[(L,scn)]=(sum(c for c,_,_ in top6),top6,cls[:3])
        print(L,scn,'top6 total',round(sum(c for c,_,_ in top6)),[ (n,round(c)) for c,n,_ in top6],'best class',[(n,round(c)) for c,n,_ in cls[:2]])
# realistic team: 1 class mon + 5 best non-class; 2 class; 3 class
print('--- class lever (L60) ---')
for scn in ('casual','informed','optimized'):
    L=60
    sc=sorted(((player_cr(b,L,scn),n) for n,s,r,b in pool if sum(b)>=470),reverse=True)
    cls=sorted(((player_cr(b,L,scn),n) for n,b in classes.items()),reverse=True)
    for k in (0,1,2,3):
        team=sum(c for c,_ in cls[:k])+sum(c for c,_ in sc[:6-k])
        print(scn,k,'class mons',round(team))
print({k:round(v[1]) for k,v in res.items()})
