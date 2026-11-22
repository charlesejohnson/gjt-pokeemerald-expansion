from PIL import Image, ImageDraw
BG=(115,197,164)
def new(pal):
    im=Image.new('P',(64,64),0)
    flat=[]
    for c in [BG]+pal: flat+=list(c)
    flat+=[0,0,0]*(256-len(flat)//3)
    im.putpalette(flat); return im,ImageDraw.Draw(im)
def outline(im,O):
    px=im.copy().load(); out=im.load()
    for y in range(64):
        for x in range(64):
            if px[x,y]==0:
                for dx,dy in((1,0),(-1,0),(0,1),(0,-1)):
                    nx,ny=x+dx,y+dy
                    if 0<=nx<64 and 0<=ny<64 and px[nx,ny] not in(0,O): out[x,y]=O;break
# ---------- sorceress ----------
pal=[(30,18,56),(240,210,190),(200,152,150),(255,236,220),(196,184,236),(132,116,196),(116,72,176),(70,40,120),(156,112,216),(236,192,72),(52,30,96),(96,48,160),(255,255,255),(60,230,255),(24,24,64)]
im,d=new(pal)
OL,SK,SKS,SKH,HR,HRS,RB,RBS,RBH,GD,CP,EY,WH,OR,ORD=range(1,16)
# cape behind
d.polygon([(30,24),(24,26),(13,38),(8,54),(13,51),(17,61),(23,50),(29,40)],fill=CP)
d.polygon([(24,26),(13,38),(10,50),(16,40),(22,32)],fill=RBS)
# back hair
d.polygon([(28,9),(24,14),(21,25),(17,36),(22,34),(25,27),(28,19),(29,13)],fill=HR)
d.polygon([(24,14),(21,25),(17,36),(20,31),(23,22)],fill=HRS)
# robe skirt
d.polygon([(29,40),(38,40),(46,58),(40,63),(24,63),(21,58)],fill=RB)
d.polygon([(29,40),(33,40),(30,63),(24,63),(21,58)],fill=RBS)
d.polygon([(36,42),(38,40),(46,58),(42,60)],fill=RBH)
d.line([(31,44),(30,62)],fill=RBS); d.line([(36,46),(38,62)],fill=RBS)
# hem gold
d.line([(22,60),(40,62)],fill=GD)
# boots
d.polygon([(25,60),(31,60),(31,63),(24,63)],fill=ORD); d.polygon([(34,61),(41,61),(42,63),(34,63)],fill=ORD)
# torso
d.polygon([(29,23),(37,23),(39,32),(37,41),(30,41),(28,32)],fill=RB)
d.polygon([(29,23),(32,23),(31,41),(30,41),(28,32)],fill=RBH)
d.polygon([(35,28),(39,32),(37,41),(34,41)],fill=RBS)
d.line([(29,37),(38,38)],fill=GD); d.line([(29,38),(38,39)],fill=GD)
# collar
d.polygon([(29,22),(37,22),(35,26),(31,27)],fill=GD)
# lowered arm
d.polygon([(29,26),(26,30),(25,40),(29,41),(31,33)],fill=RBS)
d.ellipse([24,40,29,44],fill=SK)
# raised arm
d.polygon([(36,24),(46,24),(52,20),(55,23),(47,31),(37,30)],fill=RB)
d.polygon([(36,24),(46,24),(52,20),(50,22),(45,26),(37,27)],fill=RBH)
d.polygon([(47,31),(55,23),(55,26),(49,33)],fill=RBS)
d.line([(46,27),(48,29)],fill=GD)
d.ellipse([53,17,58,23],fill=SK); d.point((55,19),fill=SKH)
# orb
d.ellipse([54,6,62,14],fill=ORD); d.ellipse([56,8,60,12],fill=OR); d.point((57,9),fill=WH)
d.point((58,4),fill=OR); d.point((52,10),fill=OR); d.point((62,16),fill=OR)
# neck
d.rectangle([30,19,34,23],fill=SKS)
# head
d.polygon([(27,8),(37,7),(39,12),(38,17),(36,21),(32,20),(29,19),(27,14)],fill=SK)
d.polygon([(27,8),(30,8),(29,19),(27,14)],fill=SKH)
d.polygon([(36,21),(38,17),(39,12),(37,16),(35,19)],fill=SKS)
# ear (pointed, swept back)
d.polygon([(27,12),(19,8),(26,16)],fill=SK); d.polygon([(26,12),(21,9),(25,14)],fill=SKH); d.point((25,14),fill=SKS)
# hair front
d.polygon([(26,10),(28,5),(34,3),(40,6),(41,12),(38,8),(34,7),(31,9),(29,13),(28,17)],fill=HR)
d.polygon([(30,5),(34,3),(36,4),(32,6)],fill=WH)
d.polygon([(38,8),(41,12),(40,16),(38,11)],fill=HRS)
# circlet
d.line([(28,9),(38,8)],fill=GD); d.point((33,8),fill=OR)
# eyes: lash line, white, iris, pupil; brows; nose; lips
d.line([(31,13),(34,13)],fill=OL); d.point((30,12),fill=OL); d.line([(36,13),(38,13)],fill=OL)
d.point((31,14),fill=WH); d.point((32,14),fill=EY); d.point((33,14),fill=OL); d.point((34,14),fill=SKS)
d.point((36,14),fill=EY); d.point((37,14),fill=OL); d.point((38,14),fill=WH)
d.line([(31,12),(33,11)],fill=RBS); d.line([(36,11),(38,11)],fill=RBS)
d.point((32,15),fill=SKS); d.point((37,15),fill=SKS)
d.point((38,16),fill=SKS); d.point((37,17),fill=SKS)
d.line([(35,19),(37,19)],fill=SKS)
outline(im,OL); im.save('sorc2.png')

# ---------- void colossus ----------
pal=[(16,8,30),(46,26,86),(80,44,136),(124,72,196),(176,120,250),(26,14,52),(255,90,200),(255,230,255),(216,200,240),(150,130,190),(255,210,235),(60,10,80),(36,20,70),(96,60,170),(120,200,255)]
im,d=new(pal)
OL,B1,B2,B3,B4,DK,GL,WH,HO,HOS,EW,EP,CK,CKH,SH=range(1,16)
# cloak tatters
d.polygon([(19,28),(9,40),(4,58),(10,52),(12,63),(18,55),(22,63),(27,52)],fill=CK)
d.polygon([(19,28),(9,40),(6,52),(12,42),(18,36)],fill=CKH)
d.polygon([(43,36),(54,46),(59,62),(51,56),(46,63),(41,54)],fill=CK)
# legs
d.polygon([(26,48),(36,48),(38,63),(31,63),(29,56)],fill=B1)
d.polygon([(26,48),(30,48),(29,56),(26,63),(22,63)],fill=DK)
d.polygon([(22,60),(31,60),(31,63),(21,63)],fill=B3)
# torso
d.polygon([(24,23),(40,23),(46,30),(44,46),(36,52),(26,52),(20,44),(18,30)],fill=B1)
d.polygon([(24,23),(30,23),(26,52),(20,44),(18,30)],fill=B2)
d.polygon([(37,30),(46,30),(44,46),(36,52)],fill=DK)
d.polygon([(32,27),(29,36),(32,45),(35,36)],fill=GL); d.polygon([(32,31),(31,36),(32,41),(33,36)],fill=WH)
# lowered arm
d.polygon([(20,28),(14,36),(11,48),(16,51),(20,41),(24,34)],fill=B2)
d.polygon([(20,28),(14,36),(11,48),(13,44),(17,34)],fill=B3)
d.polygon([(10,48),(16,50),(15,56),(12,55),(9,54)],fill=B4)
# raised arm
d.polygon([(40,24),(49,22),(55,15),(59,17),(52,29),(44,32)],fill=B2)
d.polygon([(40,24),(49,22),(55,15),(52,19),(46,26)],fill=B3)
d.polygon([(53,10),(60,12),(60,18),(55,17)],fill=B4)
# void swirl above hand
for (x,y) in((55,6),(58,4),(61,8),(52,9),(57,1),(50,4)): d.point((x,y),fill=SH)
d.ellipse([54,2,60,8],fill=DK); d.ellipse([56,4,58,6],fill=GL)
# horns
d.polygon([(26,9),(19,6),(14,0),(22,2),(28,6)],fill=HO); d.polygon([(26,9),(19,6),(16,3),(22,6)],fill=HOS)
d.polygon([(37,9),(44,6),(49,0),(41,2),(35,6)],fill=HO); d.polygon([(44,6),(49,0),(47,6),(42,8)],fill=HOS)
d.polygon([(30,7),(31,0),(33,7)],fill=HO)
# head
d.polygon([(25,7),(38,7),(41,14),(38,22),(27,22),(23,14)],fill=B2)
d.polygon([(25,7),(30,7),(28,22),(27,22),(23,14)],fill=B3)
d.polygon([(36,10),(41,14),(38,22),(35,22)],fill=B1)
# eyes (sclera + slit pupil like trainer art)
d.line([(27,13),(31,14)],fill=OL); d.line([(34,14),(38,13)],fill=OL)
d.rectangle([28,15,30,16],fill=EW); d.rectangle([35,15,37,16],fill=EW)
d.point((29,15),fill=EP); d.point((29,16),fill=EP); d.point((36,15),fill=EP); d.point((36,16),fill=EP)
d.point((28,15),fill=WH)
# brow-eyes and mouth
d.point((31,10),fill=GL); d.point((34,10),fill=GL)
d.line([(28,19),(37,19)],fill=OL); d.point((30,20),fill=WH); d.point((35,20),fill=WH)
outline(im,OL); im.save('beast2.png')

sheet=Image.new('RGB',(2*(384+20),384),(60,60,60))
for i,n in enumerate(['sorc2','beast2']):
    sheet.paste(Image.open(n+'.png').convert('RGB').resize((384,384),Image.NEAREST),(i*404,0))
sheet.save('preview2.png')
