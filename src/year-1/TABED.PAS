program tabed;
uses crt;
const maxx=11;
      maxy=16;
      maxt=6;
type table=array[1..maxx,1..maxy] of byte;
var f:file of table;
    i,j,k:integer;
    x,y:integer;
    count:integer;
    tab:table;
    ch:char;
begin
count:=0;
clrscr;
assign(f,'tables.sqd');
reset(f);
seek(f,count);
read(f,tab);
for i:=1 to maxx do begin
for j:=1 to maxy do begin
textcolor(white);
gotoxy(5+j*4,5+i);
write(tab[i,j]);
end;
end;
x:=1;
y:=2;
textcolor(white+128);
gotoxy(5+y*4,5+x);
write(tab[x,y]);

repeat
if keypressed then begin
                   ch:=readkey;
                   if ch='o' then begin
               textcolor(white);
               gotoxy(5+y*4,5+x);
               write(tab[x,y]);
               dec(y);
               if y<1 then y:=maxy;
               textcolor(white+128);
               gotoxy(5+y*4,5+x);
               write(tab[x,y]);
               end;
if ch='p' then begin
               textcolor(white);
               gotoxy(5+y*4,5+x);
               write(tab[x,y]);
               inc(y);
               if y>maxy then y:=1;
               textcolor(white+128);
               gotoxy(5+y*4,5+x);
               write(tab[x,y]);
               end;
if ch='q' then begin
               textcolor(white);
               gotoxy(5+y*4,5+x);
               write(tab[x,y]);
               dec(x);
               if x<1 then x:=maxx;
               textcolor(white+128);
               gotoxy(5+y*4,5+x);
               write(tab[x,y]);
               end;
if ch='z' then begin
               textcolor(white);
               gotoxy(5+y*4,5+x);
               write(tab[x,y]);
               inc(x);
               if x>maxx then x:=1;
               textcolor(white+128);
               gotoxy(5+y*4,5+x);
               write(tab[x,y]);
               end;
if ch='w' then begin
               textcolor(black);
               gotoxy(5+y*4,5+x);
               write(tab[x,y]);
               inc(tab[x,y]);
               textcolor(white+128);
               gotoxy(5+y*4,5+x);
               write(tab[x,y]);
               end;
if ch='x' then begin
               textcolor(black);
               gotoxy(5+y*4,5+x);
               write(tab[x,y]);
               dec(tab[x,y]);
               textcolor(white+128);
               gotoxy(5+y*4,5+x);
               write(tab[x,y]);
               end;
if ch='m' then begin
               seek(f,count);
               write(f,tab);
               end;
if ch='n' then begin
               clrscr;
               inc(count);
               if count>5 then count:=0;
               seek(f,count);
               read(f,tab);
               for i:=1 to maxx do begin
               for j:=1 to maxy do begin
               textcolor(white);
               gotoxy(5+j*4,5+i);
               write(tab[i,j]);
               end;
               end;
               x:=1;
               y:=1;
               textcolor(white+128);
               gotoxy(5+y*4,5+x);
               write(tab[x,y]);
               end;
             if ch=#27 then halt;
              end
              else ch:=#0;

until ch=#27;
readln;
end.