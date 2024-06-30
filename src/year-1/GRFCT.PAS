program project;
{R+}
uses graph,crt,funct;
type buffer=array[1..2048] of char;
     buf=^buffer;
const nr=10;
      nri=7;
      nre=nri+3;
      fname:array[1..nr,1..2] of string=
                              (('Strofoida','1'),
                               ('Astroida','1'),
                               ('Cicloida','2'),
                               ('Trisectoarea MacLaurin','1'),
                               ('Lemniscata Bernoulli','1'),
                               ('Fusee','1'),
                               ('Trisectoarea Longchamps','1'),
                               ('Epicicloida','2'),
                               ('Hipocicloida','2'),
                               ('Concoida Nicomede','2'));
     iconpos:array[1..nre,1..2] of integer=((20,400),(85,400),(150,400),
                                          (215,400),(280,400),(500,400),
                                          (565,400),(500,140),(565,140),
                                          (500,205));
var gd,gm,i,ppos,br,ipos,beg,fin:integer;
    ch:char;
    manv:string;
    f:file;
    icon1,icon2,icon3,icon4,icon5,icon6,icon7,icon8,icon9,spc:buf;
procedure MAKEWIN(x1,y1,x2,y2:integer);
begin
setfillstyle(1,lightgray);
bar(x1,y1,x2,y2);
for i:=0 to (10*(x2-x1) div getmaxx) do
begin
setcolor(white);
moveto(x1+i,y1+i);
lineto(x2-i,i);
setcolor(darkgray);
lineto(x2-i,y2-i);
lineto(i+x1,y2-i);
setcolor(white);
lineto(i+x1,i+y1);
end;
end;
procedure MAKESHAD(x1,y1,x2,y2:integer);
begin
for i:=0 to (10*(x2-x1) div getmaxx) do
begin
setcolor(darkgray);
moveto(x1-i,y1-i);
lineto(x2+i,y1-i);
setcolor(white);
lineto(x2+i,y2+i);
lineto(x1-i,y2+i);
setcolor(darkgray);
lineto(x1-i,y1-i);
end;
end;
procedure CHECKFUNCOUNT;
var comp,codeerr:integer;
begin
val(fname[funcount,2],comp,codeerr);
if funcount<1 then funcount:=nr;
if funcount>nr then funcount:=1;
setwritemode(xorput);
setcolor(red);
val(fname[funcount,2],comp,codeerr);
for i:=nri+1 to nri+comp do begin
putimage(iconpos[i,1],iconpos[i,2],icon6^,0);
moveto(iconpos[i,1]+paramval[i-nri],iconpos[i,2]+20);
linerel(0,20);
setcolor(red);
settextstyle(0,0,0);
str(zoom,manv);
outtextxy(getmaxx div 2-140,getmaxy div 2+115,fname[funcount,1]+' '+'on zoom X '+manv);

