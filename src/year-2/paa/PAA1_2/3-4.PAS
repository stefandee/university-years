PROGRAM tema3_4;

USES
    CRT;

TYPE
    PString = ^String;
   PNod = ^Nod;
    Nod = record
        info       : PString;
        count      : integer;
        left,right : PNod;
        end;

  PArbore = ^Arbore;
   Arbore = object
          Root : PNod;
          Depth : integer;
          public
           constructor Init;
           procedure   Insert(Info : PString);
           procedure   Ino(Crt : PNod);
           procedure   Action(Crt : Pnod);
           procedure   NiceTree(crt : PNod;x,y : integer);
           procedure   Adincime(crt : PNod;CrtLevel : integer);
           procedure   Frunze(crt : PNod);
           procedure   Familie(crt : PNod;info : PString);
           function    Search(Info : PString;Crt : PNod) : PNod;
           function    Level(info : PString;Crt : PNod;lcount : integer) : integer;
           procedure   SupriMin(var crtnod : PNod);
           function    Suprima(crt : PNod;info : PString) : PNod;
           destructor  Done;
          private
           function    RInsert(Info : PString;Crt : PNod) : PNod;
           function    Supred(crt : PNod;p : PNod) : PNod;
          end;

constructor Arbore.Init;
begin
 Root := NIL;Depth := 0;
end;

procedure Arbore.Insert;
var crt,aux : PNod;
begin
 Root := RInsert(Info,Root);
end;

function Arbore.RInsert;
var aux : PNod;
begin
 if Crt=NIL
    then begin
          new(Aux);
          new(Aux^.Info);
          Aux^.Info^:=Info^;
          Aux^.left := NIL;
          Aux^.right := NIL;
          Aux^.count := 1;
          RInsert := aux;
          exit;
         end
    else if info^=Crt^.Info^
            then inc(Crt^.count)
            else if info^>Crt^.Info^
                    then Crt^.right := RInsert(info,Crt^.right)
                    else Crt^.left :=RInsert(info,Crt^.left);
  RInsert := crt;
end;

procedure Arbore.Action;
begin
 writeln(Crt^.Info^,'  ',Crt^.count);
end;

procedure Arbore.Ino;
begin
 if Crt^.left<>NIL then Ino(Crt^.left);
 Action(Crt);
 if Crt^.right<>NIL then Ino(Crt^.right);
end;

function Arbore.Search;
begin
 if Crt = NIL then Search := NIL
    else if Crt^.Info^=Info^
         then Search := crt
         else if Crt^.Info^>Info^ then Search := Search(Info,Crt^.left)
                                  else Search := Search(Info,Crt^.right);
end;

function Arbore.Level;
begin
 if Crt = NIL
    then Level := 0
    else if Crt^.Info^=Info^
            then Level := lcount
            else if crt^.Info^>Info^
                    then Level := Level(info,crt^.left,lcount+1)
                    else Level := Level(info,crt^.right,lcount+1);
end;

procedure Arbore.NiceTree;
begin
 inc(y);dec(x,5);
 if crt^.left<>NIL then NiceTree(crt^.left,x,y);
 dec(y);inc(x,5);
 gotoxy(x,y);Action(crt);
 inc(y);inc(x,5);
 if crt^.right<>NIL then NiceTree(crt^.right,x,y);
 dec(y);dec(x,5);
end;

procedure Arbore.Adincime;
begin
 if CrtLevel>Depth then Depth := CrtLevel;
 if crt^.left<>NIL then  Adincime(crt^.left ,CrtLevel+1);
 if crt^.right<>NIL then Adincime(crt^.right,CrtLevel+1);
end;

procedure Arbore.Frunze;
begin
 if (crt^.left=NIL) and (crt^.right=NIL) then Action(Crt);
 if crt^.left<>NIL then Frunze(crt^.left);
 if crt^.right<>NIL then Frunze(crt^.right);
end;

procedure Arbore.Familie;
 var temp1,temp2  : PNod;
     gasit   : boolean;
