PROGRAM
       AVL;

USES
    CRT;

TYPE
    ref = ^nod;
    nod = RECORD
           cheie       : longint;
	   contor      : integer;
	   stang,drept : ref;
	   ech         : shortint;
         end;

VAR
   key      : char;
   laux     : longint;
   echl     : boolean;
   dummy    : boolean;
   Root     : Ref;
   i        : integer;
   NrChei   : longint;
   NrEchl   : longint;
   RndTable : array[1..15000] of longint;

PROCEDURE InsertEchilibrat(x : longint; VAR p:Ref;
                           VAR h:BOOLEAN);
  VAR p1,p2:Ref; {h=fals}

  BEGIN
    IF p=NIL THEN
        BEGIN {cuvintul nu e arbore; se insereaza}
          new(p); h:=TRUE;
          WITH p^ DO
            BEGIN
              cheie:=x; contor:=1;
              stang:=NIL; drept:=NIL; ech:=0
            END
        END
      ELSE
        IF x<p^.cheie THEN
            BEGIN
              InsertEchilibrat(x,p^.stang,h);
              IF h THEN {ramura stinga a crescut in inaltime}
                CASE p^.ech OF
                  +1: BEGIN
                        p^.ech:=0; h:=FALSE
                      END;
                   0: p^.ech:=-1;
                  -1: BEGIN {reechilibrare}
                        echl := true;
                        p1:=p^.stang;
                        IF p1^.ech=-1 THEN
                            BEGIN {cazul 1 stinga}
                              p^.stang:=p1^.drept; p1^.drept:=p;
                              p^.ech:=0; p:=p1
                            END
                          ELSE
                            BEGIN { cazul 2 stinga}
                              p2:=p1^.drept;
                              p1^.drept:=p2^.stang;
                              p2^.stang:=p1;
                              p^.stang:=p2^.drept;
                              p2^.drept:=p;
                              IF p2^.ech=-1 THEN
                                  p^.ech:=+1
                                ELSE
                                  p^.ech:=0;
                              IF p2^.ech=1 THEN
                                  p1^.ech:=-1
                                ELSE
                                  p1^.ech:=0;
                              p:=p2
                            END;
                        p^.ech:=0; h:=FALSE
                      END
                END {CASE}
	    END
	  ELSE
	    IF x>p^.cheie THEN
		BEGIN
		  InsertEchilibrat(x,p^.drept,h);
		  IF h THEN {ramura dreapta a crescut in inaltime}
		    CASE p^.ech OF
		      -1: BEGIN
			    p^.ech:=0; h:=FALSE
			  END;
		       0: p^.ech:=+1;
		      +1: BEGIN {reechilibrare}
                            echl := true;
			    p1:=p^.drept;
			    IF p1^.ech=+1 THEN
				BEGIN {cazul 1 dreapta}
				  p^.drept:=p1^.stang; p1^.stang:=p;
				  p^.ech:=0; p:=p1
				END
			      ELSE
				BEGIN {cazul 2 dreapta}
				  p2:=p1^.stang;
				  p1^.stang:=p2^.drept;
				  p2^.drept:=p1;
				  p^.drept:=p2^.stang;
				  p2^.stang:=p;
				  IF p2^.ech=+1 THEN
				      p^.ech:=-1
				    ELSE
				      p^.ech:=0;
				  IF p2^.ech=-1 THEN
				      p1^.ech:=+1
				    ELSE
				      p1^.ech:=0;
				  p:=p2
				END;
			    p^.ech:=0; h:=FALSE
			  END
		    END {CASE}
		END
	      ELSE
		BEGIN
		  p^.contor:=p^.contor+1;
		END
  END; {InsertEchilibrat}

