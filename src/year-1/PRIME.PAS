program prime;
uses crt;
var n,j,i,x,primcnt:integer;
function prim(x:integer):boolean;

         begin
              for j:=2 to round(sqrt(x)) do
                  if x mod j=0 then begin
                                     prim:=false;
                                     exit;
                                     end;
              prim:=true;
        end;
begin
clrscr;
 read(n);
 primcnt:=0;
 for i:=1 to n do
     begin
          read(x);
          if prim(x) then inc(primcnt);
     end;
 writeln('gasit ', primcnt ,' valori prime');
end.