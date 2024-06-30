unit resurse;

INTERFACE
uses crt;

type profesii=(inginer,profesor,economist,medic,altceva);
     sexe=(masc,fem);
     data = record
          zi:1..31;
          luna:1..12;
          an:1900..2000;
          end;

     persoana = record
              nume,prenume:string;
              adresa:string[30];
              dn:data;
              profesia:profesii;
              sex:sexe;
              end;

var fis:file of persoana;

procedure FEREASTRA(XS,YS,XJ,YJ,COLOR:integer);
procedure INTRODUCERE;
procedure RECREARE;
procedure MENIU;
procedure CAUTARE;

implementation

procedure FEREASTRA;

begin

window(xs,ys,xj,yj);
textbackground(color);
clrscr;

end;



procedure INTRODUCERE;

var c:char;
    pers:persoana;

begin
clrscr;
fereastra(20,5,60,15,green);
gotoxy(1,1);
textcolor(white);
writeln('         INTRODUCERE PERSOANA');

with pers do
         begin
              write('nume : ');readln(nume);
              write('prenume : ');readln(prenume);
              write('adresa : ');readln(adresa);
              write('data nasterii (zi/luna/an) : ');
              with dn do readln(zi,luna,an);
              repeat
              write('profesia (I/P/E/M/A) : ');
              readln(c);
              until upcase(c) in ['I','P','E','M','A'];
              case upcase(c) of
              'I':profesia:=inginer;
              'P':profesia:=profesor;
              'E':profesia:=economist;
              'M':profesia:=medic;
              'A':profesia:=altceva;
              end;
              repeat
              write('sex (F/M) : ');readln(c);
              until upcase(c) in ['F','M'];
              if upcase(c)='M' then sex:=masc
                               else sex:=fem;

         end;
assign(fis,'agenda.dat');
reset(fis);
seek(fis,filesize(fis));
write(fis,pers);
close(fis);
window(1,1,80,25);
textbackground(black);
clrscr;
meniu;

end;

procedure RECREARE;
begin
assign(fis,'agenda.dat');
reset(fis);
close(fis);
end;

procedure MENIU;
begin
fereastra(20,5,40,15,red);
gotoxy(1,1);
writeln('       MENIU');
writeln('<1> RECREARE');
writeln('<2> INTRODUCERE');
writeln('<3> CAUTARE');
writeln;
writeln;
writeln('ESC <-> TERMINARE');
end;

procedure CAUTARE;

var pers:persoana;
    found:boolean;
    nume:string;
    i:integer;


begin

fereastra(20,5,50,15,green);
gotoxy(1,1);
writeln('        CAUTARE');
writeln('INTRODUCETI NUMELE ');write('(se poate folosi ?) : ');readln(nume);
fereastra(20,5,50,15,red);
gotoxy(1,1);
writeln('PERSOANELE SINT :');
assign(fis,'agenda.dat');
reset(fis);
while not eof(fis) do
      begin
           read(fis,pers);
           if length(nume)=length(pers.nume) then begin
                                          found:=true;
                                          for i:=1 to length(nume) do
                                          if (nume[i]<>'?') and (nume[i]<>pers.nume[i]) then found:=false;
                                          if found then begin
                                                        with pers do
                                                        begin
                                                        write(nume,' ',prenume);
                                                        if sex=masc then write(' nascut la ')
                                                                    else write(' nascuta la ');
                                                        write(dn.zi,'.',dn.luna,'.',dn.an);
                                                        write(' de profesie ');
                                                        case profesia of
                                                        inginer:write('inginer.');
                                                        profesor:write('profesor.');
                                                        economist:write('economist.');
                                                        medic:write('medic.');
                                                        altceva:write('altceva.');
                                                        end;
                                                        end;
                                                        end;
                                          end;
       end;

close(fis);
writeln;writeln;
if not found then writeln('NIMENI CU ACEST NUME !!!');
writeln('APASA ENTER PT REVENIRE');

repeat until readkey=#13;

window(1,1,80,25);
textbackground(black);
clrscr;
meniu;

end;

end.

