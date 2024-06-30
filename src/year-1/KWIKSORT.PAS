{$M 16384,0,655360}
program kwiksort;


uses crt,dos;

const n=10000;

var mat:array[1..n] of integer;
   l:integer;
   time,timei:longint;
   h1,h2,m1,m2,s1,s2,s100,s200:word;

procedure kwik(first,last:integer);

var i,j,t,inter:integer;

begin

i:=first;
j:=last;
inter:=mat[(first+last) div 2];

repeat
  while (mat[i]<inter) do
        begin
             i:=i+1;
        end;
  while (mat[j]>inter) do
        begin
             j:=j-1;
        end;
  if i<=j then begin
              t:=mat[i];
              mat[i]:=mat[j];
              mat[j]:=t;
              inc(i);
              dec(j);
              end;
until i>=j;
if j>first then begin
                kwik(first,j);
                end;

if i<last then begin
               kwik(i,last);
               end;
end;

begin

clrscr;
randomize;
write('sirul de sortat este: ');
for l:=1 to n do
    begin
         mat[l]:=random(maxint);{random(n*20)+1;}
         {write(mat[l],' ');}
    end;
writeln;
gettime(h2,m2,s2,s200);
timei:=h2*3600+m2*60+s2;
write(h2,':',m2,':',s2);
kwik(1,n);
gettime(h1,m1,s1,s100);
write(h1,':',m1,':',s1);
time:=h1*3600+m1*60+s1;
writeln;
{write('sirul sortat este: ');
for l:=1 to n do write(mat[l],' ');}
writeln('time is : ',time-timei);
readln;
end.

