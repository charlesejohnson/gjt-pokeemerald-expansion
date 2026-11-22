import re,glob,csv,json
txt=""
for f in glob.glob('src/data/pokemon/species_info/*.h')+['src/data/pokemon/species_info.h']:
    txt+=open(f).read()
base={}
for m in re.finditer(r"\[(SPECIES_\w+)\]\s*=\s*\{(.*?)\n    \},",txt,re.S):
    b=m.group(2)
    g=lambda k:(re.search(r"\.%s\s*=\s*(\d+)"%k,b) or [0,0])[1]
    st=[int(g(k)) for k in("baseHP","baseAttack","baseDefense","baseSpeed","baseSpAttack","baseSpDefense")]
    if st[0]: base[m.group(1)]=st
json.dump(base,open('/tmp/base.json','w'))
print(len(base))