end;
end;
procedure PRESENT;
begin
makewin(0,0,getmaxx,getmaxy);
{setfillstyle(1,lightblue);
bar(getmaxx div 2-170,getmaxy div 2-120,getmaxx div 2+170,getmaxy div 2+120);}
setfillstyle(1,black);
bar(getmaxx div 2-150,getmaxy div 2-100,getmaxx div 2+150,getmaxy div 2+100);
makeshad(getmaxx div 2-150,getmaxy div 2-100,getmaxx div 2+150,getmaxy div 2+100);
bar(getmaxx div 2-120,20,getmaxx div 2+120,60);
makeshad(getmaxx div 2-120,20,getmaxx div 2+120,60);
bar(getmaxx div 2-150,getmaxy div 2+110,getmaxx div 2+150,getmaxy div 2+130);
makeshad(getmaxx div 2-150,getmaxy div 2+110,getmaxx div 2+150,getmaxy div 2+130);
setcolor(red);
str(zoom,manv);
settextstyle(0,0,0);
outtextxy(getmaxx div 2-140,getmaxy div 2+115,fname[funcount,1]+' '+'on zoom X '+manv);
setcolor(yellow);
settextstyle(6,0,0);
outtextxy(getmaxx div 2-110,10,'Graphics drawer');
setcolor(0);
settextstyle(0,0,0);
new(icon1);
new(icon2);
new(icon3);
new(icon4);
new(icon5);
new(icon6);
new(icon7);
new(icon8);
new(icon9);
new(spc);
assign(f,'icons.fct');
reset(f,2048);
blockread(f,icon1^,1,br);
blockread(f,icon2^,1,br);
blockread(f,icon3^,1,br);
blockread(f,icon4^,1,br);
blockread(f,icon5^,1,br);
blockread(f,icon6^,1,br);
blockread(f,icon7^,1,br);
blockread(f,icon8^,1,br);
blockread(f,icon9^,1,br);
getimage(iconpos[8,1],iconpos[8,2],iconpos[8,1]+60,iconpos[8,2]+60,spc^);
putimage(iconpos[1,1],iconpos[1,2],icon1^,0);
putimage(iconpos[2,1],iconpos[2,2],icon3^,0);
putimage(iconpos[3,1],iconpos[3,2],icon5^,0);
putimage(iconpos[4,1],iconpos[4,2],icon8^,0);
putimage(iconpos[5,1],iconpos[5,2],icon9^,0);
putimage(iconpos[7,1],iconpos[7,2],icon6^,0);
putimage(iconpos[6,1],iconpos[6,2],icon7^,0);
putimage(iconpos[8,1],iconpos[8,2],icon6^,0);
setwritemode(0);
setcolor(red);
rectangle(iconpos[ipos,1]-2,iconpos[ipos,2]-2,iconpos[ipos,1]+62,iconpos[ipos,2]+62);
setwritemode(xorput);
setcolor(red);
moveto(iconpos[7,1]+fin,iconpos[7,2]+20);
linerel(0,20);
moveto(iconpos[6,1]+60-beg,iconpos[6,2]+20);
linerel(0,20);
moveto(iconpos[8,1]+round(paramval[1]),iconpos[8,2]+20);
linerel(0,20);
end;
procedure CHECKBEG;
begin
if beg<3 then beg:=3;
if beg>50 then beg:=50;
moveto(iconpos[6,1]+60-beg,iconpos[6,2]+20);
linerel(0,20);
end;
procedure CHECKFIN;
begin
if fin<3 then fin:=3;
if fin>50 then fin:=50;
moveto(iconpos[7,1]+fin,iconpos[7,2]+20);
linerel(0,20);
end;
procedure CHECKZOOM;
begin
if zoom>110 then zoom:=20;
if zoom<20 then zoom:=110;
setcolor(red);
settextstyle(0,0,0);
str(zoom,manv);
outtextxy(getmaxx div 2-140,getmaxy div 2+115,fname[funcount,1]+' '+'on zoom X '+manv);
end;
procedure pposcheck;
var comp,codeerr:integer;
begin
val(fname[funcount,2],comp,codeerr);
if ppos>comp then ppos:=1;
if ppos<1 then ppos:=comp;
setfillstyle(1,red);
bar(490,160+10*ppos,497,168+10*ppos);
end;
procedure IPOSCHECK;
var comp,codeerr:integer;
begin
val(fname[funcount,2],comp,codeerr);
if ipos>nri+comp then ipos:=1;
if ipos<1 then ipos:=nri+comp;
setcolor(red);
rectangle(iconpos[ipos,1]-2,iconpos[ipos,2]-2,iconpos[ipos,1]+62,iconpos[ipos,2]+62);
end;
procedure CHECKPARAM;
begin
if paramval[ipos-nri]>30 then paramval[ipos-nri]:=30;
if paramval[ipos-nri]<1 then paramval[ipos-nri]:=1;
moveto(iconpos[ipos,1]+paramval[ipos-nri],iconpos[ipos,2]+20);
linerel(0,20);
end;
procedure launch;
begin
case funcount of
6:fusee(-beg*pi,fin*pi);

1:strofoida(-beg*pi,fin*pi);

2:astroida(-beg*pi,fin*pi);

3:cicloida(-beg*pi,fin*pi);

4:trismac(-beg*pi,fin*pi);

5:lemniscata(-beg*pi,fin*pi);

7:trilong(-beg*pi,fin*pi);

8:epicicl(-beg*pi,fin*pi);

