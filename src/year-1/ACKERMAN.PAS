program calcul_ackerman;
{$M 65520,0,0}

uses crt;

var m,n:integer;

function ack(m,n:integer):integer;
begin
if M=0 THEN ack:=n+1;
if n=0 then ack:=ack(m-1,1);
if (m<>0) and (n<>0) then ack:=ack(m-1,ack(m,n-1));
end;

BEGIN
clrscr;
write('valorile de calculat functia Ackermann ? ');
read(m,n);
writeln;
writeln('functia ia valoarea ',ack(m,n));
repeat until readkey=#13;
End.