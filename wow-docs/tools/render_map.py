import struct, sys, json, os
from PIL import Image, ImageDraw
R=os.environ.get('GJT_REPO','/home/claude/gjt-pokeemerald-expansion')+'/'
def load_pal(path):
    L=open(path).read().split('\n')
    n=int(L[2]); cols=[]
    for l in L[3:3+n]:
        r,g,b=map(int,l.split()); cols.append((r,g,b))
    return cols
def load_tileset(d):
    base=R+'data/tilesets/'+d+'/'
    im=Image.open(base+'tiles.png'); 
    mt=open(base+'metatiles.bin','rb').read()
    pals={}
    for f in os.listdir(base+'palettes'):
        if f.endswith('.pal'): pals[int(f[:2])]=load_pal(base+'palettes/'+f)
    return im,mt,pals
pim,pmt,ppal=load_tileset('primary/building')
SECONDARY=os.environ.get('GJT_SECONDARY','mossdeep_gym')
sim,smt,spal=load_tileset('secondary/'+SECONDARY)
def tile_img(idx,pal,xf,yf):
    if idx<512: im=pim; i=idx; cols=ppal.get(pal)
    else: im=sim; i=idx-512; cols=spal.get(pal)
    if cols is None: cols=[(255,0,255)]*16
    tw=im.width//8
    tx,ty=(i%tw)*8,(i//tw)*8
    t=im.crop((tx,ty,tx+8,ty+8))
    px=t.load()
    out=Image.new('RGBA',(8,8))
    op=out.load()
    for y in range(8):
        for x in range(8):
            c=px[x,y]
            op[x,y]=(0,0,0,0) if c==0 else cols[c]+(255,)
    if xf: out=out.transpose(Image.FLIP_LEFT_RIGHT)
    if yf: out=out.transpose(Image.FLIP_TOP_BOTTOM)
    return out
cache={}
def metatile(mid):
    if mid in cache: return cache[mid]
    data=pmt if mid<512 else smt
    i=mid if mid<512 else mid-512
    img=Image.new('RGBA',(16,16),(0,0,0,255))
    if (i+1)*16>len(data):
        cache[mid]=img; return img
    ents=struct.unpack_from('<8H',data,i*16)
    for layer in (0,1):
        for k in range(4):
            e=ents[layer*4+k]
            t=tile_img(e&0x3ff,(e>>12)&0xf,(e>>10)&1,(e>>11)&1)
            img.alpha_composite(t,((k%2)*8,(k//2)*8))
    cache[mid]=img; return img
def render(w,h,blocks,scale=2,marks=()):
    img=Image.new('RGBA',(w*16,h*16),(0,0,0,255))
    for y in range(h):
        for x in range(w):
            img.alpha_composite(metatile(blocks[y*w+x]&0x3ff),(x*16,y*16))
    d=ImageDraw.Draw(img)
    for (x,y,label,col) in marks:
        d.rectangle((x*16+1,y*16+1,x*16+14,y*16+14),outline=col,width=2)
        d.text((x*16+4,y*16+2),label,fill=col)
    return img.resize((w*16*scale,h*16*scale),Image.NEAREST)
if __name__=='__main__':
    w,h=26,36
    data=open(R+'data/layouts/MossdeepCity_Gym/map.bin','rb').read()
    blocks=list(struct.unpack('<%dH'%(w*h),data))
    render(w,h,blocks,1).save('/tmp/mossdeep_old.png')