9:hipocicl(-beg*pi,fin*pi);

10:concoida(-beg*pi,fin*pi);
end;
end;
begin
zoom:=70;    {coeficientul de marire}
funcount:=1; {numarul functiei ce va fi desenata}
ppos:=1;
for i:=1 to 6 do paramval[i]:=1;
drawtype:=true;   {trasare graficului se face prin puncte sau unind linii cu puncte}
drawover:=false;  {permite suprapunere de grafice.initial,nu}
fin:=40;    {sfirsitul intervalului pe care se deseneaza}
beg:=40;    {inceputul intervalului pe care se deseneaza}
ipos:=1;    {fereastra curenta}
gd:=detect;
initgraph(gd,gm,'c:\bin\bp\bgi');
present;
repeat
if keypressed then begin
ch:=readkey;
if ch=#13 then begin
               setwritemode(0);
               launch;
               end;
if ch=#75 then begin
               setwritemode(0);
               setcolor(lightgray);
               rectangle(iconpos[ipos,1]-2,iconpos[ipos,2]-2,iconpos[ipos,1]+62,iconpos[ipos,2]+62);
               dec(ipos);
               iposcheck;
               end;
if ch=#77 then begin
               setwritemode(0);
               setcolor(lightgray);
               rectangle(iconpos[ipos,1]-2,iconpos[ipos,2]-2,iconpos[ipos,1]+62,iconpos[ipos,2]+62);
               inc(ipos);
               iposcheck;
               end;
if ch=#72 then begin
               if ipos=1 then begin
                              drawover:=not drawover;
                              if drawover then putimage(iconpos[1,1],iconpos[1,2],icon2^,0)
                                          else putimage(iconpos[1,1],iconpos[1,2],icon1^,0);
                               end;
               if ipos=2 then begin
                              drawtype:=not drawtype;
                              if drawtype then putimage(iconpos[2,1],iconpos[2,2],icon3^,0)
                                          else putimage(iconpos[2,1],iconpos[2,2],icon4^,0);
                              end;
               if ipos=3 then begin
                              setcolor(0);
                              settextstyle(0,0,0);
                              str(zoom,manv);
                              outtextxy(getmaxx div 2-140,getmaxy div 2+115,fname[funcount,1]+' '+'on zoom X '+manv);
                              for i:=nri+1 to nre do
                              putimage(iconpos[i,1],iconpos[i,2],spc^,0);
                              inc(funcount);
                              checkfuncount;
                              end;
               if ipos=4 then begin
                              setcolor(0);
                              settextstyle(0,0,0);
                              str(zoom,manv);
                              outtextxy(getmaxx div 2-140,getmaxy div 2+115,fname[funcount,1]+' '+'on zoom X '+manv);
                              inc(zoom,3);
                              checkzoom;
                              end;
               if ipos=5 then begin
                              setfillstyle(1,black);
                              bar(getmaxx div 2-150,getmaxy div 2-100,getmaxx div 2+150,getmaxy div 2+100);
                              settextstyle(0,0,0);
                              outtextxy(getmaxx div 2-150,getmaxy div 2-100,'Graphics Drawer was written by Phane');
                              outtextxy(getmaxx div 2-150,getmaxy div 2-88, 'of Blueflower,between 15 january - 8');
                              outtextxy(getmaxx div 2-150,getmaxy div 2-76, 'february 1994.Press Enter to see any');
                              outtextxy(getmaxx div 2-150,getmaxy div 2-64, 'graphic;select an option by pressing');
                              outtextxy(getmaxx div 2-150,getmaxy div 2-52, 'arrows UP and Down.You can chose the');
                              outtextxy(getmaxx div 2-150,getmaxy div 2-40, 'parameters in the same way,in tile  ');
                              outtextxy(getmaxx div 2-150,getmaxy div 2-28, 'with [0..+ì] in the upper right part');
                              outtextxy(getmaxx div 2-150,getmaxy div 2-16, 'of screen.');
                              end;
               if ipos=6 then begin
                              setwritemode(xorput);
                              setcolor(red);
                              moveto(iconpos[6,1]+60-beg,iconpos[6,2]+20);
                              linerel(0,20);
                              dec(beg);
                              checkbeg;
                              end;
               if ipos=7 then begin
                              setwritemode(xorput);
                              setcolor(red);
                              moveto(iconpos[7,1]+fin,iconpos[7,2]+20);
                              linerel(0,20);
                              inc(fin);
                              checkfin;
                              end;
              if (ipos=8) or (ipos=9) or (ipos=10) then begin
                             setwritemode(xorput);
                             setcolor(red);
                             moveto(iconpos[ipos,1]+round(paramval[ipos-nri]),iconpos[ipos,2]+20);
                             linerel(0,20);
                             paramval[ipos-nri]:=paramval[ipos-nri]+1;
                             checkparam;
                             end;

               end;
