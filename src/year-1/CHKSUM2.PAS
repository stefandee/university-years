program chksum2;
uses graph;
type histogram=array[1..256] of integer;
var h:histogram;
    f:file of byte;
    b:byte;
    gd,gm,i:integer;
begin
for i:=1 to 256 do h[i]:=0;
assign(f,'c:\util\nc\nc.exe');
reset(f);
while not eof(f) do
      begin
           read(f,b);
           inc(h[b+1]);
      end;
gd:=detect;
initgraph(gd,gm,'c:\bin\tp7\bgi');
setfillstyle(1,yellow);
for i:=0 to 255 do bar(2*i,getmaxy,2*(i+1),getmaxy-h[i+1]);
readln;
close(f);
end.
