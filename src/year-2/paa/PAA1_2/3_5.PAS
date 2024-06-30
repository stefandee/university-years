PROGRAM tema3_5;

USES
    CRT,DEFARB;

VAR
   s          : PString;
   F          : FILE;
   c          : char;
   Arb,EArb   : PArbore;

BEGIN
 clrscr;
 Arb := New(PArbore,Init);
 EArb := New(PArbore,Init);
 new(s);
 assign(F,'3-4.dat');
 reset(F,1);
 s^:='';
 repeat
  blockread(F,c,1);
  if c>' 'then s^:=s^+c
          else if s^<>''
               then begin
                     Arb^.Insert(s);
                     s^:='';
                    end;
 until eof(F);
 close(F);

 Arb^.WriteOrdonat(Arb^.Root);
 Arb^.Equilibrium(1,CntOrdonat,EArb);
 gotoxy(25,1);writeln('Arborele initial');
 Arb^.NiceTree(Arb^.Root,25,3);
 gotoxy(25,11);writeln('Arborele echilibrat');
 EArb^.NiceTree(EArb^.Root,25,13);
 readln;
END.