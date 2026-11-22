from PIL import Image, ImageDraw
# sorceress detail pass
import subprocess
im=Image.open('sorc2.png'); d=ImageDraw.Draw(im)
OL,SK,SKS,SKH,HR,HRS,RB,RBS,RBH,GD,CP,EY,WH,OR,ORD=range(1,16)
# hands: finger separations
for p in [(55,21),(56,22),(56,20)]: d.point(p,fill=SKS)
d.point((57,19),fill=OL)
for p in [(26,43),(27,43)]: d.point(p,fill=SKS)
# gold cuff
d.line([(52,20),(55,23)],fill=GD)
d.line([(25,39),(29,40)],fill=GD)
# gem on sash
d.point((33,37),fill=OR); d.point((33,38),fill=OR)
# robe folds
d.line([(38,44),(43,56)],fill=RBH); d.line([(27,48),(25,59)],fill=RBS)
d.line([(35,46),(36,60)],fill=RBS)
# hair strands and sheen
d.line([(22,26),(19,34)],fill=HRS); d.line([(25,21),(22,29)],fill=HRS)
for p in [(23,14),(22,19),(21,25),(19,31)]: d.point(p,fill=WH)
# cape fold lines
d.line([(18,42),(14,56)],fill=RBS); d.line([(22,36),(17,48)],fill=RBH)
# eye: add sclera tint beside iris, lower lash
# lips
im.save('sorc3.png')
# colossus detail pass
im2=Image.open('beast3.png'); d=ImageDraw.Draw(im2)
OL,B1,B2,B3,B4,DK,GL,WH,HO,HOS,EW,CK,SEA,SEAL,LAND=range(1,16)
# chest plate lines and folds
for pts in [[(20,36),(24,44)],[(43,36),(39,44)],[(21,30),(26,34)],[(42,30),(37,34)]]:
    d.line(pts,fill=B1)
d.line([(19,40),(22,46)],fill=B3); d.line([(25,26),(28,30)],fill=B3)
# belly highlights left
for p in [(23,36),(24,38),(23,42)]: d.point(p,fill=B3)
# horn ridges
for p in [(18,3),(21,5),(23,4),(45,3),(42,5),(40,4)]: d.point(p,fill=HOS)
# forehead markings
d.line([(30,8),(30,12)],fill=B4); d.line([(33,8),(33,12)],fill=B1)
# fangs
d.point((31,20),fill=WH); d.point((33,20),fill=WH)
# claws digit gaps
for p in [(16,47),(18,47),(45,47),(47,47)]: d.point(p,fill=B2)
# void wisps drifting off shoulders
for p in [(7,22),(8,24),(9,26),(56,22),(55,24),(54,26)]: d.point(p,fill=B4)
im2.save('beast4.png')
sh=Image.new('RGB',(2*(384+20),384),(60,60,60))
for i,n in enumerate(['sorc3','beast4']):
    sh.paste(Image.open(n+'.png').convert('RGB').resize((384,384),Image.NEAREST),(i*404,0))
sh.save('preview4.png')
