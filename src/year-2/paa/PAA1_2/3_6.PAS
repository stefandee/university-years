PROGRAM
       Arbore_Generalizat;

USES
    CRT,DEFARB;

TYPE
   PString = ^String;
   PGNod = ^GNod;
   PLNod = ^LNod;
    GNod = record
        info       : PString;
        Tata       : PGNod;
        PrimFiu    : PLNod;
        end;

    LNod = record
         info : PGNod;
         next : PLNod;
         end;

    PGArbore = ^GArbore;
    GArbore = object
            Root : PGNod;
            Grad : integer;
            Inaltime : integer;
            constructor Init;
            function Search(var crt : PGNod;info : PString) : PGNod;
            procedure Insert(info : PString;tata : PString);
            procedure NiceTree(crt : PGNod;x,y : integer);
            procedure Ino(crt : PGNod);
            procedure Action(crt : PGNod);
            procedure CalcGrad(crt : PGNod);
            procedure CalcInal(crt : PGNod;level : integer);
            function  ToBinary(crtnod : PGNod;var ABCrt : PNod) : PNod;
            procedure InsertFiu(var primfiu ,fiu : PLNod);
            procedure Radacina(info : PString);
            procedure Oglinda(Crt : PGNod);
            destructor Done;
           end;

constructor GArbore.Init;
begin
 Grad := 0;
 Root := NIL;
end;

procedure GArbore.Action;
begin
 write(crt^.Info^);
end;

function GArbore.Search;
var aux  : PLNod;
    aux1 : PGNod;
begin
 if crt=NIL then Search := NIL
    else if crt^.Info^=info^ then Search := crt
         else begin
               aux := crt^.PrimFiu;
               while aux<>NIL do
                     begin
                      if aux^.info<>NIL
                         then begin
                               aux1:= Search(aux^.info,info);
                               if aux1<>NIL then begin Search := aux1;break;end;
                              end;
                      aux := aux^.next;
                     end;
              end;
end;

procedure GArbore.InsertFiu;
var aux : PLNod;
begin
 aux := primfiu;
 fiu^.next := NIL;
 if aux <> NIL
    then begin
          while (aux^.next <> NIL) do aux:=aux^.next;
          aux^.next := fiu;
         end
    else primfiu := fiu;
end;

procedure GArbore.Insert;
var aux  : PGNod;
    aux1 : PLNod;
begin
 aux := Search(Root,tata);
 if aux = NIL
    then begin
          writeln('Could not found this node ',tata^);
          writeln('Unable to continue inserting...');
         end
    else begin
          new(aux1);
          new(aux1^.info);
          new(aux1^.info^.info);
          aux1^.info^.PrimFiu := NIL;
          aux1^.info^.PrimFiu^.info := NIL;
          aux1^.info^.info^ := info^;
          aux1^.info^.Tata := aux;
          InsertFiu(aux^.PrimFiu,aux1);
         end;
end;

procedure GArbore.NiceTree;
var aux : PLNod;
    counter : integer;
begin
 aux := crt^.PrimFiu;
 gotoxy(x,y);
 Action(crt);
 counter := 0;
 while aux<>NIL do
       begin
        inc(counter,length(aux^.info^.info^)+2);
        aux:=aux^.next;
       end;
 dec(x,counter div 2);
 aux := crt^.PrimFiu;
 while aux<>NIL do
       begin
        inc(y);
        NiceTree(aux^.info,x,y);
        inc(x,length(aux^.info^.info^)+2);
        dec(y);
        aux:=aux^.next;
       end;
end;

procedure GArbore.Ino;
begin
end;

procedure GArbore.CalcGrad;
var counter : integer;
    aux     : PLNod;
begin
 aux := crt^.PrimFiu;
 counter := 0;
 while aux<>NIL do
       begin
        inc(counter);
        CalcGrad(aux^.info);
        aux:=aux^.next;
       end;
 if counter>Grad then Grad := counter;
end;

procedure GArbore.CalcInal;
var aux : PLNod;
begin
 aux := crt^.PrimFiu;
 while aux<>NIL do
       begin
        CalcInal(aux^.info,level+1);
        aux:=aux^.next;
       end;
 if level>Inaltime then Inaltime := level;
end;

