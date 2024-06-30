program beneficiu;

uses graph,crt;

const       pal:array[1..16,1..4] of integer=(
                                         {black}      (0,0,0,0),
                                         {blue}       (1,0,0,31),
                                         {green}      (2,0,31,0),
                                         {cyan}       (3,0,31,31),
                                         {red}        (4,31,0,0),
                                         {magenta}    (5,31,0,31),
                                         {brown}      (6,31,15,0),
                                         {lightgray}  (7,31,31,31),
                                         {darkgray}   (56,15,15,15),
                                         {lightblue}  (57,0,0,63),
                                         {lightgreen} (58,0,63,0),
                                         {lightcyan}  (59,0,63,63),
                                         {lightred}   (60,63,0,0),
                                         {lightmagenta}(61,63,0,63),
                                         {yellow}      (62,63,63,0),
		                         {white}       (63,63,63,63));


type unitate=record
     nume:string;
     benef91,benef92,benef93:longint;
     end;
     optiuni=array[1..10] of string;

var i,j,gd,gm,lungmax,xmi,ymi,color,xi,yi,nropt:integer;
    u:unitate;
    opt:optiuni;
    ch:char;
    numefis:string;
    fis:file of unitate;


procedure FONDU;

var wp:array[1..16,1..4] of integer;

begin

for i:=1 to 16 do begin
wp[i,1]:=pal[i,1];
wp[i,2]:=pal[i,2];
wp[i,3]:=pal[i,3];
wp[i,4]:=pal[i,4];
end;
for j:=0 to 13 do begin
for i:=2 to 16 do begin
if wp[i,2]>5 then dec(wp[i,2],6);
if wp[i,3]>5 then dec(wp[i,3],6);
if wp[i,4]>5 then dec(wp[i,4],6);
setrgbpalette(wp[i,1],wp[i,2],wp[i,3],wp[i,4]);
end;
end;
cleardevice;

end;

procedure PALREC;
begin
for i:=1 to 16 do begin
setpalette(i-1,pal[i,1]);
setrgbpalette(pal[i,1],pal[i,2],pal[i,3],pal[i,4]);
end;
end;


function data(x,y:integer;tip:byte):string;{0-sir,1-numar}

var s:string;
    ch:char;

begin
s:='';
repeat

if keypressed then ch:=readkey
              else ch:=#0;
if tip=0 then if (ch in ['A'..'Z','a'..'z']) or (ch=' ') or (ch='.') then
                                             begin
                                              inc(x,8);
                                              outtextxy(x,y,ch);
                                              s:=s+ch;
                                             end;
if tip=1 then if (ch>='0') and (ch<='9') then begin
                                                inc(x,8);
                                              outtextxy(x,y,ch);
                                              s:=s+ch;
                                              end;


until ch=#13;
data:=s;

end;



procedure windows(xi,yi,color:integer;numewin:string;nropt:byte;opt:optiuni);

var i:integer;

begin

lungmax:=0;
for i:=1 to nropt do if length(opt[i])>lungmax then lungmax:=length(opt[i]);
setfillstyle(1,color);
bar(xi,yi,xi+lungmax*15,yi+11*(nropt+1));
setcolor(getmaxcolor-color);
rectangle(xi+3,yi+3,xi+lungmax*15-3,yi+11*(nropt+1)-3);
setfillstyle(1,color);
settextjustify(1,2);
bar(xi+lungmax*15 div 2-12*length(numewin) div 2,yi,xi+lungmax*15 div 2+12*length(numewin) div 2,yi+10);
outtextxy(xi+lungmax*15 div 2,yi,numewin);
for i:=1 to nropt do outtextxy(xi+lungmax*15 div 2,yi+i*10,opt[i]);

end;


procedure creare;

begin

fondu;palrec;
opt[1]:='numele fisierului ?';opt[2]:='';
windows(xi,yi,blue,'CREARE FISIER',2,opt);

settextjustify(0,2);
numefis:=copy(data(xi+lungmax*15 div 2-40,yi+20,0),1,7)+'.dat';

assign(fis,numefis);
rewrite(fis);

fondu;palrec;
opt[1]:='creare fisier';opt[2]:='introducere unitati';opt[3]:='grafice';opt[4]:='terminare';
windows(xi,yi,red,'MENIU',4,opt);

end;

procedure introducere;

var a:unitate;
    err:integer;

begin

fondu;palrec;
opt[1]:='numele unitatii ?';opt[2]:='';
opt[3]:='beneficiu in ''91 ?';opt[4]:='';
opt[5]:='beneficiu in ''92 ?';opt[6]:='';
opt[7]:='beneficiu in ''93 ?';opt[8]:='';
windows(xi,yi,blue,'introducere',8,opt);

