program lista;

uses crt;
{simplu inlantuita}

type  leg = ^nod;
      nod = record
          nr:integer;
          next:leg;
          end;
      convptr = record
              ofs:word;
              seg:word;
              end;
var p:leg;
    n:integer;
    ch:char;

procedure meniu;

begin
clrscr;
gotoxy(20,5);write('<1> Introducere in lista;');
gotoxy(20,6);write('<2> Afisarea listei;');
gotoxy(20,7);write('<3> Stergere;');
gotoxy(20,9);write('<4> Halt.');
end;



procedure introducere;
var n:integer;
    q,q1:leg;
    found:boolean;
begin
gotoxy(20,24);write('Valoarea nodului de introdus: ');readln(n);
gotoxy(20,24);write('                                         ');
if p=nil then begin
              new(p);
              p^.nr:=n;
              p^.next:=nil;
              end
         else begin
              q:=p;
              found:=false;
              while (q<>nil) and not found do
                    begin
                    if (q^.nr<=n) and (q^.next^.nr>=n) then begin
                                                          new(q1);
                                                          q1^.nr:=n;
                                                          q1^.next:=q^.next;
                                                          q^.next:=q1;
                                                          found:=true;
                                                          end;
                    q:=q^.next;
                    end;
                    if not found then begin
                                      new(q1);
                                      q1^.nr:=n;
                                      q1^.next:=p;
                                      p:=q1;
                                      end;
              end;

end;
procedure afisare;
var cnt,i:integer;
    q:leg;
begin
cnt:=0;
q:=p;
for i:=11 to 20 do
    begin
    gotoxy(20,i);
    delline;
    end;
if q=nil then begin
              gotoxy(20,11);
              delline;
              writeln('nimic in lista');
              exit;
              end;
while q<>nil do
      begin
           inc(cnt);
           gotoxy(20,10+cnt);writeln('nod ',cnt,' cu valoarea ',q^.nr,' la adresa ',convptr(p).ofs,':',convptr(p).seg);
           q:=q^.next;
      end;
gotoxy(20,10+cnt+1);writeln('                                              ');
end;

procedure stergere;
var q,q1:leg;
begin
if p=nil then begin
              gotoxy(20,11);writeln('nimic in lista');
              exit;
              end;
gotoxy(20,24);write('Valoarea in nodul de sters: ');readln(n);
gotoxy(20,24);write('                                   ');
q:=p;
while q<>nil do
begin
if q^.nr=n then begin
                if q=p then begin
                            p:=p^.next;
                            dispose(q);
                            exit;
                            end
                       else if q^.next=nil then begin
                                                q:=p;
                                                while q^.next^.next<>nil do q:=q^.next;
                                                q1:=q^.next;
                                                q^.next:=nil;
                                                dispose(q1);
                                                exit;
                                                end
                                            else begin
                                                 q1:=q^.next;
                                                 q^:=q1^;
                                                 dispose(q1);
                                                 exit;
                                                 end;
                end;
q:=q^.next;
end;


end;

begin

p:=nil;
meniu;
repeat
if keypressed then ch:=readkey
              else ch:=#0;
case ch of
'1' : begin
      introducere;
      afisare;
      end;
'2':afisare;
'3' : begin
      stergere;
      afisare;
      end;
end;
until ch='4';
end.