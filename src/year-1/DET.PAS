program detm;

uses crt;

const n=3;

var st:array[1..n] of integer;
    mat:array[1..n,1..n] of integer;
    k,det,l,m:integer;

function suc:boolean;
var i:integer;
begin
suc:=false;
for i:=1 to k-1 do if st[k]=st[i] then exit;
suc:=true;
end;

procedure calcul;
var i,j,prod,ex:integer;
function power(x,n:integer):integer;
var i,p:integer;
begin
p:=1;
for i:=1 to n do p:=p*x;
power:=p;
end;
begin
ex:=0;
for i:=1 to n do for j:=i to n do if st[i]>st[j] then inc(ex);
prod:=1;
for i:=1 to n do prod:=prod*mat[i,st[i]];
det:=det+prod*power(-1,ex);
end;

begin

clrscr;
for k:=1 to n do st[k]:=0;
writeln('matricea este :');
for l:=1 to n do
for m:=1 to n do
begin
write('a[',l,',',m,']:');
readln(mat[l,m]);
end;
k:=1;
det:=0;
while k>0 do
      begin
           while st[k]<n do
                 begin
                      inc(st[k]);
                      if suc then if k=n then calcul
                                         else inc(k);
                 end;
      st[k]:=0;
      dec(k);
      end;
writeln('valoarea determinantului este :',det);
readln;
end.

