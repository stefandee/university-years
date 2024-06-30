program x;
uses graph;
type paleta=array[1..256,1..3] of byte;

var drv,gm,i,j:integer;
    b:byte;
    st1,st2:string;
    f:file of paleta;
    f1:file of byte;
    pal:paleta;
begin
drv:=installuserdriver('vga256',nil);
if drv=grerror then halt;
initgraph(drv,gm,'c:\bin\tp7\bgi');
assign(f,'default.pal');
reset(f);
read(f,pal);
close(f);
for i:=1 to 256 do setrgbpalette(i-1,pal[i,1],pal[i,2],pal[i,3]);
for i:=256 downto 1 do
begin
setcolor(i);
line(i,0,i,getmaxy);
end;
readln;
end.
