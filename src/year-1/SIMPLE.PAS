{Keep.PAS}

{ Example for Keep }

{$M $800,0,$800 }   { 2K stack, no heap }
{ This program causes a click each time
 a key is pressed.}
uses Crt, Dos;
const install:boolean=false;
var
  b1 : Procedure;
{$F+}
procedure HOOK1b; interrupt;
begin
  gotoxy(10,10);write('this intr is hooked $1b');
  b1;
end;
{$F-}
begin
if paramstr(1)='+r' then if install then begin
                                         gotoxy(1,1);
                                         writeln('resident already installed !')
                                         end
                              else
                              begin
                              gotoxy(1,1);
                              writeln('resident is installed');
                              install:=true;
                              GetIntVec($1b,@b1);
                              SetIntVec($1b,Addr(HOOK1b));
                              Keep(0); { Terminate, stay resident }
                              end;
if paramstr(1)='-r' then if install then
                                    begin
                                    setintvec($1b,@b1);
                                    install:=false;
                                    gotoxy(1,1);
                                    write('no resident exists now !');
                                    end;
end.
