from PIL import Image, ImageDraw
BG=(115,197,164)
def new(pal):
    im=Image.new('P',(64,64),0); flat=[]
    for c in [BG]+pal: flat+=list(c)
    flat+=[0,0,0]*(256-len(flat)//3); im.putpalette(flat); return im,ImageDraw.Draw(im)
def outline(im,O):
    px=im.copy().load(); out=im.load()
    for y in range(64):
        for x in range(64):
            if px[x,y]==0:
                for dx,dy in((1,0),(-1,0),(0,1),(0,-1)):
                    nx,ny=x+dx,y+dy
                    if 0<=nx<64 and 0<=ny<64 and px[nx,ny] not in(0,O): out[x,y]=O;break
pal=[(16,8,30),(46,26,86),(80,44,136),(124,72,196),(176,120,250),(26,14,52),(255,90,200),(255,255,255),(216,200,240),(150,130,190),(255,210,235),(36,20,70),(50,110,190),(110,180,240),(70,170,90)]
im,d=new(pal)
OL,B1,B2,B3,B4,DK,GL,WH,HO,HOS,EW,CK,SEA,SEAL,LAND=range(1,16)
def sym(pts,c):
    d.polygon(pts,fill=c); d.polygon([(63-x,y) for x,y in pts],fill=c)
# cloak tatters
sym([(19,28),(9,40),(3,56),(9,52),(10,63),(17,55),(21,63),(26,50)],CK)
# legs / feet
sym([(23,46),(31,46),(31,60),(18,60)],B1)
sym([(23,46),(26,46),(22,60),(18,60)],B2)
sym([(15,59),(30,59),(30,63),(13,63)],B3)
# torso
sym([(24,23),(31,23),(31,50),(24,50),(19,44),(17,30)],B1)
d.polygon([(24,23),(29,23),(26,50),(19,44),(17,30)],fill=B2)
# rift
d.polygon([(32,26),(29,34),(32,42),(35,34)],fill=GL); d.polygon([(32,30),(31,34),(32,38),(33,34)],fill=WH)
# shoulders spikes
sym([(18,26),(10,18),(14,30)],B3)
sym([(18,26),(12,22),(15,29)],B4)
# horns
sym([(27,9),(20,6),(15,0),(23,2),(29,6)],HO)
sym([(20,6),(15,0),(17,4),(22,7)],HOS)
d.polygon([(30,7),(32,0),(34,7)],fill=HO)
# head
sym([(25,7),(31,7),(31,22),(27,22),(23,14)],B2)
d.polygon([(25,7),(29,7),(27,22),(23,14)],fill=B3)
d.polygon([(32,7),(32,22),(37,22),(41,14),(38,7)],fill=B2)
d.polygon([(36,12),(41,14),(37,22),(35,22)],fill=B1)
# eyes (pokemon-style: lash, sclera, pupil, highlight) + two small brow eyes
d.line([(26,13),(30,14)],fill=OL); d.line([(34,14),(38,13)],fill=OL)
d.rectangle([27,15,30,16],fill=EW); d.rectangle([34,15,37,16],fill=EW)
d.rectangle([29,15,29,16],fill=OL); d.rectangle([35,15,35,16],fill=OL)
d.point((28,15),fill=WH); d.point((36,15),fill=WH)
d.point((29,10),fill=GL); d.point((34,10),fill=GL)
d.line([(28,19),(36,19)],fill=OL); d.point((29,20),fill=WH); d.point((35,20),fill=WH)
# arms reaching down toward globe
sym([(22,26),(14,34),(14,46),(20,48),(25,40),(24,32)],B2)
d.polygon([(22,26),(14,34),(14,46),(17,40),(19,32)],fill=B3)
# globe (planet being consumed)
d.ellipse([22,40,42,60],fill=SEA)
d.pieslice([22,40,42,60],200,330,fill=SEAL)
d.polygon([(26,46),(31,44),(33,48),(29,52),(26,50)],fill=LAND)
d.polygon([(34,52),(39,50),(40,56),(35,57)],fill=LAND)
for (x,y) in((30,47),(27,55),(36,45)): d.point((x,y),fill=WH)
# void eating the globe: dark patch + cracks
d.polygon([(32,57),(38,54),(41,58),(36,61)],fill=DK)
d.line([(31,51),(34,55),(33,60)],fill=GL); d.line([(26,57),(30,56)],fill=GL)
d.arc([22,40,42,60],0,360,fill=B1)
# claws over globe + tendrils
sym([(14,45),(22,44),(24,49),(19,52),(14,51)],B4)
sym([(16,51),(18,54),(20,51)],HO)
sym([(24,49),(27,53)],GL)
d.line([(24,49),(27,52)],fill=GL); d.line([(39,49),(36,52)],fill=GL)
# sparkles
for (x,y) in((6,10),(57,10),(5,30),(58,34)): d.point((x,y),fill=B4)
outline(im,OL); im.save('beast3.png')
sh=Image.open('beast3.png').convert('RGB').resize((384,384),Image.NEAREST); sh.save('preview3.png')
