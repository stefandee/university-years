program beneficiu;
{$I-}
uses graph,crt;

type unitate=record
     nume:string;
     benef91,benef92,benef93:longint;
     end;

var i,j:integer;
    u:unitate;
    num:string;
    ch:char;
    fis:file of unitate;

procedure MENIU;

begin
clrscr;
gotoxy(30,10);write('MENIU :');
gotoxy(30,12);write('<1> Creare fisier.');
gotoxy(30,13);write('<2> Introducere date in fisier.');
gotoxy(30,14);write('<3> Afisare grafic.');
gotoxy(30,16);write('ESC pentru terminare');
end;


procedure creare;

begin
clrscr;
assign(fis,'unitati.dat');
rewrite(fis);
if ioresult<>0 then begin
                    gotoxy(30,14);write('Fisierul nu poate fi deschis');
                    end
               else begin
                    gotoxy(30,14);write('Fisierul a fost deschis');
                    end;
repeat until readkey=#13;
meniu;
end;

procedure introducere;

var a:unitate;

begin
clrscr;
gotoxy(30,10);write('Introducere unitati in fisier');
seek(fis,filesize(fis));
delay(100);
gotoxy(30,12);write('numele unitatii ? ');read(a.nume);
gotoxy(30,13);write('beneficiul in 1991 ? ');read(a.benef91);
gotoxy(30,14);write('beneficiul in 1992 ? ');read(a.benef92);
gotoxy(30,15);write('beneficiul in 1993 ? ');read(a.benef93);
write(fis,a);
meniu;
end;

procedure grafic;

var searchst,st:string;
    a:unitate;
    benefmax:longint;
    h:real;
    gd,gm:integer;

begin
clrscr;
delay(100);
gotoxy(30,10);write('Afisare beneficii');
gotoxy(30,12);write('numele unitatii ?');
gotoxy(37,13);read(searchst);

gd:=detect;initgraph(gd,gm,'c:\bin\tp7\bgi');
reset(fis);
while not eof(fis) do
begin
read(fis,a);
if a.nume=searchst then begin
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

                             cleardevice;
                             closegraph;
                             meniu;
                             exit;
                             end;

end;

closegraph;
gotoxy(30,10);write('Unitatea cu acest nume nu exista !!!');
repeat until readkey=#13;
meniu;
end;


BEGIN

assign(fis,'unitati.dat');reset(fis);
meniu;

repeat

if keypressed then ch:=readkey
              else ch:=#0;
case ch of
'1'  : creare;
'2'  : introducere;
'3'  : grafic;
end;

until ch=#27;

close(fis);

END.
