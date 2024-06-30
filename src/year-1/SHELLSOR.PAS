program shellsort;
uses crt,dos;
const n=30000;
var i,j,pas,c:integer;
    h,m,s,ms,ms1,s1,m1:word;
    a:array[1..n] of integer;
begin
clrscr;
randomize;
for i:=1 to n do a[i]:=random(maxint)+1;
{for i:=1 to n do write(a[i],' ');}
writeln;
pas:=n div 2;
gettime(h,m,s,ms);
repeat
i:=1;
while i+pas<=n do
      begin
      if a[i]>a[i+pas] then begin
                            c:=a[i+pas];
                            a[i+pas]:=a[i];
                            a[i]:=c;
                            end;
      inc(i);
      end;
pas:=pas div 2;
{dec(pas);}
until pas=0;
gettime(h,m1,s1,ms1);
writeln('shellsort took ÷',(m1-m)*60+s1-s,' seconds');
readln;
{for i:=1 to n do write(a[i],' ');}
readln;
end.