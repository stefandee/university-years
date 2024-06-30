program cutia_maimuta;

uses graph,crt;

type maimuta = record
             nume:string;
             nr:byte;
             pos:array[1..4,1..2] of byte;
             color:byte;
             end;

var f:text;
    i,j,err:integer;
    gd,gm:integer;
    tabla:array[1..5,1..4] of byte;
    manv,directie:string;
    m:array[1..10] of maimuta;
    nr:byte;
    nume:string;
    dirx,diry:integer;
    pos:byte;
    mf:maimuta;

function cauta:boolean;

var i:integer;

begin
cauta:=false;
for i:=1 to 10 do
if (m[i].nume=nume) and (m[i].nr=nr) then begin
                                          cauta:=true;
                                          pos:=i;
                                          end;
end;

function verifica_dir(dir:string):boolean;
begin
if dir='stanga' then begin
                     dirx:=0;
                     diry:=-1;
                     verifica_dir:=true;
                     exit;
                     end;
if dir='dreapta' then begin
                     dirx:=0;
                     diry:=1;
                     verifica_dir:=true;
                     exit
                     end;
if dir='sus' then begin
                     dirx:=-1;
                     diry:=0;
                     verifica_dir:=true;
                     exit
                     end;
if dir='jos' then begin
                     dirx:=1;
                     diry:=0;
                     verifica_dir:=true;
                     exit
                     end;
verifica_dir:=false;
end;

function muta:boolean;
var i,j,k:integer;

begin
for i:=1 to 4 do
    begin
         if (m[pos].pos[i,1]<>0) and (m[pos].pos[i,2]<>0)
            then begin
                 m[pos].pos[i,1]:=m[pos].pos[i,1]+dirx;
                 m[pos].pos[i,2]:=m[pos].pos[i,2]+diry;
         if (m[pos].pos[i,1]<1) or (m[pos].pos[i,1]>5)
            then begin
                 gotoxy(0,0);
                 write('mutare eronata');
                 repeat until readkey=#13;
                 halt;
                 end;
         if (m[pos].pos[i,2]<1) or (m[pos].pos[i,2]>4)
            then begin
                 gotoxy(0,0);
                 write('mutare eronata');
                 repeat until readkey=#13;
                 halt;
                 end;
                 end;
    end;

for i:=1 to 10 do
    if i<>pos then
    begin
         for j:=1 to 4 do
             for k:=1 to 4 do
                 if (m[pos].pos[j,1]<>0) and (m[i].pos[k,1]<>0) and
                    (m[pos].pos[j,2]<>0) and (m[i].pos[k,1]<>0)
                    then
                         if (m[pos].pos[j,2]=m[i].pos[k,2]) and
                            (m[pos].pos[j,1]=m[i].pos[k,1])
                            then begin
                                 muta:=false;
                                 exit;
                                 end;
     end;
muta:=true;
end;


procedure afiseaza;
var i,j:integer;
begin
clrscr;
gotoxy(30,10);
write('legenda (coduri pt maimute):');
for i:=1 to 10 do
    begin
    gotoxy(34,10+i);
    write(m[i].nume,' ',m[i].nr,' ',m[i].color);
    end;

for i:=1 to 10 do
    begin
{    setcolor(m[i].color);
    setfillstyle(1,m[i].color);}
    for j:=1 to 4 do
        if m[i].pos[j,1]<>0
           then begin
                gotoxy(10+m[i].pos[j,2],10+m[i].pos[j,1]);
                writeln(m[i].color);
                end;
    end;
end;



begin

for i:=1 to 10 do
    for j:=1 to 4 do
        begin
             m[i].pos[j,1]:=0;
             m[i].pos[j,2]:=0;
        end;

m[1].nume:='tamba';m[1].nr:=1;m[1].color:=1;
m[1].pos[1,1]:=1;m[1].pos[1,2]:=2;
m[1].pos[2,1]:=1;m[1].pos[2,2]:=3;
m[1].pos[3,1]:=2;m[1].pos[3,2]:=2;
m[1].pos[4,1]:=2;m[1].pos[4,2]:=3;

m[2].nume:='mamba';m[2].nr:=1;m[2].color:=2;
m[2].pos[1,1]:=3;m[2].pos[1,2]:=2;
m[2].pos[2,1]:=3;m[2].pos[2,2]:=3;


m[3].nume:='timba';m[3].nr:=1;m[3].color:=3;
m[3].pos[1,1]:=1;m[3].pos[1,2]:=1;
m[3].pos[2,1]:=2;m[3].pos[2,2]:=1;

m[4].nume:='timba';m[4].nr:=2;m[4].color:=4;
m[4].pos[1,1]:=1;m[4].pos[1,2]:=4;
m[4].pos[2,1]:=2;m[4].pos[2,2]:=4;

m[5].nume:='timba';m[5].nr:=3;m[5].color:=5;
m[5].pos[1,1]:=3;m[5].pos[1,2]:=1;
m[5].pos[2,1]:=4;m[5].pos[2,2]:=1;

m[6].nume:='timba';m[6].nr:=4;m[6].color:=6;
m[6].pos[1,1]:=3;m[6].pos[1,2]:=4;
m[6].pos[2,1]:=4;m[6].pos[2,2]:=4;

m[7].nume:='kimba';m[7].nr:=1;m[7].color:=7;
m[7].pos[1,1]:=4;m[7].pos[1,2]:=2;

m[8].nume:='kimba';m[8].nr:=2;m[8].color:=8;
m[8].pos[1,1]:=4;m[8].pos[1,2]:=3;

m[9].nume:='kimba';m[9].nr:=3;m[9].color:=9;
m[9].pos[1,1]:=5;m[9].pos[1,2]:=1;

m[10].nume:='kimba';m[10].nr:=4;m[10].color:=0;
m[10].pos[1,1]:=5;m[10].pos[1,2]:=4;

assign(f,'monkey.txt');
reset(f);


clrscr;
{gd:=detect;
initgraph(gd,gm,'g:\tp\bgi');}
gotoxy(30,10);
write('legenda (coduri pt maimute):');
for i:=1 to 10 do
    begin
    gotoxy(34,10+i);
    write(m[i].nume,' ',m[i].nr,' ',m[i].color);
    end;

afiseaza;
while not eof(f) do
      begin
           readln(f,manv);
           nume:=copy(manv,1,5);
           val(manv[7],nr,err);
           directie:=copy(manv,9,length(manv)-8);
           if not verifica_dir(directie)
              then begin
                   gotoxy(0,0);
                   write('data eronata');
                   repeat until readkey=#13;
                   halt;
                   end;
           if not cauta then begin
                             gotoxy(0,0);
                             write('data eronata');
                             repeat until readkey=#13;
                             halt;
                             end;
           if not muta then begin
                            gotoxy(0,0);
                            write('mutare eronata');
                            repeat until readkey=#13;
                            halt;
                            end;
           afiseaza;
           repeat until readkey=#13;
       end;
close(f);
end.


           





