program FUNCTII_TIPURI;

{$F+}

uses crt;

type tipfunct=function(x:real):real;

var functii:array[1..5] of tipfunct;
    ch:char;
    err:integer;
    nf:byte;
    a,b:real;

function f1(x:real):real;
begin
f1:=sin(x);
end;

function f2(x:real):real;
begin
f2:=arctan(x);
end;

function f3(x:real):real;
begin
f3:=x;
end;

function f4(x:real):real;
begin
f4:=x*sin(x);
end;

function f5(x:real):real;
begin
f5:=x*sin(x)+cos(x);
end;

function integrare(a,b:real;f:tipfunct):real;

const n=100;

var h,s:real;
    i:integer;

begin

h:=(b-a)/n;
s:=0;
for i:=0 to n do s:=s+f(a+i*h);
integrare:=s*h;

end;

procedure meniu;
begin

clrscr;
gotoxy(30,11);
write('MENIU :');
gotoxy(30,13);
write('~T~ABELEAZA FUNCTIA');
gotoxy(30,14);
write('~I~NTEGEREAZA FUNCTIA');
gotoxy(30,16);
write('ESC PT. IESIRE');
gotoxy(55,25);
write('FUNCTIA CURENTA ESTE ',nf);

end;

procedure TABELARE;

var i,x,y:integer;
    pas:real;

begin

clrscr;
gotoxy(30,6);
write('CAPETELE INTERVALULUI ?');
gotoxy(35,7);
read(a,b);
gotoxy(30,8);
write('PASUL ?');
gotoxy(37,9);
read(pas);
x:=30;y:=10;
gotoxy(x,y);

writeln('ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄ¿');
gotoxy(x,y+1);
writeln('³     x       ³     f(x)    ³');
gotoxy(x,y+2);
writeln('ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄ´');
for i:=0 to 6 do
    begin
         gotoxy(x,y+3+i);
writeln('³             ³             ³');
    end;
gotoxy(x,i+y+3);
writeln('ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÙ');

y:=12;
while a<b do
begin
     inc(y);
     if y>18 then begin
                  gotoxy(55,25);
                  write('APASA ENTER PT CONTINUARE');
                  repeat until readkey=#13;
                  for i:=1 to 6 do begin
                                   gotoxy(x+5,12+i);
                                   write('     ');
                                   gotoxy(x+19,12+i);
                                   write('     ');
                                   end;
                  y:=13;
                  gotoxy(55,25);
                  write('                         ');
                  end;
     a:=a+pas;
     gotoxy(x+5,y);
     write(a:2:2);
     gotoxy(x+19,y);
     write(functii[nf](a):2:2);
end;

repeat until readkey=#13;

meniu;

end;  {procedure tabeleaza}

procedure INTEGREAZA;

begin
clrscr;
gotoxy(30,10);
writeln('LIMITELE DE INTEGRARE ?');
gotoxy(37,11);
read(a,b);
gotoxy(20,12);
write('VALOAREA INTEGERALEI PT. FUNCTIA ',nf,' ESTE ',integrare(a,b,functii[nf]):3:3);
repeat until readkey=#13;
meniu;

end;

BEGIN

functii[1]:=f1;functii[2]:=f2;functii[3]:=f3;functii[4]:=f4;functii[5]:=f5;
nf:=1;
meniu;

repeat
if keypressed then ch:=readkey
              else ch:=#0;

case upcase(ch) of
'T'      : tabelare;
'I'      : integreaza;
'1'..'5' : begin
           val(ch,nf,err);
           gotoxy(55,25);
           write('FUNCTIA CURENTA ESTE ',nf);
           end;

end;

until ch=#27;

end.