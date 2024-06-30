program radicell;
{$F+}
uses crt;

type tipfunct=function(xi,a:real):real;

const n=10;
      eps=0.000000000001;

var a:real;

function NEWTON(xi,a:real):real;

begin
newton:=(xi+a/xi)/2;
end;

function RELAX(xi,a:real):real;

begin
relax:=xi+(a-xi*xi)/a
end;

function DEDEKIND(xi,a:real):real;

begin
dedekind:=(xi*xi*xi+3*a*xi)/(3*xi*xi+a);
end;

function radical(f:tipfunct;a:real):real;

var x0,xi,x1:real;
    iter:integer;

begin

x0:=a;iter:=0;

repeat

x1:=f(x0,a);
xi:=x0;
x0:=x1;
inc(iter);

until (iter>=n) or (abs(x0-xi)<eps);

radical:=x0;

end;

begin

clrscr;
write('radical din cit :');readln(a);
writeln('radical din ',a:3:3,' cu metoda NEWTON este ',radical(NEWTON,a):3:11);
writeln('radical din ',a:3:3,' cu metoda RELAXARE este ',radical(RELAX,a):3:11);
writeln('radical din ',a:3:3,' cu metoda DEDEKIND este ',radical(DEDEKIND,a):3:11);

repeat until readkey=#13;

end.

