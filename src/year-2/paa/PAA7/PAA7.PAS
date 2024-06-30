PROGRAM
       TRIE_TREES;

USES
    CRT,DOS;

TYPE
    PNodAR = ^NodAR;
     NodAR = array['A'..'['] of PNodAR;

VAR
   Root   : PNodAR;
   aux    : string;
   c,key  : char;
   i      : integer;
   numar  : longint;
   min    : integer;
   max    : integer;
   mincuv : string;
   maxcuv : string;
   found  : boolean;

procedure Initializare(var Nod:NodAR);
  var c:char;
  begin
    for c:='A' to '[' do Nod[c]:=nil
  end;

procedure Atribuie(var Nod:NodAR; c:char;
                   p:PNodAR);
  begin
    Nod[c]:=p
  end;

function Valoare(var Nod:NodAR; c:char)
                :PNodAR;
  begin
    Valoare:=Nod[c]
  end;

procedure NodNou(var Nod:NodAR; c:char);
  begin
    new(Nod[c]);
    Initializare(Nod[c]^)
  end;

function One(Nod : NodAR) : boolean;
 var
    c : char;
    i : integer;
begin
 i := 0;
 One := true;
 for c:='A' to '[' do
     if Nod[c] <> NIL
        then begin
              inc(i);
              if i>1 then begin One := false;break;end
             end;
end;

procedure Adauga(x : String;var cuvinte : PNodAR);
var i : integer;
    t : PNodAR;
begin
  i:=1;
  t:=cuvinte;
  while x[i]<>'[' do
    begin
      if Valoare(t^,UPCASE(x[i]))=nil then NodNou(t^,UPCASE(x[i]));
      t:=Valoare(t^,UPCASE(x[i]));
      i:=i+1
    end;
  Atribuie(t^,'[',t);
end;

procedure Listare(Crt : PNodAR;c : string);
 var
    i : char;
begin
 for i:='A' to 'Z' do
     if Crt^[i]<>NIL then Listare(Crt^[i],c+i);
 if Crt^['[']<>NIL then writeln(c);
end;

procedure Cauta(Crt : PNodAR;c : string;src : string);
 var
    i : char;
begin
 for i:='A' to 'Z' do
     if Crt^[i]<>NIL then Cauta(Crt^[i],c+i,src);
 if Crt^['[']<>NIL then if c=src then begin gotoxy(30,6);writeln('Am gasit cuintul ',c);found:=true;end;
end;

procedure Prefix(Crt : PNodAR;c : string);
 var
    i   : integer;
    t   : PNodAR;
    j   : char;
begin
 t := Crt;
 for i:=1 to length(c) do
     for j:='A' to 'Z' do if Crt^[j]<>NIL then if c[i]=j then begin Crt := Crt^[j];break;end;
 if Crt<>t then Listare(Crt,c);
end;

procedure NumarCuvinte(Crt : PNodAR;c : string;var numar : longint);
 var
    i : char;
begin
 for i:='A' to 'Z' do
     if Crt^[i]<>NIL then NumarCuvinte(Crt^[i],c+i,numar);
 if Crt^['[']<>NIL then inc(numar);
end;

function Primul(Crt : PNodAR) : string;
 var
    i : char;
    c : string;
begin
 c:='';
 for i:='A' to 'Z' do if Crt^[i]<>NIL then begin Crt := Crt^[i];c:=c+i;i:=#64;end;
 Primul := c;
end;

function Ultimul(Crt : PNodAR) : string;
 var
    i : char;
    c : string;
begin
 c:='';
 for i:='Z' downto 'A' do if Crt^[i]<>NIL then begin Crt := Crt^[i];c:=c+i;i:=#91;end;
 Ultimul := c;
end;

procedure Minim(Crt : PNodAR;c : string);
 var
    i : char;
begin
 for i:='A' to 'Z' do
     if Crt^[i]<>NIL then Minim(Crt^[i],c+i);
 if Crt^['[']<>NIL
    then if length(c)<min then begin min := length(c);mincuv := c;end;
end;

procedure Maxim(Crt : PNodAR;c : string);
 var
    i : char;
begin
 for i:='A' to 'Z' do
     if Crt^[i]<>NIL then Maxim(Crt^[i],c+i);
 if Crt^['[']<>NIL
    then if length(c)>max then begin max := length(c);maxcuv := c;end;