function GArbore.ToBinary;
var aux : PLNod;
begin
 if crtnod<>NIL
    then begin
          new(ABCrt);
          new(ABCrt^.info);
          ABCrt^.info^ := crtnod^.info^;
          ABCrt^.left := ToBinary(crtnod^.primfiu^.info,ABCrt^.left);
          {the right branch}
          if crtnod=Root then ABCrt^.right := NIL{ToBinary(crtnod^.primfiu^.next^.info,ABCrt^.right)}
             else begin
                   aux := crtnod^.tata^.primfiu;
                   while aux<>NIL do
                         begin
                          if aux^.info = crtnod then break;
                          aux := aux^.next;
                         end;
                   ABCrt^.right := ToBinary(aux^.next^.info,ABCrt^.right);
                  end;
          ToBinary := ABCrt;
         end
    else ToBinary := NIL;
end;

destructor GArbore.Done;
begin
end;

procedure GArbore.Radacina;
begin
 new(Root);
 new(Root^.info);
 Root^.info^ := info^;
 Root^.PrimFiu := NIL;
 Root^.Tata := NIL;
end;

procedure GArbore.Oglinda;
var aux,aux1,aux2 : PLNod;
begin
 aux := crt^.primfiu;
 aux1 := NIL;
 aux2 := NIL;{new first pointer of list}
 while aux<>NIL do
       begin
        aux2 := aux^.next;
        aux^.next := aux1;
        aux1 := aux;
        Oglinda(aux^.info);
        aux := aux2;
       end;
 crt^.primfiu := aux1;
end;

procedure ReadFii(tata : PString;info : PString;var GArb : PGArbore);
var aux : PString;
    i   : integer;
begin
 new(aux);aux^:='';
 for i:=1 to length(info^)+1 do
      if (info^[i]=',') or (i>length(info^)) then
         begin
          GArb^.Insert(aux,tata);
          aux^:='';
         end
         else aux^:=aux^+info^[i];
 dispose(aux);
end;

procedure ReadRadacina(info :  PString;var GArb : PGArbore);
var aux : PString;
    fii : PString;
    i,j : integer;
begin
 new(aux);aux^:='';
 for i:=1 to length(info^) do
     begin
      if info^[i]='>' then break
                      else aux^:=aux^+info^[i];
     end;

 if GArb^.Root = NIL
    then GArb^.Radacina(aux);

 new(fii);fii^:='';
 for j:=i+1 to length(info^) do fii^:=fii^+info^[j];
 ReadFii(aux,fii,GArb);
 dispose(fii);

 dispose(aux);
end;

VAR
   GArb : PGArbore;
   c    : char;
   s    : PString;
   Arb  : PArbore;
   F    : file;

begin
 clrscr;
 GArb := new(PGArbore,Init);
 Arb := new(PArbore,Init);
 new(s);s^:='';

 assign(F,'3_6.dat');
 reset(F,1);
 while not eof(F) do
       begin
        blockread(F,c,1);
        if c>' 'then s^:=s^+c
                else if s^<>''
                     then begin
                           ReadRadacina(s,GArb);
                           s^:='';c:=' ';
                          end;
       end;
 close(F);
 gotoxy(15,1);writeln('Arborele este');
 GArb^.NiceTree(GArb^.Root,40,5);
 readln;

 clrscr;
 GArb^.CalcGrad(GArb^.Root);
 GArb^.CalcInal(GArb^.Root,1);
 gotoxy(15,1);writeln('Gradul arborelui este : ',GArb^.Grad,' si inaltimea este ',GArb^.Inaltime);
 readln;

 clrscr;
 GArb^.ToBinary(GArb^.Root,Arb^.Root);

 Arb^.Adincime(Arb^.Root,1);
 GArb^.Inaltime := 0;
 GArb^.CalcInal(GArb^.Root,1);
 gotoxy(8,1);writeln('Inaltimea arborelui binar este ',Arb^.Depth,' iar a arborelui generalizat este ',GArb^.Inaltime);

 Arb^.NiceTree(Arb^.Root,40,3);
 GArb^.NiceTree(GArb^.Root,40,15);
 readln;

 clrscr;
 gotoxy(15,1);writeln('Arborele in oglinda/arborele initial');
 GArb^.NiceTree(GArb^.Root,40,3);
 GArb^.Oglinda(GArb^.Root);
 GArb^.NiceTree(GArb^.Root,40,12);
 readln;

 dispose(s);
end.