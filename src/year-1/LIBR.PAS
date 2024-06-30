program librarie;

uses librunit,crt;

var opt:char;

begin

meniu;
assign(fis,'libraria.lib');
reset(fis);
close(fis);

repeat

if keypressed then opt:=readkey
              else opt:=#0;
case upcase(opt) of
'I': introducere;
'N': cautare_nume;
'A': cautare_autor;
end;

until upcase(opt)='T';

supr(1,1,80,24,black);

end.