end;

procedure Sterge(x : string;Nod : PNodAR);
 var
    i,a   : integer;
    aux,t : PNodAR;
    c     : char;
begin
 i   := 1;
 a   := 1;
 aux := Nod;
 t   := Nod;

 while (Nod^[x[i]] <> NIL) and (i<=length(x)) do
       begin
        if not One(Nod^)
           then begin
                 aux := Nod;
                 a:=i;
                end;
        Nod := Nod^[x[i]];
        inc(i);
       end;

 if a<length(x)
    then begin
          nod := aux^[x[a]];
          aux^[x[a]] := nil;
          aux := nod;
          inc(a);
          while x[a] <> '[' do
                begin
                 nod := aux^[x[a]];
                 dispose(aux);
                 aux := nod;
                 inc(a);
                end;
         end;
end;

procedure Meniu;
begin
 clrscr;
 gotoxy(30,1);writeln('Dictionar-TrieTrees cu tablouri');
 gotoxy(32,5);writeln('<V>ideaza dictionarul');
 gotoxy(34,6);writeln('<A>dauga cuvint û');
 gotoxy(34,7);writeln('<S>terge cuvint');
 gotoxy(35,8);writeln('<C>auta cuvint û');
 gotoxy(33,9);writeln('<L>istare dictionar û');
 gotoxy(30,10);writeln('Listare dupa <p>refix litera û');
 gotoxy(35,11);writeln('<I>nformatii û');
 gotoxy(38,13);writeln('E<x>it');
 gotoxy(1,24);write(memavail);
end;

BEGIN
 Meniu;
 new(Root);Initializare(Root^);
 {for key:='A' to '[' do NodNou(Root^,key);}
 repeat
  if keypressed then key := readkey
     else key := #0;
  case UPCASE(key) of
   'V' : begin
         end;
   'A' : begin
          clrscr;
          gotoxy(31,1);writeln('Introducere in arbore');
          gotoxy(30,5);write('Cuvintul : ');readln(aux);
          aux := aux+'[';
          Adauga(aux,Root);
          gotoxy(39,6);writeln('OK');
          readln;
          Meniu;
         end;
   'S' : begin
          clrscr;
          gotoxy(31,1);writeln('Suprimare din arbore');
          gotoxy(30,5);write('Cuvintul : ');readln(aux);
          for i:= 1 to length(aux) do aux[i]:=UPCASE(aux[i]);
          found := false;
          Cauta(Root,'',aux);
          gotoxy(32,5);
          if found then Sterge(aux+'[',Root)
             else writeln('Nu am gasit cuvintul!');
          readln;
          Meniu;
         end;
   'C' : begin
          clrscr;
          gotoxy(31,1);writeln('Listare dictionar');
          gotoxy(25,5);write('Cuvintul de cautat :');readln(aux);
          for i:= 1 to length(aux) do aux[i]:=UPCASE(aux[i]);
          Cauta(Root,'',aux);
          readln;
          Meniu;
         end;
   'L' : begin
          clrscr;
          gotoxy(31,1);writeln('Listare dictionar');
          Listare(Root,'');
          readln;
          Meniu;
         end;
   'P' : begin
          clrscr;
          gotoxy(30,1);writeln('Listare dupa prefix');
          gotoxy(33,5);write('Prefixul :');readln(aux);
          for i:= 1 to length(aux) do aux[i]:=UPCASE(aux[i]);
          Prefix(Root,aux);
          readln;
          Meniu;
         end;
   'I' : begin
          clrscr;
          gotoxy(30,1);writeln('Informatii despre dictionar');
          numar := 0;
          gotoxy(30,5);NumarCuvinte(Root,'',numar);write('Numarul de cuvinte : ',numar);
          gotoxy(28,6);writeln('Primul cuvint : ',Primul(Root));
          gotoxy(27,7);writeln('Ultimul cuvint : ',Ultimul(Root));
          min := 20000;max := -1;mincuv := '';maxcuv := '';
          Minim(Root,c);Maxim(Root,c);
          gotoxy(26,8);writeln('Cuvintul minim e : ',mincuv,'(',min,')');
          gotoxy(26,9);writeln('Cuvintul maxim e : ',maxcuv,'(',max,')');
          readln;
          Meniu;
         end;
  end;
 until UPCASE(key)='X';
 clrscr;
END.