begin
 gasit := false;
 temp1 := crt;
 temp2 := NIL;
 while (temp1<>NIL) and (not gasit) do
        if temp1^.info^ = info^
           then begin
                 gasit := true;
                 gotoxy(10,10);writeln('Nodul ',info^,' a fost gasit.');
                 if temp2<>NIL
                    then begin gotoxy(10,11);writeln('Parintele este ',temp2^.info^);end;
                 if (temp2<>NIL)
                    then if temp2^.left<>temp1 then begin gotoxy(10,12);writeln('Fratele sting este ',temp2^.left^.info^);end;
                 if (temp2<>NIL)
                    then if temp2^.right<>temp1 then begin gotoxy(10,13);writeln('Fratele drept este',temp2^.right^.info^);end;
                 if (temp1^.left<>NIL)
                    then begin gotoxy(10,14);writeln('Fiul sting este ',temp1^.left^.info^);end;
                 if (temp1^.right<>NIL)
                    then begin gotoxy(10,15);writeln('Fiul drept este ',temp1^.right^.info^);end;
                end
          else if temp1^.info^>info^
                  then if temp1^.left<>NIL
                       then begin temp2:=temp1;temp1:=temp1^.left;end
                       else begin end
                  else if temp1^.right<>NIL
                          then begin temp2:=temp1;temp1:=temp1^.right;end
                               else begin end;

 if gasit = FALSE then begin gotoxy(10,10);writeln('Nodul ',info^,' nu a fost gasit.');end;
end;

procedure Arbore.SupriMin;
var temp : PNod;
begin
 if crtnod^.left<>NIL then SupriMin(crtnod^.left)
    else begin
          dispose(crtnod^.info);
          temp := crtnod^.right;
          dispose(crtnod);
          crtnod := temp;
         end;
end;

function Arbore.Supred;
var temp1,temp2 : PNod;
begin
 if crt^.right<>NIL then crt^.right := Supred(crt^.right,p)
    else begin
          temp2 := crt;
          dispose(p^.info);
          p^.info := crt^.info;
          p^.count := crt^.count;
          crt := crt^.left;
          dispose(temp2);
         end;
 Supred := crt;
end;

function Arbore.Suprima;
var temp1 : PNod;
begin
 if crt<>NIL
    then if crt^.info^>info^ then crt^.left := Suprima(crt^.left,info)
            else if crt^.info^<info^ then crt^.right := Suprima(crt^.right,info)
                 else if crt^.left=NIL
                      then begin
                            temp1 := crt^.right;
                            dispose(crt^.info);
                            dispose(crt);
                            Suprima := temp1;
                            exit;
                           end
                      else if crt^.right=NIL
                           then begin
                                 temp1 := crt^.left;
                                 dispose(crt^.info);
                                 dispose(crt);
                                 Suprima := temp1;
                                 exit;
                                end
                           else crt^.left := Supred(crt^.left,crt);
 Suprima := crt;
end;

destructor Arbore.Done;
begin
 {should destroy the tree-not yet implemented}
end;

procedure Meniu;
begin
 clrscr;
 gotoxy(5,2);writeln('Alegeti :');
 gotoxy(5,3);writeln('=========');
 gotoxy(10,4);writeln('1.Afisare arbore');
 gotoxy(10,5);writeln('2.Descendenta?');
 gotoxy(10,6);writeln('3.Adincimea arborelui');
 gotoxy(10,7);writeln('4.Frunze');
 gotoxy(10,8);writeln('5.Descendentii unui nod');
 gotoxy(10,9);writeln('6.Familia unui nod');
 gotoxy(10,10);writeln('7.Stergeri');
 gotoxy(10,11);writeln('8.Iesire');
end;


VAR
   Arb   : PArbore;
   F     : FILE;
   c     : char;
   s     : pstring;
   aux1  : PNod;
   aux2  : PNod;
   lvl1  : integer;
   lvl2  : integer;
   s1,s2 : PString;

