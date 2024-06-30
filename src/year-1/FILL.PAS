program fillrnr;

uses graph,crt;

var gd,gm:integer;

procedure fillr(x,y,color:integer);
var limit:integer;
procedure rfill(x,y:integer);
begin
putpixel(x,y,color);
if getpixel(x+1,y)=limit then begin
                              rfill(x+1,y);
                              end;
if getpixel(x-1,y)=limit then begin
                              rfill(x-1,y);
                              end;
if getpixel(x,y+1)=limit then begin
                              rfill(x,y+1);
                              end;
if getpixel(x,y-1)=limit then rfill(x,y-1);
end;
begin
limit:=getpixel(x,y);
rfill(x,y);
end;

procedure fillnr(x,y,color:integer);

type point =record
          x,y:integer;
          end;
const maxsp=1000;
var stack:array[1..maxsp] of point;
    i,j,k,l:integer;
procedure addstack(z,t:integer);
var m:integer;
begin
for m:=1 to maxsp do if (stack[m].x=-1) and (stack[m].y=-1) then begin
                                         stack[m].x:=z;
                                         stack[m].y:=t;
                                         exit;
                                         end;
end;
procedure init;
var m:integer;
begin
for m:=1 to maxsp do
begin
stack[m].x:=-1;
stack[m].y:=-1;
end;
end;
procedure checkstack;
var m,sum:integer;
    s:string;
begin
sum:=0;
for m:=1 to maxsp do if stack[m].x<>-1 then inc(sum);
str(sum,s);
setfillstyle(1,black);
bar(200,200,250,210);
outtextxy(200,200,s);
end;
begin
l:=getpixel(x,y);
init;
i:=1;
stack[i].x:=x;stack[i].y:=y;
repeat
if (stack[i].x<>-1) and (stack[i].y<>-1) then
   if getpixel(stack[i].x,stack[i].y)=color then begin
                                                 stack[i].x:=-1;
                                                 stack[i].y:=-1;
                                                 end
                                             else begin
                                                  k:=stack[i].x;
                                                  j:=k-1;
                                                  while getpixel(k,stack[i].y)=l do
                                                  begin
                                                  if getpixel(k,stack[i].y+1)=l then addstack(k,stack[i].y+1);
                                                  if getpixel(k,stack[i].y-1)=l then addstack(k,stack[i].y-1);
                                                  putpixel(k,stack[i].y,color);
                                                  inc(k);
                                                  end;
                                                  while getpixel(j,stack[i].y)=l do
                                                  begin
                                                  if getpixel(j,stack[i].y-1)=l then addstack(j,stack[i].y-1);
                                                  if getpixel(j,stack[i].y+1)=l then addstack(j,stack[i].y+1);
                                                  putpixel(j,stack[i].y,color);
                                                  dec(j);
                                                  end;
                                                  i:=0;
                                                  end;

inc(i);
{checkstack;}
until i>maxsp;
end;

begin
gd:=detect;
initgraph(gd,gm,'c:\bin\bp\bgi');
rectangle(0,0,90,90);
circle(40,40,4);
circle(20,20,15);
circle(10,10,5);
fillr(2,2,3);
readln;
end.