PROCEDURE SuprimaEchilibrat(x : longint; VAR p:Ref;
                           VAR h:BOOLEAN);
  VAR q:Ref; {h=fals}

  PROCEDURE Echilibru1(VAR p:Ref; VAR h:BOOLEAN);
    VAR p1,p2:Ref; e1,e2 : shortint;
    BEGIN {h=adevarat,ramura stinga a devenit mai mica}
      CASE p^.ech OF
        -1: p^.ech:=0;
         0: BEGIN
              p^.ech:=+1; h:=FALSE
            END;
        +1: BEGIN {reechilibrare}
              echl := true;
              p1:=p^.drept; e1:=p1^.ech;
              IF e1>=0 THEN
                  BEGIN {cazul 1 dreapta}
                    p^.drept:=p1^.stang; p1^.stang:=p;
                    IF e1=0 THEN
                        BEGIN
                          p^.ech:=+1; p1^.ech:=-1;
                          h:=FALSE
                        END
                      ELSE
                        BEGIN
                          p^.ech:=0; p1^.ech:=0
                        END;
                    p:=p1
                  END
                ELSE
                  BEGIN {cazul 2 dreapta}
                    p2:=p1^.stang; e2:=p2^.ech;
                    p1^.stang:=p2^.drept; p2^.drept:=p1;
                    p^.drept:=p2^.stang;
                    p2^.stang:=p;
                    IF e2=+1 THEN
                        p^.ech:=-1
                      ELSE
                        p^.ech:=0;
                    IF e2=-1 THEN
                        p1^.ech:=+1
                      ELSE
                        p1^.ech:=0;
                    p:=p2; p2^.ech:=0
                  END
            END
      END  {CASE}
    END; {Echilibru1}

  PROCEDURE Echilibru2(VAR p:Ref; VAR h:BOOLEAN);
    VAR p1,p2:Ref; e1,e2 : shortint;
    BEGIN {h=adevarat,ramura dreapta a devenit mai mica}
      CASE p^.ech OF
        +1: p^.ech:=0;
         0: BEGIN
              p^.ech:=-1; h:=FALSE
            END;
        +1: BEGIN  {reechilibrare}
              echl := true;
              p1:=p^.stang; e1:=p1^.ech;
              IF e1<=0 THEN
                  BEGIN {cazul 1 stinga}
                    p^.stang:=p1^.drept; p1^.drept:=p;
                    IF e1=0 THEN
                        BEGIN
                          p^.ech:=-1; p1^.ech:=+1;
                          h:=FALSE
                        END
                      ELSE
                        BEGIN
                          p^.ech:=0; p1^.ech:=0
                        END;
                    p:=p1
                  END
                ELSE
                  BEGIN {cazul 2 stinga}
                    p2:=p1^.drept; e2:=p2^.ech;
                    p1^.drept:=p2^.stang; p2^.stang:=p1;
                    p^.stang:=p2^.drept;
                    p2^.drept:=p;
                    IF e2=-1 THEN
                        p^.ech:=+1
                      ELSE
                        p^.ech:=0;
                    IF e2=+1 THEN
                        p1^.ech:=-1
                      ELSE
                        p1^.ech:=0;
                    p:=p2; p2^.ech:=0
                  END
            END
      END {CASE}
    END; {Echilibru2}

  PROCEDURE Suprima(VAR r:Ref; VAR h:BOOLEAN);
    BEGIN {h=false}
      IF r^.drept<>NIL THEN
          BEGIN
            Suprima(r^.drept,h);
            IF h THEN Echilibru2(r,h)
          END
        ELSE
          BEGIN
            q^.cheie:=r^.cheie;
            q^.contor:=r^.contor;
            r:=r^.stang; h:=TRUE
          END
    END; {Suprima}

  BEGIN {SuprimaEchilibrat}
    IF p=NIL THEN
        BEGIN
	  WRITE('cheia ',x,' nu e IN arbore'); h:=FALSE
	END
      ELSE
        IF x<p^.cheie THEN
            BEGIN
              SuprimaEchilibrat(x,p^.stang,h);
              IF h THEN Echilibru1(p,h)
            END
          ELSE
            IF x>p^.cheie THEN
                BEGIN
                  SuprimaEchilibrat(x,p^.drept,h);
                  IF h THEN Echilibru2(p,h)
                END
              ELSE
                BEGIN {suprima p^}
                  q:=p;
                  IF q^.drept=NIL THEN
                      BEGIN
                        p:=q^.stang; h:=TRUE
                      END
                    ELSE
                      IF q^.stang=NIL THEN
                          BEGIN
                            p:=q^.drept; h:=TRUE
                          END
                        ELSE
                          BEGIN
                            Suprima(q^.stang,h);
                            IF h THEN Echilibru1(p,h)
                          END;
                  {DISPOSE(q)}
                END
  END; {SuprimaEchilibrat}

