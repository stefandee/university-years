program forest;
uses graph;
const n=20;

var x,y:integer;
    gd,gm,i,j,k,l:integer;
    f:array[1..n,1..n] of byte;
    barat:boolean;

function cmmdc(m,n:integer):integer;
begin
if n=0 then cmmdc:=m
       else cmmdc:=cmmdc(n,m mod n);
end;


begin
x:=10;y:=10;
gd:=detect;initgraph(gd,gm,'c:\bin\bp\bgi');
setfillstyle(1,green);
for i:=1 to n do for j:=1 to n do fillellipse(i*10,j*10,2,2);
setfillstyle(1,lightblue);
fillellipse(x*10,y*10,2,2);
setfillstyle(1,yellow);
setcolor(yellow);
for i:=1 to n do
    for j:=1 to n do
        if cmmdc(abs(i-x),abs(j-y))=1 then fillellipse(i*10,j*10,2,2);
readln;
end.



