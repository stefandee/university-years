program gar;
uses graph,crt;
var n,i,gd,gm:integer;
    a:array[1..100]of pointtype;
begin
gd:=detect;
initgraph(gd,gm,'c:\bin\tp7\bgi');
if graphresult   <> grok  then halt;
circle(200,200,100);
readln(n);
for i:=1 to n do begin
 a[i].x:=round(200+100*cos(2*pi*i/n));
 a[i].y:=round(200+100*sin(2*pi*i/n));
end;
a[n+1]:=a[1];
drawpoly(n+1,a);
readln;
closegraph;
end.