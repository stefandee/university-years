PROGRAM CARS;

uses crt;

CONST cont=1000000.00;
      maxm=100;

type mas =record
        nume:string[15];
        cil,an:integer;
        pv,pa:real;
        exist:boolean;
        end;

var dep:array[1..maxm] of mas;
    cnt:integer;
    suma:real;
    c:char;

procedure initializare;
var i:integer;
begin
for i:=1 to maxm do dep[i].exist:=false;
suma:=cont;
cnt:=0;
end;

procedure menu;
begin
clrscr;
writeln('alegeti:');
writeln('a-achizitie');
writeln('v-vinzare');
writeln('i-inventar');
writeln('ESC pt iesire');
end;

function finder:integer;
var j:integer;
begin
finder:=0;
for j:=1 to maxm do if dep[j].exist=false then begin
                                               finder:=j;
                                               exit;
                                               end;
end;

function place:boolean;
var i:integer;
begin
place:=true;
for i:=1 to maxm do if dep[i].exist=false then begin
                                         place:=false;
                                         exit;
                                         end;
end;

procedure achizitie;
var omas:mas;
    i:integer;
begin
clrscr;
writeln('ACHIZITIE:');
if finder=0 then begin
                writeln('nu mai e loc in depozit');
                delay(1000);
                menu;
                exit;
                end;
write('pretul:');readln(omas.pa);
if omas.pa>suma then begin
                         writeln('nu sint bani');
                         delay(1000);
                         menu;
                         exit
                         end;
suma:=suma-omas.pa;
write('nume:');readln(omas.nume);
write('an fabr:');readln(omas.an);
write('cap cil:');readln(omas.cil);
write('pret vinzare:');readln(omas.pv);
omas.exist:=true;
dep[finder]:=omas;
menu;
{sortare}
end;

procedure vinzare;
var opt,i:integer;
begin
clrscr;
writeln('VINZARE');
if finder=0 then begin
                 writeln('nu exista nici o masina in stoc');
                 delay(1000);
                 menu;
                 exit;
                 end;
for i:=1 to maxm do
if dep[i].exist then writeln(i,':',dep[i].nume,'/',dep[i].an,'/',dep[i].cil,'/',
                             dep[i].pa:6:2,'/',dep[i].pv:6:2);
writeln('optiune:');
readln(opt);
if dep[opt].exist then begin
                       suma:=suma+dep[opt].pv;
                       writeln('masina a fost vinduta');
                       dep[opt].exist:=false;
                       delay(1000);
                       menu;
                       exit;
                       end
                  else begin
                       writeln('nu exista aceasta masina');
                       menu;
                       delay(1000);
                       exit;
                       end;

end;

procedure inventar;
var i:integer;
    profit:real;
begin
clrscr;
writeln('inventar');
profit:=0;
for i:=1 to maxm do
if dep[i].exist then begin
                     writeln(i,':',dep[i].nume,'/',dep[i].an,'/',dep[i].cil,'/',
                             dep[i].pa:6:2,'/',dep[i].pv:6:2);
                     profit:=dep[i].pv-dep[i].pa+profit;
                     end;
writeln('suma ramasa:',suma:10:2);
writeln('profitul:',profit:10:2);
readln;
menu;
end;

begin

initializare;
menu;
repeat
if keypressed then c:=readkey
              else c:=#0;
case c of
     'a':achizitie;
     'v':vinzare;
     'i':inventar;
end;
until c=#27;

end.