program maxim;
uses crt;
const p=0.01;
var a,b,c,max:real;
begin
clrscr;
write('capetele:');
read(a);
read(b);
if a>b then begin
            b:=c;
            b:=a;
            a:=c;
            end;
max:=0;
repeat
c:=(1+sin(a))/(1+cos(2*a));
if c>max then max:=c;
a:=a+p
until a>=b;
write('maximul este ',max:8:4);
readln;
readln;
end.