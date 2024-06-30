program try;
uses crt;
var b:byte;
begin
b:=200;
repeat
inc(b);
gotoxy(1,1);
write(b);
delay(200);
until keypressed
end.