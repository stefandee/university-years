program divprim;

uses crt;

var n,m,i,divcnt:integer;

function prim(x:integer):boolean;
var j:integer;

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
i:=2;
divcnt:=0;
write('numarul este :');
read(n);
writeln('divizorii sint :');
m:=n;
repeat
      if prim(i) then if (n mod i=0) then begin
                                          inc(divcnt);
                                          n:=n div i;
                                          end
                                     else begin
                                          if divcnt<>0 then if divcnt=1 then writeln(i,' de cite ',divcnt,' o data')
                                                                        else writeln(i,' de cite ',divcnt,' ori');
                                          divcnt:=0;
                                          inc(i);
                                          end
                 else inc(i);
until (i=m div 2);
readln;
readln;

end.
