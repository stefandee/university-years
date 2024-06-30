program arbore_partial_minim;

{ metoda Prim }
uses crt,graph;

const n=5;

var cost:array[1..n,1..n] of integer;
    mark:array[1..n,1..n] of boolean;
    lin:array[1..n] of boolean;
    i,j,min,marcate,linie,coloana,cost_arb:integer;

begin
clrscr;
writeln('introduceti costul muchiilor(100-nu exista drum):');
for i:=1 to n do
    for j:=i+1 to n do
        begin
             write('costul muchiei ',i,' ',j,' ? ');
             readln(cost[i,j]);
             cost[j,i]:=cost[i,j];
        end;
for i:=1 to n do for j:=1 to n do mark[i,j]:=false;{elementele sint nemarcate}
for i:=1 to n do
    begin
         mark[i,1]:=true;{se marcheaza prima coloana}
         lin[i]:=false;{liniile sint nemarcate}
         cost[i,i]:=0;
    end;
lin[1]:=true;{se marcheaza prima linie}
marcate:=n;
cost_arb:=0;
while marcate<>n*n do
      begin
           min:=101;
           for i:=1 to n do if lin[i] then begin
                                           for j:=1 to n do
                                           if not mark[i,j] then if cost[i,j]<min then begin
                                                                                       min:=cost[i,j];
                                                                                       linie:=i;
                                                                                       coloana:=j;
                                                                                       end;
                                           end;
           writeln(min,' ',linie,' ',coloana);
           for i:=1 to n do mark[i,coloana]:=true;
           inc(marcate,n);
           lin[coloana]:=true;
           inc(cost_arb,min);
      end;
writeln('costul minim este ',cost_arb);
readln;
end.





