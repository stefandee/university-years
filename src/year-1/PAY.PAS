program pay;

uses crt;

const n7;

var maxim,valori,st:array[1..n] of integer;
    k,sum_prim:integer;

procedure typing;
var i:integer;
begin
for i:=1 to n do if st[i]<>-1 then write(st[i],' monede ');
writeln;
end;

function suc:boolean;
var s,i:integer;
begin
s:=0;
for i:=1 to n do if st[i]<>-1 then s:=s+valori[i]*st[i];
if s>sum_prim then suc:=false;
if s<sum_prim then suc:=true;
if s=sum_prim then begin
                   typing;
                   suc:=false;
                   end;
end;

begin
write('dati suma :');
read(sum_prim);
for k:=1 to n do
    begin
         write('valoare monedei ',k,' este :');
         read(valori[k]);
         maxim[k]:=sum_prim div valori[k];
         st[k]:=-1;
    end;
while k>0 do
      begin
           while st[k]<=maxim[k] do
                 begin
                      inc(st[k]);
                      if (suc) and (k<n) then begin
                                              inc(k);
                                              end;
                 end;
          st[k]:=0;
          dec(k);
     end;
readln;
end.