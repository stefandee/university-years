program Generator_de_Partitii;

uses crt;

const Nr_Maxim = 8;


var Nr_Elemente : integer;
    i,j,k       : integer;
    stack       : array[1..100] of integer;
    sp          : integer;
    p2          : integer;
    sum         : integer;
    found       : boolean;
    nr_part     : integer;

function Putere2(p : integer) : integer;
 var i,prod : integer;
begin
 prod:=1;
 for i:=1 to p do prod:=prod*2;
 putere2:=prod;
end;

procedure ComBinari(N,P : integer);{Calculeaza combinari de N luate cite P}
 var sp : integer;

function continuare(k:integer):boolean;
var i:integer;
begin
 continuare:=true;
 for i:=1 to k-1 do if (stack[k]<=stack[i]) or (stack[k] and stack[i]<>0) then begin
                                       continuare:=false;
                                       exit;
                                       end;
end;

procedure GetBits(v : integer);
 var i : integer;
begin
 write('{');
 for i:=Nr_Elemente downto 0 do if putere2(i) and v=putere2(i) then write(i+1,' ');
 write('} ');
end;

procedure tipareste;
var i : integer;
    sum : integer;
begin
 sum:=0;
 for i:=1 to p do sum:=sum+stack[i];
 if sum=p2-1
    then begin
          inc(nr_part);
          write('Partitia nr.',nr_part,' : ');
          for i:=1 to p do GetBits(stack[i]);
          writeln;
         end;
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
 write('Cite elemente ? ');readln(Nr_Elemente);
 sp:=1;
 p2:=putere2(Nr_Elemente);
 nr_part:=0;
 for i:=1 to Nr_Elemente do Combinari(p2,i);
 readln;
end.




