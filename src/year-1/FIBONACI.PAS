program fibonacci;
uses crt;
var n:integer;
function fib(k:integer):integer;
          begin
               if (k=0) or (k=1) then fib:=1
                                 else fib:=fib(k-1)+fib(k-2);
           end;
begin
clrscr;
write('numarul de iteratii ? ');read(n);
writeln('valoarea este ',fib(n));
readln;
readln;
end.