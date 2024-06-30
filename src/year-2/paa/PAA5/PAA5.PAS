PROGRAM
       PAA5_ARBORE_B;

USES
    CRT;

CONST
     N  = 2;
     NN = 4;

TYPE
    PPagina = ^Pagina;
    Nod_B  = RECORD
           cheie : integer;
           sup   : PPagina;
           count : integer;
           END;
    Pagina = RECORD
           index   : integer;
           p0      : PPagina;
           list    : array[1..NN] of Nod_B;
           END;

VAR
   q,Root  : PPagina;
   key     : char;
   temp    : integer;
   H       : boolean;
   Nod     : Nod_B;
   Compare : integer;
   Depth   : integer;
   Last    : PPagina;
   Aux     : PPagina;
   i       : integer;

PROCEDURE Cauta(Curent : PPagina;x : integer;var H : boolean);
 VAR
    s,d,k  : integer;

BEGIN
 if Curent=NIL then H := false
    else WITH Curent^ DO
           BEGIN
             s:=1; d:=index; {cautare binara}
             REPEAT
               k:=(s+d) DIV 2;
               inc(Compare,3);
               IF x<=list[k].cheie THEN d:=k-1;
               IF x>=list[k].cheie THEN s:=k+1;
             UNTIL d<s;
             inc(Compare);
             IF s-d>1 THEN begin H := true;Last := Curent; end
               ELSE
                 BEGIN {nodul nu e in aceasta pagina}
                   inc(Compare);
                   Last := Curent;
                   inc(Depth);
                   IF d=0 THEN
                       Cauta(p0,x,h)
                     ELSE Cauta(list[d].sup,x,h);
                 END
         end
END;

PROCEDURE Insert(x:integer; VAR a:PPagina; VAR h:boolean; VAR v:Nod_B);
    { cauta cheia x in arborele-b de radacina a; daca o gaseste
      incrementeaza controlul,altfel insereaza un nod cu cheia x si
      contor=1. daca un nod trebuie pasat spre un nivel interior,
      el este atribuit lui v; h:='arborele a a devenit mai inalt' }
VAR k,s,d:integer; q:PPagina; u:Nod_B;

PROCEDURE insereaza;
  VAR i:integer; b:PPagina;
  BEGIN {insereaza pe u in dreapta lui a^.e[r] }
    WITH a^ DO
      BEGIN
        IF index<nn THEN
            BEGIN
              index:=index+1; h:=false;
              FOR i:=index DOWNTO d+2 DO list[i]:=list[i-1];
              list[d+1]:=u
            END
          ELSE
            BEGIN {pagina a^ e plina; scindeaza pagina si
                    atribuie nodul median lui v}
              new(b);
              IF d<=n THEN
                  BEGIN
                    IF d=n THEN
                        v:=u                           {5.69}
                      ELSE
                        BEGIN
                          v:=list[n];
                          FOR i:=n DOWNTO d+2 DO list[i]:=list[i-1];
                          list[d+1]:=u
                        END;
                    FOR i:=1 TO n DO b^.list[i]:=a^.list[i+n]
                  END
                ELSE
                  BEGIN {insereaza pe u}
                    d:=d-n; v:=list[n+1];
                    FOR i:=1 TO d-1 DO b^.list[i]:=a^.list[i+n+1];
                    b^.list[d]:=u;
                    FOR i:=d+1 TO n DO b^.list[i]:=a^.list[i+n];
                  END;
              index:=n; b^.index:=n; b^.p0:=v.sup; v.sup:=b
            END
      END {WITH}
  END; {insereaza}

BEGIN {cauta cheia x in pagina a^; h:=fals}
  IF a=NIL THEN
      BEGIN {nodul cu cheia x nu este in arbore}
        h:=true;
        WITH v DO
          BEGIN
            cheie:=x; count:=1; sup:=NIL
          END
      END
    ELSE
      WITH a^ DO
        BEGIN
          s:=1; d:=index; {cautare binara}
          REPEAT
            k:=(s+d) DIV 2;
            IF x<=list[k].cheie THEN d:=k-1;
            IF x>=list[k].cheie THEN s:=k+1;
          UNTIL d<s;
          IF s-d>1 THEN {gasit}
              BEGIN
                list[k].count:=list[k].count+1; h:=false
              END
            ELSE
              BEGIN {nodul nu e in aceasta pagina}
                IF d=0 THEN
                    q:=p0
                  ELSE
                    q:=list[d].sup;
                Insert(x,q,h,u);
                IF h THEN insereaza
              END
        END
END; {cauta}


PROCEDURE NiceTree(Page : PPagina;x,y : integer);
 VAR
    i : integer;
BEGIN
 if Page<>NIL
    then begin
          NiceTree(Page^.p0,x-(Page^.index+1)*7,y+2);
          for i:=1 to Page^.index do
              begin
               NiceTree(Page^.List[i].Sup,x-(Page^.index+1)*7+i*14,y+2);
               gotoxy(x+i*3-3,y+1);write(Page^.List[i].cheie);
              end;
         end;
END;

