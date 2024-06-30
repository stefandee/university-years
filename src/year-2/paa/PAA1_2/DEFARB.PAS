UNIT
    DEFARB;

INTERFACE

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
           procedure   Adincime(Crt : PNod;CrtLevel : integer);
           procedure   NiceTree(crt : PNod;x,y : integer);
           procedure   WriteOrdonat(crt : PNod);
           procedure   Equilibrium(s,d : integer;EArb : PArbore);
           function    Search(Info : PString;Crt : PNod) : PNod;
           destructor  Done;
          private
           function    RInsert(Info : PString;Crt : PNod) : PNod;
          end;
VAR
   CntOrdonat : integer;
   Ordonat    : array[1..300] of PNod;

IMPLEMENTATION

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
 writeln(Crt^.Info^);
end;

procedure Arbore.Ino;
begin
 if Crt^.left<>NIL then Ino(Crt^.left);
 Action(Crt);
 if Crt^.right<>NIL then Ino(Crt^.right);
end;

procedure Arbore.Adincime;
begin
 if CrtLevel>Depth then Depth := CrtLevel;
 if crt^.left<>NIL then  Adincime(crt^.left ,CrtLevel+1);
 if crt^.right<>NIL then Adincime(crt^.right,CrtLevel+1);
end;


procedure Arbore.WriteOrdonat;
begin
 if Crt^.left<>NIL then WriteOrdonat(Crt^.left);
 inc(CntOrdonat);Ordonat[CntOrdonat] := Crt;
 if Crt^.right<>NIL then WriteOrdonat(Crt^.right);
end;

procedure Arbore.Equilibrium;
var m : integer;
begin
 m := (s+d) div 2;
 if s<=m then EArb^.Insert(Ordonat[m]^.Info);
 if s<=m-1 then Equilibrium(s,m-1,EArb);
 if m+1<=d then Equilibrium(m+1,d,EArb);
end;

procedure Arbore.NiceTree;
begin
 inc(y);dec(x,5);
 if crt^.left<>NIL then NiceTree(crt^.left,x,y);
 dec(y);
 gotoxy(x,y);Action(crt);
 inc(y);inc(x,10);
 if crt^.right<>NIL then NiceTree(crt^.right,x,y);
 dec(y);dec(x,5);
end;

function Arbore.Search;
begin
 if Crt = NIL then Search := NIL
    else if Crt^.Info^=Info^
         then Search := crt
         else if Crt^.Info^>Info^ then Search := Search(Info,Crt^.left)
                                  else Search := Search(Info,Crt^.right);
end;

destructor Arbore.Done;
begin
 {should destroy the tree-not yet implemented}
end;

BEGIN
END.