if ch=#80 then begin
               if ipos=1 then begin
                              drawover:=not drawover;
                              if drawover then putimage(iconpos[1,1],iconpos[1,2],icon2^,0)
                                          else putimage(iconpos[1,1],iconpos[1,2],icon1^,0);
                               end;
               if ipos=2 then begin
                              drawtype:=not drawtype;
                              if drawtype then putimage(iconpos[2,1],iconpos[2,2],icon3^,0)
                                          else putimage(iconpos[2,1],iconpos[2,2],icon4^,0);
                              end;
               if ipos=3 then begin
                              for i:=nri+1 to nre do
                              putimage(iconpos[i,1],iconpos[i,2],spc^,0);
                              setcolor(0);
                              settextstyle(0,0,0);
                              str(zoom,manv);
                              outtextxy(getmaxx div 2-140,getmaxy div 2+115,fname[funcount,1]+' '+'on zoom X '+manv);
                              dec(funcount);
                              checkfuncount;
                              end;
               if ipos=4 then begin
                              setcolor(0);
                              settextstyle(0,0,0);
                              str(zoom,manv);
                              outtextxy(getmaxx div 2-140,getmaxy div 2+115,fname[funcount,1]+' '+'on zoom X '+manv);
                              dec(zoom,3);
                              checkzoom;
                              end;
               if ipos=5 then begin
                              setfillstyle(1,black);
                              bar(getmaxx div 2-150,getmaxy div 2-100,getmaxx div 2+150,getmaxy div 2+100);
                              settextstyle(0,0,0);
                              outtextxy(getmaxx div 2-150,getmaxy div 2-100,'Graphics Drawer was written by Phane');
                              outtextxy(getmaxx div 2-150,getmaxy div 2-88, 'of Blueflower,between 15 january - 8');
                              outtextxy(getmaxx div 2-150,getmaxy div 2-76, 'february 1994.Press Enter to see any');
                              outtextxy(getmaxx div 2-150,getmaxy div 2-64, 'graphic;select an option by pressing');
                              outtextxy(getmaxx div 2-150,getmaxy div 2-52, 'arrows UP and Down.You can chose the');
                              outtextxy(getmaxx div 2-150,getmaxy div 2-40, 'parameters in the same way,in tile  ');
                              outtextxy(getmaxx div 2-150,getmaxy div 2-28, 'with [0..+ì] in the upper right part');
                              outtextxy(getmaxx div 2-150,getmaxy div 2-16, 'of screen.');
                              end;
               if ipos=6 then begin
                              setwritemode(xorput);
                              setcolor(red);
                              moveto(iconpos[6,1]+60-beg,iconpos[6,2]+20);
                              linerel(0,20);
                              inc(beg);
                              checkbeg;
                              end;
               if ipos=7 then begin
                              setwritemode(xorput);
                              setcolor(red);
                              moveto(iconpos[7,1]+fin,iconpos[7,2]+20);
                              linerel(0,20);
                              dec(fin);
                              checkfin;
                              end;
              if (ipos=8) or (ipos=9) or (ipos=10) then begin
                             setwritemode(xorput);
                             setcolor(red);
                             moveto(iconpos[ipos,1]+round(paramval[ipos-nri]),iconpos[ipos,2]+20);
                             linerel(0,20);
                             paramval[ipos-nri]:=paramval[ipos-nri]-1;
                             checkparam;
                             end;
               end;
end
        else ch:=#0;
until ch=#27;
closegraph;
end.