BEGIN

 Arb := new(PArbore,Init);
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

 meniu;

 while (c<>'8') do
       begin
        if keypressed then c := readkey
                      else c := #0;
        case c of
        '1' : begin
               clrscr;
               gotoxy(15,1);
               writeln('Afisare arbore in inordine');
               Arb^.Ino(Arb^.Root);
               readln;
               clrscr;
               gotoxy(15,1);writeln('Afisare NiceTree style');
               Arb^.NiceTree(Arb^.Root,25,5);
               readln;
               meniu;
              end;
        '2' : begin
               clrscr;
               new(s1);new(s2);
               gotoxy(15,1);writeln('Descendenta?');
               gotoxy(10,5);write('Introduceti primul nume : ');readln(s1^);
               aux1 := Arb^.Search(s1,Arb^.Root);lvl1 := Arb^.Level(s1,Arb^.Root,1);
               if aux1=NIL
                  then begin
                        gotoxy(15,15);
                        writeln('Nu a fost gasit!');
                       end
                  else begin
                        gotoxy(10,6);write('Introduceti al doilea nume : ');readln(s2^);
                        aux2 := Arb^.Search(s2,Arb^.Root);lvl2 := Arb^.Level(s2,Arb^.Root,1);
                        if aux2=NIL
                           then begin
                                 gotoxy(15,15);
                                 writeln('Nu a fost gasit!');
                                end
                           else if lvl1=lvl2
                                   then begin
                                         gotoxy(15,8);
                                         writeln('nodurile se afla pe nivelul ',lvl1);
                                        end
                                   else begin
                                         if lvl1<lvl2
                                            then begin
                                                  aux1 := Arb^.Search(s2,aux1);
                                                  if aux1<>NIL
                                                     then begin
                                                           gotoxy(15,8);
                                                           writeln('nodul ',s1^,' e stramos a lui ',s2^);
                                                          end
                                                     else begin
                                                           gotoxy(15,8);
                                                           writeln('nodul ',s1^,' nu e stramos a lui ',s2^);
                                                          end
                                                 end
                                            else begin
                                                  aux2 := Arb^.Search(s1,aux2);
                                                  if aux1<>NIL
                                                     then begin
                                                           gotoxy(15,8);
                                                           writeln('nodul ',s2^,' e stramos a lui ',s1^);
                                                          end
                                                     else begin
                                                           gotoxy(15,8);
                                                           writeln('nodul ',s2^,' nu e stramos a lui ',s1^);
                                                          end
                                                 end
                                        end;
                       end;
               readln;
               dispose(s1);dispose(s2);
               meniu;
              end;
        '3' : begin
               clrscr;
               Arb^.Adincime(Arb^.Root,1);
               gotoxy(15,1);writeln('Adincimea arborelui este : ',Arb^.Depth);
               readln;
               meniu;
              end;
        '4' : begin
               clrscr;
               gotoxy(15,1);writeln('Frunzele sint :');
               gotoxy(1,10);
               Arb^.Frunze(Arb^.Root);
               readln;
               meniu;
              end;
        '5' : begin
               new(s1);
               clrscr;
               gotoxy(15,1);writeln('Descendentii unui nod');
               gotoxy(10,4);write('Introduceti nodul ');readln(s1^);
               aux1 := Arb^.Search(s1,Arb^.Root);
               if aux1 = NIL
                  then begin
                        gotoxy(10,8);
                        writeln('Nodul ',s1^,' nu a fost gasit !');
                       end
                  else Arb^.NiceTree(aux1,25,10);
               readln;
               meniu;
               dispose(s1);
              end;
        '6' : begin
               new(s1);
               clrscr;
               gotoxy(15,1);writeln('Familia unui nod');
               gotoxy(10,4);write('Introduceti nodul :');readln(s1^);
               Arb^.Familie(Arb^.Root,s1);
               readln;
               meniu;
               dispose(s1);
              end;
        '7' : begin
               clrscr;
               gotoxy(15,1);writeln('Suprimare nod minim');
               Arb^.SupriMin(Arb^.Root);
               Arb^.NiceTree(Arb^.Root,25,10);
               readln;
               {}
               new(s1);
               clrscr;
               gotoxy(15,1);writeln('Suprimarea nodului cu cheie data');
               gotoxy(10,4);write('Introduceti nodul :');readln(s1^);
               Arb^.Suprima(Arb^.Root,s1);
               Arb^.NiceTree(Arb^.Root,25,10);
               readln;
               dispose(s1);
               {}
               meniu;
              end;
        end;
       end;

 dispose(s);
 clrscr;
END.