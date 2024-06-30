program agenda;

uses crt,resurse;

var ch:char;

begin

textbackground(black);
textcolor(white);
clrscr;
meniu;

repeat

if keypressed then ch:=readkey
              else ch:=#0;
case ch of
'1': recreare;
'2': introducere;
'3': cautare;
end;

until ch=#27;

window(1,1,80,25);
textbackground(black);
textcolor(white);
clrscr;

end.

