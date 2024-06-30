program inssort;
uses crt;
const n=15;
var i,j,com:integer;
    found:boolean;
    a:array[1..n] of integer;

begin
clrscr;
randomize;
writeln('metoda Insert Sort');
writeln;
for i:=1 to n do a[i]:=random(101)+1;
write('sirul initial este : ');
for i:=1 to n do write(a[i],' ');
writeln;
for i:=2 to n do
    begin
         j:=i;
         com:=a[i];
         while (j>1) and (a[j-1]>com) do
         begin
              a[j]:=a[j-1];
              dec(j);
         end;
         a[j]:=com;
     end;
write('sirul sortat  este : ');
for i:=1 to n do write(a[i],' ');
readln;
end.