program partitie2;

uses crt;

var Nr_elemente : integer;
    stiva : array[1..100] of integer;
    sp : integer;
    nr_part : integer;

function Putere2(p : integer) : integer;
 var i,prod : integer;
begin
 prod:=1;
 for i:=1 to p do prod:=prod*2;
 putere2:=prod;
end;

procedure GetBits(v : integer);
 var i : integer;
begin
 write('{');
 for i:=Nr_Elemente downto 0 do if putere2(i) and v=putere2(i) then write(i+1,' ');
 write('} ');
end;

procedure Partitie(v : integer);
 var i,j : integer;
     found : boolean;
begin
 if v=putere2(Nr_elemente)-1
    then begin
          write('Partitia nr .',nr_part,': ');
          inc(nr_part);
          for i:=1 to sp-1 do GetBits(stiva[i]);
          writeln;
         end
    else begin
          for i:=1 to putere2(Nr_elemente) do
              begin
               if v and i=0
                  then begin
                        found:=true;
                        for j:=1 to sp-1 do if stiva[j]>i then found:=false;
                        if found then
                           begin
                            v:=v+i;
                            stiva[sp]:=i;
                            inc(sp);
                            partitie(v);
                            dec(sp);
                            v:=v-i;
                           end;
                       end;
              end;
         end;


end;

begin
clrscr;
write('Nr. de elemente ? ');readln(Nr_Elemente);
nr_part:=1;
sp:=1;
Partitie(0);
end.