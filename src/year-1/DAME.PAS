program dame;

uses crt;

const n=4;

var st:array[1..n] of integer;
    k:integer;

function suc:boolean;
var i:integer;
begin
suc:=false;
for i:=1 to k-1 do if (((abs(st[k]-st[i])=abs(i-k)) or (st[k]=st[i]))) and (k<>i) then exit;
suc:=true;
end;

function solution:boolean;
var i:integer;
begin
solution:=false;
for i:=1 to n do if st[i]=0 then exit;
solution:=true;
end;

procedure typing;
var i:integer;
begin
for i:=1 to n do writeln('dama ',i,' linia ',i,' coloana ',st[i]);
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
                        else begin
                             inc(k);
                             st[k]:=0;
                             end;
     end;
     st[k]:=0;
     dec(k);
     end;

readln;
end.

