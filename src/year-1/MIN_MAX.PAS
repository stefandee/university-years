program min_max;

uses crt;

const nmax=1000;

var a:array[1..nmax] of integer;
    n,i:integer;
    count,min,max:integer;

procedure cauta(l,h:integer;var min,max:integer);
var min1,max1,min2,max2:integer;
begin
if h<=l+1 then begin
               if a[l]<a[h] then begin
                                 min:=a[l];
                                 max:=a[h];
                                 {if a[l]<min then min:=a[l];
                                 if a[h]>max then max:=a[h];}
                                 inc(count);
                                 end
                            else begin
                                 min:=a[h];
                                 max:=a[l];
                                 {if a[l]>max then max:=a[l];
                                 if a[h]<min then min:=a[h];}
                                 inc(count);
                                 end;
               end
         else begin
              cauta(l,(l+h) div 2,min1,max1);
              cauta((l+h) div 2+1,h,min2,max2);
              if max2>max1 then max:=max2
                           else max:=max1;
              if min2<min1 then min:=min2
                           else min:=min1;
              inc(count,2);
              end;
end;

begin
clrscr;
randomize;
write('cite numere ? ');
readln(n);
writeln('numerele generate aleator sint :');
for i:=1 to n do
    begin
    a[i]:=random(1000);
    write(a[i],' ');
    end;
writeln;
max:=-21000;
min:=21000;
count:=0;
cauta(1,n,min,max);
writeln('minimul e ',min,' si maximul e ',max,' ;s-au facut ',count,' comparatii.');
readln;
end.
for i:=1
