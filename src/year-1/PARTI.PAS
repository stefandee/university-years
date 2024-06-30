program Parti;

uses crt;

const Nr_Maxim = 50;

var stack : array[1..Nr_Maxim] of integer;
    i     : integer;
    Nr_Elemente : integer;

procedure ComBinari(N,P : integer);{Calculeaza combinari de N luate cite P}

var sp : integer;

function continuare(k:integer):boolean;
var i:integer;
begin
continuare:=true;
for i:=1 to k-1 do if (stack[k]<=stack[i]) then begin
                                       continuare:=false;
                                       exit;
                                       end;
end;

procedure tipareste;
var i:integer;
begin
for i:=1 to p do write(stack[i],' ');
writeln;
end;


begin

stack[1]:=0;
sp:=1;
while sp>0 do
begin
while stack[sp]<n-p+sp do
begin
inc(stack[sp]);
if continuare(sp) then if sp=p then tipareste
                               else begin
                                    inc(sp);
                                    stack[sp]:=0;
                                    end;
end;
stack[sp]:=0;
dec(sp);
end;
end;


begin
clrscr;
write('Introduceti numarul de elemente al multimii : ');
readln(Nr_Elemente);
writeln('Partile multimii sint : ');
for i:=1 to Nr_Elemente do Combinari(Nr_Elemente,i);
readln;
end.