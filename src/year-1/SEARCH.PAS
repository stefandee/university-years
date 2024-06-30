program search;

uses crt;

const n=5;

var i,j,a:integer;
    x:array[1..n] of integer;

function ordonat:boolean;

begin
for i:=1 to n-1 do
if x[i]>x[i+1] then begin
                    ordonat:=false;
                    exit;
                    end;
ordonat:=true;
end;

function cautaneord:integer;

begin
for i:=1 to n do if x[i]=a then begin
                                cautaneord:=i;
                                exit
                                end;
cautaneord:=0;
end;

function cautaord(first,last:integer):integer;

var mid:integer;

begin
repeat
mid:=(first+last) div 2;
if x[mid]=a then begin
                 cautaord:=mid;
                 exit
                 end;
if x[last]=a then begin
                  cautaord:=last;
                  exit
                  end;
if x[first]=a then begin
                   cautaord:=first;
                   exit
                   end;
if x[mid]<a then first:=mid
            else last:=mid;
until (last-first)<=1;
cautaord:=0;
end;

begin

clrscr;
writeln('sirul x:');

for i:=1 to n do read(x[i]);
writeln('elementul de cautat');
read(a);
if ordonat then writeln('pozitia este : ',cautaord(1,n))
           else writeln('pozitia este : ',cautaneord);
readln;
readln;
end.
