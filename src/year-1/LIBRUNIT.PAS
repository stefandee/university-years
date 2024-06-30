unit librunit;

interface

uses crt;

type carte = record
           nume:string[30];
           autor:string[100];
           comentariu:string;
           pagini:integer;
           impr:boolean;
           end;

var fis:file of carte;

procedure SUPR(xup,yup,xdown,ydown,col:integer);
procedure INTRODUCERE;
procedure MENIU;
procedure CAUTARE_NUME;
procedure CAUTARE_AUTOR;


implementation

procedure SUPR;

begin

window(xup,yup,xdown,ydown);
textbackground(col);
clrscr;

end;

procedure INTRODUCERE;

var c:carte;
    ch:char;

begin

clrscr;
supr(20,5,60,15,green);
gotoxy(1,1);
textcolor(white);
writeln('ACHIZITIE DE CARTE');

with c do
         begin
              write('nume ? ');readln(nume);
              write('autor ? ');readln(autor);
              write('comentariu ? ');readln(comentariu);
              write('pagini ?');readln(pagini);
              repeat
              write('imprumutata ? ');
              readln(ch);
              until (upcase(ch)='A') or (upcase(ch)='D');
         end;
assign(fis,'libraria.lib');
reset(fis);
seek(fis,filesize(fis));
write(fis,c);
close(fis);
supr(1,1,80,25,black);
meniu;

end;

procedure MENIU;

begin

supr(1,1,80,24,black);
supr(20,5,40,15,brown);
gotoxy(1,1);
writeln('       LIBRARIE ');
writeln('<I>NTRODUCERE');
writeln('CAUTARE DUPA <A>UTOR');
writeln('CAUTARE DUPA <N>UME');
writeln('<T>ERMINARE');
write('optiunea dv ? ');

end;

procedure CAUTARE_NUME;

var c:carte;
    found:boolean;
    nume:string;

begin

supr(20,5,50,15,red);
gotoxy(1,1);
writeln('        CAUTARE DUPA NUME ');
writeln('NUMELE CARTII ?');read(nume);
supr(20,5,50,15,red);
gotoxy(1,1);
writeln('CARTILE SINT :');
assign(fis,'libraria.lib');
reset(fis);
found:=false;
while not eof(fis) do
      begin
           read(fis,c);
           if nume=c.nume then begin
                               found:=true;
                               with c do writeln(nume,' de ',autor,',',pagini,' pagini ',comentariu);
                               end;
       end;

close(fis);
writeln;writeln;
if not found then writeln('Nu exista aceasta carte !');
writeln('Apasa orice tasta');
repeat until keypressed;
meniu;

end;

procedure CAUTARE_AUTOR;

var c:carte;
    found:boolean;
    autor:string;

begin

supr(20,5,50,15,red);
gotoxy(1,1);
writeln('CAUTARE DUPA AUTOR ');
writeln('NUMELE AUTORULUI ?');read(autor);
supr(20,5,50,15,red);
gotoxy(1,1);
writeln('CARTILE SINT :');
assign(fis,'libraria.lib');
reset(fis);
found:=false;
while not eof(fis) do
      begin
           read(fis,c);
           if autor=c.autor then begin
                               found:=true;
                               with c do writeln(nume,' de ',autor,',',pagini,' pagini ',comentariu);
                               end;
       end;

close(fis);
writeln;writeln;
if not found then writeln('Nu exista aceasta carte !');
writeln('Apasa orice tasta');
repeat until keypressed;
meniu;

end;

end.

