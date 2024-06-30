program keys;
uses crt;
var c:char;
begin
clrscr;
repeat
if keypressed then begin
                   c:=readkey;
                   if c<>#0 then writeln(ord(c));
                   end
              else c:=#0;

until c=#27;
end.