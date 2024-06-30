program date_personale;

uses crt;

const nr_pers=1;

type profesii=(inginer,profesor,economist,medic,altceva);
     sexe=(masc,fem);
     data = record
          zi:1..31;
          luna:1..12;
          an:1900..2000;
          end;

     persoana = record
              nume,prenume:string[10];
              adresa:string[30];
              data_nastere:data;
              nr_copii:byte;
              profesia:profesii;
              salar:real;
              impozit:real;
              sex:sexe;
              end;

var persoane:array[1..nr_pers] of persoana;
    i:integer;
    c:char;
    b:byte;

begin

clrscr;

for i:=1 to nr_pers do
    with persoane[i] do
         begin
              write('nume,prenume : ');readln(nume,prenume);
              write('adresa : ');readln(adresa);
              write('data nasterii (zi/luna/an) : ');
              with data_nastere do readln(zi,luna,an);
              write('numar de copii : ');readln(nr_copii);
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
              write('salariul : ');readln(salar);
              impozit:=20*salar/100;
              repeat
              write('sex (F/M) : ');readln(c);
              until upcase(c) in ['F','M'];
              if upcase(c)='M' then sex:=masc
                               else sex:=fem;

         end;
clrscr;
repeat
write('persoana ? (0 pt terminare )');readln(b);
if (b>0) and (b<=nr_pers) then begin
                          clrscr;
                          with persoane[b] do
                               begin
                                    with data_nastere do
                                    write(nume,' ',prenume,' e nascut in ',
                                    zi,'.',luna,'.',an,' si muncind ca ');
                                    case profesia of
                                    inginer:write('inginer ');
                                    profesor:write('profesor ');
                                    economist:write('economist ');
                                    medic:write('medic ');
                                    altceva:write('nu se stie ce ');
                                    end;
                                    write('obtine ',salar:10:2,' lei cu impozit de ',
                                    impozit:10:2,'lei .');
                              end;
                         readln;
                         clrscr;
                         end;
until b=0;

readln;
end.



