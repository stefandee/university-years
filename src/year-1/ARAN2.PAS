program aranjari2;

uses crt;

var p,n:integer;
    sta:array[1..100] of integer;

procedure aran(k:integer);

var i:integer;

function cont(k:integer):boolean;
var i:integer;
begin
for i:=p downto k+1 do if sta[k]=sta[i] then begin
                                      cont:=false;
                                      exit;
                                      end;
cont:=true;
end;

procedure scrie;
var i:integer;
begin
for i:=1 to p do write(sta[i],' ');
writeln;
end;

begin
sta[k]:=0;
for i:=1 to n do
    begin
         sta[k]:=i;
         if cont(k) then if k=1 then scrie
                                else aran(k-1);
    end;
end;

begin
clrscr;
readln(n,p);
aran(p);
readln;
end.