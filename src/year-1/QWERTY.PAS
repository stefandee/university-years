program x;
uses crt;
begin
clrscr;
repeat
if keypressed then write(ord(readkey));
until 1=0;
end.