PROCEDURE Vidare(Curent : PPagina);
 VAR
    i : integer;
BEGIN
 if Curent<>NIL
    then begin
          Vidare(Curent^.p0);
          for i:=1 to Curent^.index do Vidare(Curent^.List[i].sup);
          dispose(Curent);
         end;
END;

PROCEDURE Crescator(Curent : PPagina);
 VAR
    i : integer;
BEGIN
 if Curent<>NIL
    then begin
          Crescator(Curent^.p0);
          write(Curent^.List[1].cheie,' ');{tratare speciala pt primul nod!}
          Crescator(Curent^.List[1].sup);
          for i:=2 to Curent^.index do
              begin
               Crescator(Curent^.List[i].sup);
               write(Curent^.List[i].cheie,' ');
              end;
         end;
END;

PROCEDURE suprima(x:integer; VAR a:PPagina; VAR h:boolean);
 { cauta si suprima nodul cu cheia x din arborele-b cu radacina
   a. daca o pagina devine subdimensionata se incearca fie
   echilibrarea cu o pagina adiacenta (daca e posibil) fie contopirea.
   h:='pagina a este subdimensionata'}
 VAR i,k,s,d:integer; q:PPagina;

 PROCEDURE subdepasire(VAR c,a:PPagina; VAR s1:integer; VAR h:boolean);
   { a=pagina subdepasita; c=pagina stramos}
   VAR b:PPagina; i,k,mb,mc:integer;
   BEGIN
     mc:=c^.index; {h=true; a^.m=n-1}
     IF s1<mc THEN
         BEGIN { b:=pagina din dreapta lui a}
           s1:=s1+1;
           b:=c^.list[s1].sup; mb:=b^.index; k:=(mb-n+1) DIV 2;
           { k=nr. de noduri disponibile in pagina adiacenta b}
           a^.list[n]:=c^.list[s1]; a^.list[n].sup:=b^.p0;
           IF k>0 THEN
               BEGIN {muta k noduri din b in a }
                 FOR i:=1 TO k-1 DO a^.list[i+n]:=b^.list[i];
                 c^.list[s1]:=b^.list[k]; c^.list[s1].sup:=b;
                 b^.p0:=b^.list[k].sup; mb:=mb-k;
                 FOR i:=1 TO mb DO b^.list[i]:=b^.list[i+k];
                 b^.index:=mb; a^.index:=n-1+k; h:=false
               END
             ELSE
               BEGIN {contopeste paginile a si b}
                 FOR i:=1 TO n DO a^.list[i+n]:=b^.list[i];
                 FOR i:=s1 TO mc-1 DO c^.list[i]:=c^.list[i+1];
                 a^.index:=nn; c^.index:=mc-1  {Dispose(b)}
               END                                      {5.69}
         END
       ELSE
         BEGIN {b:=pagina din stinga lui a}
           IF s1=1 THEN b:=c^.p0 ELSE b:=c^.list[s1-1].sup;
           mb:=b^.index+1; k:=(mb-n) DIV 2;
           IF k>0 THEN
               BEGIN {muta k noduri din pagina b in a}
                 FOR i:=n-1 DOWNTO 1 DO a^.list[i+k]:=a^.list[i];
                 a^.list[k]:=c^.list[s1]; a^.list[k].sup:=a^.p0;
                 mb:=mb-k;
                 FOR i:=k-1 DOWNTO 1 DO a^.list[i]:=b^.list[i+mb];
                 a^.p0:=b^.list[mb].sup;
                 c^.list[s1]:=b^.list[mb]; c^.list[s1].sup:=a;
                 b^.index:=mb-1; a^.index:=n-1+k; h:=false;
               END
             ELSE
               BEGIN {contopire pagini a si b}
                 b^.list[mb]:=c^.list[s1]; b^.list[mb].sup:=a^.p0;
                 FOR i:=1 TO n-1 DO b^.list[i+mb]:=a^.list[i];
                 b^.index:=nn; c^.index:=mc-1  {Dispose(a)}
               END
         END
   END; {subdepasire}

PROCEDURE supr(VAR p:PPagina; VAR h:boolean);
 VAR q:PPagina; {a si k variabile globale}
 BEGIN
   WITH p^ DO
     BEGIN
       q:=list[index].sup;
       IF q<>NIL THEN
           BEGIN
             supr(q,h);
             IF h THEN subdepasire(p,q,index,h)
           END
         ELSE
           BEGIN
             p^.list[index].sup:=a^.list[k].sup; a^.list[k]:=p^.list[index];
             index:=index-1; h:=index<n
           END
     END
 END; {supr}

 BEGIN {suprima}
   IF a=NIL THEN
       BEGIN
         WriteLn('   cheia nu exista in arbore'); h:=false
       END
     ELSE
       WITH a^ DO
         BEGIN {cautare binara}
           s:=1; d:=index;
           REPEAT
             k:=(s+d) DIV 2;
             IF x<=list[k].cheie THEN d:=k-1;
             IF x>=list[k].cheie THEN s:=k+1;
           UNTIL s>d;
           IF d=0 THEN
               q:=p0
             ELSE
               q:=list[d].sup;
           IF s-d>1 THEN
               BEGIN {gasit; se sterge e[k]}
                 IF q=NIL THEN
                     BEGIN {a este o pagina terminala}
                       index:=index-1; h:=index<n;
                       FOR i:=k TO index DO list[i]:=list[i+1];
                     END
                   ELSE
                     BEGIN
                       supr(q,h);
                       IF h THEN subdepasire(a,q,d,h)
                     END
               END
             ELSE
               BEGIN
                 suprima(x,q,h);
                 IF h THEN subdepasire(a,q,d,h)
               END
         END
 END; {suprima}


