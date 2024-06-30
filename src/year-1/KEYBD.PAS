program keybd;
uses crt;
var p,c:byte;
begin
clrscr;
repeat
c:=port[$60];
gotoxy(10,10);write('      ');write(c);
c:=port[$60];
gotoxy(10,11);write('      ');write(c);
if c=ord('q') then begin
                 gotoxy(20,20);
                 write('q pressed');
                 end;
until false;
end.