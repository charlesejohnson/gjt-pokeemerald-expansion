import struct, sys, os
sys.path.insert(0,os.path.dirname(os.path.abspath(__file__)))
from render_map import *
W,H=10,31
FLOOR=522
b=[[ (520,0,0) for _ in range(W)] for _ in range(H)]   # (metatile, collision, elevation)
def put(x,y,m,c=0,e=0): b[y][x]=(m,c,e)
for y in range(5,H):
    for x in range(1,9): put(x,y,FLOOR)
# side walls (519 = wall on the left of the floor, 517 = wall on the right)
for y in range(2,H):
    put(0,y,519,1); put(9,y,517,1)
# top wall + leader alcove
for x in range(0,10):
    put(x,1,526,1)
for x in range(1,9): put(x,2,534,1)
put(0,2,533,1); put(9,2,535,1)
put(4,2,552,1); put(5,2,553,1)
for x in range(1,9):
    put(x,3,FLOOR); put(x,4,FLOOR)
for i,m in enumerate((536,537,538,539)): put(3+i,3,m,1)
for i,m in enumerate((544,545,546,547)): put(3+i,4,m,1)
# center runner (floor variant)
for y in range(6,H-2):
    put(4,y,514); put(5,y,514)
# statue pairs between stations: orb 516 above base 524
def statue(x,y): put(x,y,516); put(x,y+1,524,1)
for y in (12,19):
    statue(1,y); statue(8,y)
# door statues and mat
statue(3,H-3); statue(6,H-3)
put(4,H-1,6,0,3); put(5,H-1,7,0,3)
# stations south->north: (x, y, label, facing, color)
L=(255,60,60,255); R=(60,120,255,255); G=(40,200,40,255); P=(255,0,255,255)
marks=[(4,3,'S',P),(5,3,'A',P),
 (8,8,'Ve',R),(1,10,'Rh',L),(8,15,'Tu',R),(1,17,'Ar',L),(8,22,'Va',R),(1,24,'Na',L),(3,27,'G',G)]
def blocks():
    return [(m&0x3ff)|(c<<10)|(e<<12) for row in b for (m,c,e) in row]
if __name__=='__main__':
    render(W,H,blocks(),3,[]).save('/tmp/mossdeep_new.png')
    print('ok')
