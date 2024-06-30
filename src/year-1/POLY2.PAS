program poly2;
uses graph;
var gd,gm,i:integer;
    r,x0,y0,n:integer;
begin
gd:=detect;
initgraph(gd,gm,'c:\bin\tp7\bgi');
x0:=200;y0:=200;r:=100;n:=5;
{setcolor(lightred);
circle(x0,y0,r);}
moveto(x0-r,y0);
{setcolor(yellow);  }
i:=0;
for i:=0 to 5 do lineto(round(x0-r*cos(4*pi*i/n)),round(y0-r*sin(4*pi*i/n)));
{for i:=1 to n do lineto(round(x0-r*cos(2*pi*i/n)),round(y0-r*sin(2*pi*i/n)));}
readln;
{setcolor(black);
circle(x0,y0,r);}
end.