procedure NiceTree(NodCrt : Ref;x,y : integer);
begin
 dec(x,3);inc(y);
 if NodCrt^.stang<>NIL then NiceTree(NodCrt^.stang,x,y);
 inc(x,3);dec(y);
 if NodCrt<>NIL then begin gotoxy(x,y);writeln(NodCrt^.cheie,'(',NodCrt^.contor,')');end;
 inc(x,3);inc(y);
 if NodCrt^.drept<>NIL then NiceTree(NodCrt^.drept,x,y);
 dec(x,3);dec(y);
end;

procedure Curatare(NodCrt : Ref);
begin
 if NodCrt^.stang<>NIL then Curatare(NodCrt^.stang);
 if NodCrt^.drept<>NIL then Curatare(NodCrt^.drept);
 if NodCrt<>NIL
    then begin
          dispose(NodCrt);
         end;
end;

procedure Meniu;
begin
 clrscr;
 gotoxy(35,1);writeln('Arbori AVL');
 gotoxy(30,5);writeln('<C> Initializare arbore');
 gotoxy(30,6);writeln('<I>nserare in arbore');
 gotoxy(30,7);writeln('<S>uprimare din arbore');
 gotoxy(30,8);writeln('<V>izualizarea arborelui');
 gotoxy(30,9);writeln('<P> Statistica');
 gotoxy(35,11);writeln('ESC iesire');
 gotoxy(1,22);writeln('Memory available : ',memavail);
end;

BEGIN
 meniu;
 Root := NIL;
 Root^.stang := NIL;
 Root^.drept := NIL;
 randomize;

 repeat
   if keypressed then key := readkey
      else key := #0;
   case UPCASE(key) of
    'C' : begin
           clrscr;
           gotoxy(30,1);writeln('Curatare arbore AVL');
           Curatare(Root);
           gotoxy(28,5);writeln('Arborele a fost curatat !');
           readln;
           meniu;
          end;
    'I' : begin
           clrscr;
           gotoxy(30,1);writeln('Introducere in arbore AVL');
           gotoxy(30,5);write('Introduceti cheia : ');
           readln(Laux);
           echl := false;dummy := false;
           InsertEchilibrat(Laux,Root,dummy);
           gotoxy(25,6);
           if echl then writeln('A fost necesara echilibrarea !')
              else writeln('NU a fost necesara echilibrarea !');
           readln;
           meniu;
          end;
    'S' : begin
           clrscr;
           gotoxy(30,1);writeln('Stergere din arbore AVL');
           gotoxy(30,5);write('Introduceti cheia : ');
           readln(Laux);
           echl := false;dummy := false;
           SuprimaEchilibrat(Laux,Root,dummy);
           gotoxy(25,6);
           if echl then writeln('A fost necesara echilibrarea !')
              else writeln('NU a fost necesara echilibrarea !');
           readln;
           meniu;
          end;
    'V' : begin
           clrscr;
           gotoxy(30,1);writeln('Vizualizare arbore AVL');
           NiceTree(Root,40,5);
           readln;
           meniu;
          end;
    'P' : begin
           clrscr;
           gotoxy(26,1);writeln('Analiza statistica a arborelui AVL');
           gotoxy(28,5);write('Introduceti numarul de chei : ');readln(NrChei);
           if NrChei>15000 then NrChei := 15000;
           gotoxy(18,6);writeln('Analiza pentru insertie...generez numere aleatoare');
           NrEchl := 0;
           for i:=1 to NrChei do
               begin
                RndTable[i] := random(MaxInt);
                gotoxy(32,7);writeln('Index ',i,' ,cheia ',RndTable[i]);
                dummy := false;echl := false;
                InsertEchilibrat(RndTable[i],Root,dummy);
                if echl then inc(NrEchl);
               end;
           gotoxy(20,7);
           writeln('Au fost necesare ',NrEchl,' echilibrari pentru ',NrChei,' chei (',(NrEchl*100) div NrChei,'%)');

           gotoxy(33,9);writeln('Analiza pentru suprimare...');
           NrEchl := 0;
           for i:=1 to NrChei do
               begin
                gotoxy(37,10);write('Index ',i,' ');
                dummy := false;echl := false;
                SuprimaEchilibrat(RndTable[i],Root,dummy);
                if Echl then inc(NrEchl);
               end;

           gotoxy(18,11);
           writeln('Au fost necesare ',NrEchl,' echilibrari pentru ',NrChei,' chei (',(NrEchl*100) div NrChei,'%)');
           readln;
           meniu;
          end;
   end;
 until key = #27;
END.
