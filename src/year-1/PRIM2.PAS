program arbore_partial_minim;

{ metoda Prim }

uses crt;

const nmax=100;

type oras = record
          nume:string;
          end;

var cost:array[1..nmax,1..nmax] of integer;
    col:array[1..nmax] of boolean;
    lin:array[1..nmax] of boolean;
    i,j,min,err,marcate,linie,coloana,cost_arb,nr_oras:integer;
    orase:array[1..nmax] of oras;
    manv,manv2,manv3:string;

procedure Citire_din_fisier;

var err,i,j,oras1,oras2:integer;
    manv,manv1,manv2:string;
    f:text;

begin

assign(f,'orase.dat');
reset(f);
readln(f,manv);
val(manv,nr_oras,err);
for i:=1 to nr_oras do
    for j:=1 to nr_oras do
        begin
        if i=j then cost[i,j]:=0;
        cost[i,j]:=maxint;
        end;

for i:=1 to nr_oras do
    begin
         readln(f,manv);
         orase[i].nume:=manv;
    end;
while not eof(f) do
      begin
           readln(f,manv);
           manv1:='';
           for i:=1 to length(manv) do
               case manv[i] of
               '-' : begin
                     for j:=1 to nr_oras do
                         if orase[j].nume=manv1 then oras1:=j;
                     manv1:='';
                     end;
               '=' : begin
                     for j:=1 to nr_oras do
                         if orase[j].nume=manv1 then oras2:=j;
                     manv1:='';
                     end;
                   else manv1:=manv1+manv[i];
               end;{case}
           val(manv1,cost[oras1,oras2],err);
           cost[oras2,oras1]:=cost[oras1,oras2];
       end;{end while}
close(f);
end;{procedure citire...}

procedure Algoritmul_prim;

begin

while marcate<sqr(nr_oras) do
      begin
           min:=maxint;
           for i:=1 to nr_oras do if lin[i] then begin
                                           for j:=1 to nr_oras do
                                           if not col[j] then if cost[i,j]<min then begin
                                                                                       min:=cost[i,j];
                                                                                       linie:=i;
                                                                                       coloana:=j;
                                                                                       end;
                                           end;
           writeln(orase[linie].nume,'-',orase[coloana].nume,':',min);
           col[coloana]:=true;
           inc(marcate,nr_oras);
           lin[coloana]:=true;
           inc(cost_arb,min);
      end;
writeln;
write('costul minim al arborelui este ',cost_arb);

end;

procedure Initializari;

begin

for i:=1 to nr_oras do
    begin
    lin[i]:=false;{liniile sint nemarcate}
    col[i]:=false;{coloanele sint nemarcate}
    end;
lin[1]:=true;{se marcheaza prima linie}
col[1]:=true;{se marcheaza prima coloana}
marcate:=nr_oras;
cost_arb:=0;

end;


BEGIN

clrscr;
citire_din_fisier;
initializari;
algoritmul_prim;
readln;

END.





