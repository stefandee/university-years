program generare_aranjari;

uses crt;

const nmax=100;

var p,sp:integer;
    st:string;
    sta:array[1..nmax] of integer;


procedure tipareste;
var i:integer;
begin
for i:=1 to p do write(st[sta[i]],' ');
writeln;
end;


procedure perm(k:integer);

var i,x:integer;
begin
if k=1 then tipareste
       else begin
            perm(k-1);
            for i:=1 to k-1 do
                begin
                     x:=sta[i];
                     sta[i]:=sta[k];
                     sta[k]:=x;
                     perm(k-1);
                     x:=sta[i];
                     sta[i]:=sta[k];
                     sta[k]:=x;
                end;{for}
           end;{else}
end;


procedure aranjari(p:integer);

function continuare(k:integer):boolean;
var i:integer;
begin
continuare:=true;
for i:=1 to k-1 do if (sta[k]<=sta[i])  then begin
                                       continuare:=false;
                                       exit;
                                       end;
end;

begin
{se genereaza permutari-recursiv de combinari-backtrack nerecursiv}
sta[1]:=0;
sp:=1;
while sp>0 do
begin
while sta[sp]<length(st)-p+sp do
begin
inc(sta[sp]);
if continuare(sp) then if sp=p then perm(p)
                               else begin
                                    inc(sp);
                                    sta[sp]:=0;
                                    end;
end;
sta[sp]:=0;
dec(sp);
end;

end;





begin
clrscr;
write('sirul ?');readln(st);
write('nr pt aranjari ?');readln(p);
if p>length(st) then begin
                     writeln('Imposibil !!!');
                     halt(0);
                     end;
aranjari(p);
end.
