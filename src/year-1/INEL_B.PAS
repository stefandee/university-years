program inel_boolean;

uses crt;

var stack:array[1..100] of byte;
    k,i,max:integer;{nr de biti pt un numar}

function power(val,exp:integer):integer;
var i,p:integer;
begin
p:=1;
for i:=1 to exp do p:=p*val;
power:=p;
end;{power}

function transf(pos:integer):integer;
var i,s:integer;
begin
s:=0;
for i:=0 to k-1 do s:=s+power(2,k-1-i)*stack[i+pos];
transf:=s;
end;{transf}

function cont(sp:integer):boolean;
var i:integer;
begin
cont:=true;
for i:=1 to sp-k-1 do if transf(i)=transf(sp-k) then begin
                                                     cont:=false;
                                                     exit;
                                                     end;
end;

procedure lant(sp:integer);
var i,j:integer;
    fnd1,fnd2:boolean;
begin
if sp=max then if (stack[max]=0) and (stack[max-1]=0) then begin
                                                           fnd1:=true;
                                                           for i:=1 to max-k do
                                                               begin
                                                               fnd2:=false;
                                                               for j:=1 to k do
                                                                   if transf(i)=j then fnd2:=true;
                                                               if not fnd2 then fnd1:=false;
                                                               end;
                                                           if fnd2 then begin
                                                                        for i:=1 to max-k+1 do
                                                                        write(stack[i]);
                                                                        write('...');
                                                                        readln;
                                                                        halt;
                                                                        end;
                                                           end
                                                      else
          else begin
               inc(sp);
               if cont(sp) then begin
                                stack[sp]:=0;
                                lant(sp);
                                end;
               if cont(sp) then begin
                                stack[sp]:=1;
                                lant(sp);
                                end;
               end;
end;


Begin
clrscr;
k:=5;
max:=power(2,k)+k-1;
for i:=1 to 100 do stack[i]:=0;
lant(k);
readln;
End.