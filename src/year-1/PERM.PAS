program perm;

uses crt;

const n=4;

var st:array[1..n] of integer;
    k:integer;

function suc:boolean;
var i:integer;
begin
suc:=false;
for i:=1 to k-1 do if st[k]=st[i] then exit;
suc:=true;
end;

procedure typing;
var i:integer;
begin
write('o permutare este: ');
for i:=1 to n do write(st[i],' ');
writeln;
end;

begin

clrscr;
for k:=1 to n do st[k]:=0;
k:=1;
while k>0 do
      begin
           while st[k]<n do
                 begin
                      inc(st[k]);
                      if suc then if k=n then typing
                                         else inc(k);
                 end;
      st[k]:=0;
      dec(k);
      end;
readln;
end.

