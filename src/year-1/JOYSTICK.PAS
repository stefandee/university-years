program x;
uses dos,crt;
var r:registers;
begin
clrscr;
repeat
r.ah:=$84;
r.dx:=1;
intr($15,r);
gotoxy(10,10);write(r.ax);
gotoxy(10,11);write(r.bx);
gotoxy(10,12);write(r.cx);
gotoxy(10,13);write(r.dx);

r.ah:=$84;
r.dx:=0;
intr($15,r);
gotoxy(10,14);write(r.al and 128,' ',r.al and 64,' ',r.al and 32);

gotoxy(10,15);write(port[$2f8]);

until readkey=#13;
end.