a.nume:=data(xi+lungmax*15 div 2-40,yi+20,0);
val(data(xi+lungmax*15 div 2-40,yi+40,1),a.benef91,err);
val(data(xi+lungmax*15 div 2-40,yi+60,1),a.benef92,err);
val(data(xi+lungmax*15 div 2-40,yi+80,1),a.benef93,err);
seek(fis,filesize(fis));
write(fis,a);

fondu;palrec;
opt[1]:='creare fisier';opt[2]:='introducere unitati';opt[3]:='grafice';opt[4]:='terminare';
windows(xi,yi,red,'MENIU',4,opt);

end;

procedure grafic;

var searchst,st:string;
    a:unitate;
    benefmax:longint;
    h:real;

begin

fondu;palrec;
opt[1]:='numele unitatii de cautat ?';opt[2]:='';
windows(xi,yi,blue,'grafice',2,opt);
searchst:=data(xi+lungmax*15 div 2-40,yi+20,0);
reset(fis);
while not eof(fis) do
begin
read(fis,a);
if a.nume=searchst then begin
                             fondu;palrec;
                             if a.benef91>a.benef92 then if a.benef91>a.benef93 then benefmax:=a.benef91
                                                                                 else benefmax:=a.benef93
                                                    else if a.benef92>a.benef93 then benefmax:=a.benef92
                                                                                 else benefmax:=a.benef93;

                             h:=200/benefmax;
                             setcolor(white);
                             line(0,getmaxy-12,getmaxx,getmaxy-12);
                             line(0,getmaxy-12,0,0);
                             setcolor(white);
                             settextjustify(1,2);
                             settextstyle(1,0,1);
                             outtextxy(getmaxx div 2,0,a.nume);
                             settextstyle(0,0,0);
                             settextjustify(0,2);

                             setcolor(lightred);
                             setfillstyle(2,lightred);
                             bar3d(1,getmaxy-13-round(a.benef91*h),100,getmaxy-13,30,topon);
                             setcolor(white);
                             outtextxy(10,getmaxy-10,'1991');
                             str(a.benef91,st);
                             outtextxy(1,getmaxy-13-round(a.benef91*h)-30,st);

                             setcolor(lightblue);
                             setfillstyle(6,lightblue);
                             bar3d(150,getmaxy-13-round(a.benef92*h),250,getmaxy-13,30,topon);
                             setcolor(white);
                             outtextxy(160,getmaxy-10,'1992');
                             str(a.benef92,st);
                             outtextxy(150,getmaxy-13-round(a.benef92*h)-30,st);

                             setcolor(lightgreen);
                             setfillstyle(10,lightgreen);
                             bar3d(300,getmaxy-13-round(a.benef93*h),400,getmaxy-13,30,topon);
                             setcolor(white);
                             outtextxy(310,getmaxy-10,'1993');
                             str(a.benef93,st);
                             outtextxy(300,getmaxy-13-round(a.benef93*h)-30,st);
                             repeat
                             until readkey=#13;

                             fondu;palrec;
                             opt[1]:='creare fisier';opt[2]:='introducere unitati';opt[3]:='grafice';opt[4]:='terminare';
                             windows(xi,yi,red,'MENIU',4,opt);
                             exit;
                             end;

end;

cleardevice;
opt[1]:='nu exista aceasta unitate !';opt[2]:='apasati enter pt. revenire';
windows(xi,yi,blue,'',2,opt);

repeat
until readkey=#13;

fondu;palrec;
opt[1]:='creare fisier';opt[2]:='introducere unitati';opt[3]:='grafice';opt[4]:='terminare';
windows(xi,yi,red,'MENIU',4,opt);

end;

BEGIN

gd:=vga;gm:=vgahi;initgraph(gd,gm,'c:\bin\tp7\bgi');

opt[1]:='creare fisier';
opt[2]:='introducere unitati';
opt[3]:='grafice';
opt[4]:='terminare';
color:=red;xi:=170;yi:=100;nropt:=4;
windows(xi,yi,red,'MENIU',4,opt);
xmi:=xi+lungmax*15 div 2;ymi:=yi+10;i:=1;

assign(fis,'unitati.dat');reset(fis);

repeat

if keypressed then ch:=readkey
              else ch:=#0;
case ch of
#72  : begin
       setcolor(getmaxcolor-color);
       outtextxy(xmi,yi+10*i,opt[i]);
       dec(i);
       if i<1 then i:=nropt;
       setcolor(black);
       outtextxy(xmi,yi+10*i,opt[i]);
       end;
#80  : begin
       setcolor(getmaxcolor-color);
       outtextxy(xmi,yi+10*i,opt[i]);
       inc(i);
       if i>nropt then i:=1;
       setcolor(black);
       outtextxy(xmi,yi+10*i,opt[i]);
       end;
#13  : case i of
       1:creare;
       2:introducere;
       3:grafic;
       4: begin
          close(fis);
          halt;
          end;
       end;
end;

until ch=#27;

END.
