import struct, sys, os
sys.path.insert(0,os.path.dirname(os.path.abspath(__file__)))
from render_map import *
W,H=10,35
FLOOR=522
b=[[ (520,0,0) for _ in range(W)] for _ in range(H)]   # (metatile, collision, elevation)
def put(x,y,m,c=0,e=0): b[y][x]=(m,c,e)
for y in range(5,H):
    for x in range(1,9): put(x,y,FLOOR)
# top wall + leader alcove
for x in range(1,9):
    put(x,1,526,1); put(x,2,534,1)
put(4,2,552,1); put(5,2,553,1)
for x in range(1,9):
    put(x,3,FLOOR); put(x,4,FLOOR)
for i,m in enumerate((536,537,538,539)): put(3+i,3,m,1)
for i,m in enumerate((544,545,546,547)): put(3+i,4,m,1)
# statues flanking the door, door mat
put(3,33,524,1); put(6,33,524,1)
put(3,32,516); put(6,32,516)   # statue top halves (516 sits above 524)
put(4,34,6,0,3); put(5,34,7,0,3)
# objects (x,y,label,color)
L=(255,60,60,255); R=(60,120,255,255); G=(40,200,40,255)
marks=[(4,3,'S',(255,0,255,255)),(5,3,'A',(255,0,255,255)),
 (8,9,'Ve',R),(1,13,'Rh',L),(8,17,'Tu',R),(1,21,'Ar',L),(8,25,'Va',R),(1,29,'Na',L),(2,31,'G',G)]
def blocks():
    return [(m&0x3ff)|(c<<10)|(e<<12) for row in b for (m,c,e) in row]
if __name__=='__main__':
    bl=blocks()
    render(W,H,bl,2,marks).save('/tmp/mossdeep_new.png')
    print('ok')