PROCEDURE Meniu;
BEGIN
 clrscr;
 gotoxy(37,1);writeln('Arbori B');
 gotoxy(30,6);writeln('<V>idanjare arbore');
 gotoxy(30,7);writeln('<C>auta cheie');
 gotoxy(30,8);writeln('<A>dauga cheie');
 gotoxy(30,9);writeln('<S>uprima cheie');
 gotoxy(30,10);writeln('<L>istare ordonata');
 gotoxy(30,11);writeln('A<f>isare pe pagini');
 gotoxy(30,12);writeln('A<d>incimea arborelui,minim si maxim');
 gotoxy(30,14);writeln('E<x>it');
END;

BEGIN
 Meniu;
 Randomize;
 repeat
  if keypressed then key := readkey
     else key:= #0;
  case UPCASE(key) of
   'V' : begin
          clrscr;
          gotoxy(33,1);writeln('Vidanjare arbore');
          gotoxy(35,5);write('memorie inainte : ',memavail);
          Vidare(Root);
          Root := NIL;
          gotoxy(35,7);write('memorie dupa    : ',memavail);
          readln;
          Meniu;
         end;
   'C' : begin
          clrscr;
          gotoxy(33,1);writeln('Cautare in arbore');
          gotoxy(35,5);write('cheia de cautat : ');readln(temp);
          H := false;
          Compare := 0;Depth := 0;
          Last := NIL;
          Cauta(Root,temp,H);
          if H
             then begin
                   gotoxy(23,6);
                   writeln('Am gasit cheia la adincimea ',Depth,' facind ',Compare,' comparatii');
                  end
             else begin
                   gotoxy(35,6);
                   writeln('Nu am gasit cheia !');
                  end;
          gotoxy(28,7);writeln('Cheile ultimei pagini accesate : ');
          if Last<>NIL
             then begin
                   gotoxy(35-3*Last^.Index div 2,8);
                   for i:=1 to Last^.Index do write(Last^.List[i].cheie,' ');
                  end
             else begin
                   gotoxy(35,8);
                   writeln('Arbore vid !');
                  end;
          readln;
          Meniu;
         end;
   'A' : begin
          clrscr;
          gotoxy(33,1);writeln('Introducere in arbore');
          gotoxy(35,5);write('cheia de introdus : ');
          readln(temp);
          Insert(temp,Root,H,Nod);
          if h then
            begin {insereaza noua pagina de baza}
              q:=Root; new(Root);
              with Root^ do
                begin
                  index:=1; p0:=q; list[1]:=Nod;
                  gotoxy(32,6);write('Arborele a crescut in inaltime !');
                end;
            end;
          readln;
          Meniu;
         end;
   'S' : begin
          clrscr;
          gotoxy(35,1);writeln('Suprimare nod');
          gotoxy(35,5);write('Nodul de suprimat : ');readln(Temp);
          gotoxy(30,6);
          suprima(temp,root,h);
          IF h THEN
            BEGIN {pagina de baza s-a redus ca dimensiune}
              IF root^.index=0 THEN
                BEGIN
                  q:=root; root:=q^.p0
                  {Dispose(q)}
                END
            END;
          gotoxy(39,7);writeln('OK');
          readln;
          Meniu;
         end;
   'L' : begin
          clrscr;
          gotoxy(35,1);writeln('Afisare ordonata');
          gotoxy(1,5);
          Crescator(Root);
          readln;
          Meniu;
         end;
   'F' : begin
          clrscr;
          gotoxy(35,1);writeln('Afisare arbore NiceTree');
          NiceTree(Root,40,5);
          readln;
          Meniu;
         end;
   'D' : begin
          clrscr;
          gotoxy(27,1);writeln('Adincime arbore,Min si Max');
          Depth := 0;
          if Root<>NIL
             then begin
                   Aux := Root;
                   while Aux^.p0<>NIL do
                         begin
                          inc(Depth);
                          Aux := Aux^.p0;
                         end;
                   gotoxy(35,5);writeln('Minimul e ',Aux^.List[1].cheie);
                   Aux := Root;
                   while Aux^.List[Aux^.index].sup<>NIL do Aux := Aux^.List[Aux^.index].sup;
                   gotoxy(35,6);writeln('Maximul e ',Aux^.List[Aux^.index].cheie);
                  end;
          gotoxy(34,7);writeln('Adincimea e ',Depth);
          readln;
          Meniu;
         end;
  end;
 until (UPCASE(key)='X') or (key=#27);
END.