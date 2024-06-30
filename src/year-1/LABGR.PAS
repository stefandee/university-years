program labirint;
uses crt,graph;

const a:array[1..4] of integer=(1,0,-1,0);
      b:array[1..4] of integer=(0,1,0,-1);
      sxf=7;
      syf=14;
      brick:fillpatterntype=(255,129,129,255,38,38,255,255);

var h:array[1..24] of string[80];
    gd,gm:integer;

procedure read_maze;

var f:text;
    i,j:integer;

begin

setfillpattern(brick,lightgray);
assign(f,'labirint.dat');
reset(f);
setfillstyle(12,lightgray);
for i:=1 to 24 do
        begin
             readln(f,h[i]);
             for j:=1 to 80 do
                 case h[i,j] of
                 'P':bar(j*sxf-sxf,i*syf-syf,j*sxf,i*syf)
                 end;
        end;
close(f);
end;

procedure way(x,y:integer);

var u,v,k:integer;
    found:boolean;

begin

k:=0;
setfillstyle(1,lightblue);
bar(y*sxf-sxf+1,x*syf-syf+1,y*sxf-1,x*syf-1);
h[x,y]:='*';
found:=false;

repeat
k:=k+1;
u:=x+a[k];
v:=y+b[k];
if (u>24) or (v>80) or (u<1) or (v<1) then begin
                                           setfillstyle(1,yellow);
                                           bar(y*sxf-sxf+1,x*syf-syf+1,y*sxf-1,x*syf-1);
                                           found:=true;
                                           end
   else begin
        if h[u,v]='.' then begin
                           setfillstyle(1,lightblue);
                           bar(v*sxf-sxf+1,u*syf-syf+1,v*sxf-1,u*syf-1);
                           setfillstyle(1,black);
                           bar(v*sxf-sxf+1,u*syf-syf+1,v*sxf-1,u*syf-1);
                           delay(11);
                           way(u,v);
                           end;

        end;
until k=4;
if not found then begin
                  setfillstyle(1,black);
                  bar(y*sxf-sxf+1,x*syf-syf+1,y*sxf-1,x*syf-1);
                  end;
end;



begin

gd:=detect;
initgraph(gd,gm,'f:\bin\tp6\bgi');
cleardevice;
read_maze;
way(2,2);
readln;

end.

