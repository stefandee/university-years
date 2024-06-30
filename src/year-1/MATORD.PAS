program matord;

uses crt;

const n=4;
      m=4;
var mat:array[1..n,1..m] of integer;
    i,j,k:integer;

procedure coloane;

var ordonat:boolean;

begin

for i:=1 to m do
    begin
    ordonat:=true;
    for j:=1 to n-1 do
        begin
        if mat[j,i]>mat[j+1,i] then ordonat:=false;
        end;
    if ordonat then writeln('o coloana ordonata crescator este ',i);
    end;
end;

procedure linii;

var ordonat:boolean;

begin

for i:=1 to n do
    begin
    ordonat:=true;
    for j:=1 to m-1 do
        begin
        if mat[i,j]<mat[i,j+1] then ordonat:=false;
        end;
    if ordonat then writeln('o linie ordonata descrescator este ',i);
    end;
end;

procedure linii_identice;

var identic:boolean;

begin

for i:=1 to n do
    for k:=1 to n do
        begin
       if i<>k then begin
                     identic:=true;
                     for j:=1 to m do
                         if mat[i,j]<>mat[k,j] then identic:=false;
                     if identic then writeln('liniile ',i,' si ',k,' sint identice');
                     end;
                     end;
end;

begin

clrscr;
for i:=1 to n do
    for j:=1 to n do
        read(mat[i,j]);

coloane;
linii;
linii_identice;
readln;
readln;
end.