program demonstration;
uses turtle,graph;
var gd,gm,l,p,c,m:integer;
    u,c1:real;
procedure poli(var lat:integer;var unghi:real);
begin
forward(lat);
right(unghi);
poli(lat,unghi);
end;
procedure spirala1(var pas:integer;var unghi:real;var cres:integer);
begin
forward(pas);
right(unghi);
inc(pas,cres);
spirala1(pas,unghi,cres);
end;
procedure spirala2(var pas:integer;var unghi:real;var cres:real);
begin
forward(pas);
right(unghi);
unghi:=unghi+cres;
spirala2(pas,unghi,cres);
end;
procedure copac1(marime:integer);
var m:integer;
begin
forward(marime);
left(20);
m:=marime div 2;
copac1(m);
forward(marime);
right(40);
copac1(m);
end;
begin
gd:=detect;
initgraph(gd,gm,'c:\bin\bp\bgi');
m:=20;u:=30;c1:=2.0;
copac1(m);
{spirala2(m,u,c1);}
{poli(m,u);}
readln;
end.
