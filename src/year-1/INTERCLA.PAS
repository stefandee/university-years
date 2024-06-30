program intercls;

uses crt;

const n=5;

var x,y:array[1..n] of integer;
    z:array[1..2*n] of integer;
    i,j,l,k:integer;

begin

clrscr;
writeln('sirul x:');
for k:=1 to n do read(x[k]);
writeln('sirul y:');
for k:=1 to n do read(y[k]);

i:=1;j:=1;l:=1;
repeat
      if x[i]<=y[j] then begin
                        z[l]:=x[i];
                        inc(i);
                        end
                   else begin
                        z[l]:=y[j];
                        inc(j);
                        end;
      inc(l);
until (i>n) or (j>n);
if i>n then for k:=l to 2*n do z[l]:=y[j+l-k];
if j>n then for k:=l to 2*n do z[l]:=x[i+l-k];

for k:=1 to 2*n do write(z[k],' ');

readln;
readln;
end.
