unit squadvar;

{coordonatele din matrice=coordonatele carteziene}
{scade miscarile din variabila soldatului !!}

interface

uses graph,crt;

const n=60;
      m=40;
      my=3;
      en=10;
      pasx=10;
      pasy=10;
      cursc=black;
      enemc=red;
      myc=white;
      gridc=lightgray;
type gnd = record
         color,height,move:byte;
           end;
     table=array[1..n,1..m] of gnd;
     soldier = record
             name:string[10];
             x,y,move:integer;
             skill,hide,power:byte;
             task:byte;{what is really the soldier doing:free to move,stand&fight,retreat}
             end;
     switch=(on,off);

var i,j,gd,gm,err:integer;
    cx,cy,msgx,mgsy:integer;
    mysold:array[1..my] of soldier;
    enemy:array[1..en] of soldier;
    ground:table;
    fg:file of table;
    gridtest:switch;
    ret_name:string;
    ret_pos:integer;

procedure initsoldiers;
procedure initscreen;
procedure outintxy(x,y,nr:integer);
procedure testfield;
procedure do_it(xi,yi,color1,color2:integer);

implementation

const   nr_opt=5;
        options:array[1..nr_opt] of string[12]=('Move','Fire','Weapon','Stand&Fight','End turn');


procedure move_sold;

var ch:char;

begin

repeat
if keypressed then ch:=readkey
              else ch:=#0;
case ch of
#72 : begin
      setfillstyle(1,ground[mysold[ret_pos].x,mysold[ret_pos].y].color);
      bar((mysold[ret_pos].x-1)*pasx,pasy*(mysold[ret_pos].y-1),pasx*mysold[ret_pos].x,pasy*mysold[ret_pos].y);
      if gridtest=on then begin
                          setcolor(gridc);
                          rectangle((mysold[ret_pos].x-1)*pasx,pasy*(mysold[ret_pos].y-1),pasx*mysold[ret_pos].x,
                          pasy*mysold[ret_pos].y);
                          end;
      dec(mysold[ret_pos].y);
      if mysold[ret_pos].y<1 then mysold[ret_pos].y:=1;
      setfillstyle(1,myc);
      bar((mysold[ret_pos].x-1)*pasx,pasy*(mysold[ret_pos].y-1),pasx*mysold[ret_pos].x,pasy*mysold[ret_pos].y);
      end;
#80 : begin
      setfillstyle(1,ground[mysold[ret_pos].x,mysold[ret_pos].y].color);
      bar((mysold[ret_pos].x-1)*pasx,pasy*(mysold[ret_pos].y-1),pasx*mysold[ret_pos].x,pasy*mysold[ret_pos].y);
      if gridtest=on then begin
                          setcolor(gridc);
                          rectangle((mysold[ret_pos].x-1)*pasx,pasy*(mysold[ret_pos].y-1),pasx*mysold[ret_pos].x,
                          pasy*mysold[ret_pos].y);
                          end;
      inc(mysold[ret_pos].y);
      if mysold[ret_pos].y>m then mysold[ret_pos].y:=m;
      setfillstyle(1,myc);
      bar((mysold[ret_pos].x-1)*pasx,pasy*(mysold[ret_pos].y-1),pasx*mysold[ret_pos].x,pasy*mysold[ret_pos].y);
      end;
#77 : begin
      setfillstyle(1,ground[mysold[ret_pos].x,mysold[ret_pos].y].color);
      bar((mysold[ret_pos].x-1)*pasx,pasy*(mysold[ret_pos].y-1),pasx*mysold[ret_pos].x,pasy*mysold[ret_pos].y);
      if gridtest=on then begin
                          setcolor(gridc);
                          rectangle((mysold[ret_pos].x-1)*pasx,pasy*(mysold[ret_pos].y-1),pasx*mysold[ret_pos].x,
                          pasy*mysold[ret_pos].y);
                          end;
      inc(mysold[ret_pos].x);
      if mysold[ret_pos].x>n then mysold[ret_pos].x:=n;
      setfillstyle(1,myc);
      bar((mysold[ret_pos].x-1)*pasx,pasy*(mysold[ret_pos].y-1),pasx*mysold[ret_pos].x,pasy*mysold[ret_pos].y);
      end;
#75 : begin
      setfillstyle(1,ground[mysold[ret_pos].x,mysold[ret_pos].y].color);
      bar((mysold[ret_pos].x-1)*pasx,pasy*(mysold[ret_pos].y-1),pasx*mysold[ret_pos].x,pasy*mysold[ret_pos].y);
      if gridtest=on then begin
                          setcolor(gridc);
                          rectangle((mysold[ret_pos].x-1)*pasx,pasy*(mysold[ret_pos].y-1),pasx*mysold[ret_pos].x,
                          pasy*mysold[ret_pos].y);
                          end;
      dec(mysold[ret_pos].x);
      if mysold[ret_pos].x<1 then mysold[ret_pos].x:=1;
      setfillstyle(1,myc);
      bar((mysold[ret_pos].x-1)*pasx,pasy*(mysold[ret_pos].y-1),pasx*mysold[ret_pos].x,pasy*mysold[ret_pos].y);
      end;
end;
until ch=#32;
end;


procedure initgrid;

var i,j:integer;

begin
gridtest:=off;
if gridtest=on then begin
                    setcolor(gridc);
                    for i:=0 to n do line(i*pasx,0,i*pasx,m*pasy);
                    for i:=0 to m do line(0,i*pasy,n*pasx,i*pasy);{grila}
                    end;
end;

procedure initscreen;

var msgx,msgy:integer;

begin

gd:=detect;initgraph(gd,gm,'c:\bin\tp7\bgi');
cx:=1;cy:=1;
msgx:=getmaxx-150;msgy:=getmaxy-150;
assign(fg,'ground.dat');
reset(fg);
read(fg,ground);
close(fg);
for i:=1 to n do
    for j:=1 to m do
        begin
        setfillstyle(1,ground[i,j].color);
        bar((i-1)*pasx,pasy*(j-1),pasx*i,pasy*j);
        end;
initgrid;
setcolor(cursc);rectangle((cx-1)*pasx,pasy*(cy-1),pasx*cx,pasy*cy);
setfillstyle(1,myc); {my soldiers}
for i:=1 to my do bar((mysold[i].x-1)*pasx,pasy*(mysold[i].y-1),pasx*mysold[i].x,pasy*mysold[i].y);
setfillstyle(1,enemc); {enemies}
for i:=1 to en do bar((enemy[i].x-1)*pasx,pasy*(enemy[i].y-1),pasx*enemy[i].x,pasy*enemy[i].y);

end;

procedure initsoldiers;

begin

randomize;
mysold[1].name:='PHANE';mysold[2].name:='BRIGAND';mysold[3].name:='NAVVIE';
for i:=1 to my do
with mysold[i] do
     begin
          x:=random(n)+1;
          y:=random(m)+1;
          move:=random(30)+1;
          skill:=random(30)+1;
          hide:=random(30)+1;
          power:=random(30)+1;
     end;

for i:=1 to en do
with enemy[i] do
     begin
          x:=random(n)+1;
          y:=random(m)+1;
          move:=random(30)+1;
          skill:=random(30)+1;
          hide:=random(30)+1;
          power:=random(30)+1;
     end;
end;{procedure initsoldiers}

procedure outintxy;

var st:string;

begin

str(nr,st);
outtextxy(x,y,st);

end;

procedure do_it;

var i,lungmax:integer;
    oldstyle:textsettingstype;
    xc,opt:integer;
    ch:char;

begin


{making window ...}
gettextsettings(oldstyle);
lungmax:=0;
for i:=1 to nr_opt do if length(options[i])>lungmax then lungmax:=length(options[i]);
setfillstyle(1,color1);
bar(xi,yi,xi+lungmax*15,yi+11*(nr_opt+1));
setcolor(color2);
rectangle(xi+3,yi+3,xi+lungmax*15-3,yi+11*(nr_opt+1)-3);
setfillstyle(1,color1);
bar(xi+lungmax*15 div 2-4*length(ret_name),yi,xi+lungmax*15 div 2+4*length(ret_name),yi+10);
outtextxy(xi+lungmax*15 div 2-4*length(ret_name),yi,ret_name);
settextjustify(1,2);
for i:=1 to nr_opt do outtextxy(xi+lungmax*15 div 2,yi+i*10,options[i]);

{moving in the menu...}
xc:=xi+lungmax*15 div 2;opt:=1;
setcolor(black);
outtextxy(xc,yi+opt*10,options[opt]);

repeat
if keypressed then ch:=readkey
              else ch:=#0;
case ch of
#72 : begin
      setcolor(color2);
      outtextxy(xc,yi+opt*10,options[opt]);
      dec(opt);
      if opt<1 then opt:=nr_opt;
      setcolor(black);
      outtextxy(xc,yi+opt*10,options[opt]);
      end;
#80 : begin
      setcolor(color2);
      outtextxy(xc,yi+opt*10,options[opt]);
      inc(opt);
      if opt>nr_opt then opt:=1;
      setcolor(black);
      outtextxy(xc,yi+opt*10,options[opt]);
      end;
#32: begin
     case opt of
     1:move_sold;
     end;{case}
     end;
end;
until ch in [#27,#75,#77];

{clear the mess...}
setfillstyle(1,black);
bar(xi,yi,xi+lungmax*15,yi+11*(nr_opt+1));
{undo paint changes...}
with oldstyle do
     begin
          settextjustify(horiz,vert);
          settextstyle(font,direction,charsize);
     end;


end;

procedure testfield;

var i:integer;

begin

ret_name:='';
ret_pos:=0;
for i:=1 to my do
    if (mysold[i].x=cx) and (mysold[i].y=cy) then begin
                                                  ret_name:=mysold[i].name;
                                                  ret_pos:=i;
                                                  break;
                                                  end;

end;

end.