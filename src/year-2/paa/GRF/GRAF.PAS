PROGRAM
       GRAFURI;

USES
    DOS,CRT;

CONST
     MaxN = 10;

TYPE
    Str10 = string[10];

VAR
   MA    : array[1..MaxN,1..MaxN] of boolean;
   Key   : array[1..MaxN] of str10;
   Mark  : array[1..MaxN] of boolean;
   Keyp  : char;
   i,j,k : integer;
   found : boolean;
   last  : integer;
   queue : array[1..100] of integer;
   cf,cl : integer;
   temp,temp1  : str10;
   ind,ind1    : integer;

procedure Meniu;
begin
 clrscr;
 gotoxy(5,5);writeln('Grafuri-matrici de adiacenta');
 gotoxy(10,10);writeln('I-Insereaza nod');
 gotoxy(10,11);writeln('N-Sterge nod');
 gotoxy(10,12);writeln('A-Insereaza arc');
 gotoxy(10,13);writeln('S-Sterge arc');
 gotoxy(10,14);writeln('T-Traversare in adincime');
 gotoxy(10,15);writeln('C-Traversare prin cuprindere');
 gotoxy(10,16);writeln('B-Componente conexe');
 gotoxy(10,17);writeln('D-Padure de arbori de acoperire');
 gotoxy(10,18);writeln('P-Graf biconex/puncte de articulatie ale comp conexe maxime');
 gotoxy(10,20);writeln('E<x>it');
end;

procedure Adincime(x : integer);
var
   i : integer;
begin
 Mark[x] := true;
 write(Key[x],' ');
 for i:=1 to MaxN do if MA[x,i] then if not Mark[i] then Adincime(i);
end;

procedure Cuprindere(x : integer);
begin
 inc(cl);queue[cl]:=x;Mark[x]:=true;
 while cl<>cf do
       begin
        inc(cf);
        x:=queue[cf];write(Key[x],' ');
        for i:=1 to last do if MA[x,i] then if not Mark[i] then begin inc(cl);queue[cl]:=i;Mark[i]:=true;end;
       end;
end;

function Articulatie(x : integer) : integer;
begin

end;

BEGIN
 for i:=1 to MaxN do for j:=1 to MaxN do MA[i,j]:=false;
 for i:=1 to MaxN do Key[i]:='';
 meniu;
 last:=0;
 repeat
  if keypressed then keyp:=UPCASE(readkey)
                else keyp:=#0;
  case keyp of
  'V' : begin
         clrscr;
         gotoxy(5,5);writeln('Vizualizare graf');
         gotoxy(10,10);for i:=1 to last do write(Key[i],' ');
         for i:=1 to last do for j:=1 to last do begin gotoxy(10+j*2,11+i*2);writeln(byte(MA[i,j]));end;
         readln;
         meniu;
        end;
  'I' : begin
         clrscr;
         gotoxy(5,5);writeln('Insereaza nod');
         gotoxy(10,10);write('Cheia : ');readln(temp);
         found := false;
         for i:=1 to MaxN do if temp=Key[i] then begin found := true;break;end;
         if found then begin gotoxy(10,11);writeln('Nodul exista.');end
            else begin
                  inc(last);
                  Key[last]:=temp;
                  gotoxy(10,11);writeln('Done.');
                 end;
         readln;
         meniu;
        end;
  'N' : begin
         clrscr;
         gotoxy(5,5);writeln('Sterge nod');
         gotoxy(10,10);write('Cheia : ');readln(temp);
         found := false;
         for i:=1 to last do
             if Key[i]=temp then begin
                for j:=i to last do Key[j]:=Key[j+1];
                for j:=i to last do
                    for k:=1 to MaxN do MA[k,j]:=MA[k,j+1];
                for j:=i to last do
                    for k:=1 to MaxN do MA[j,k]:=MA[j+1,k];
                dec(last);
                found := true;
                break;
               end;
         gotoxy(10,11);
         if not found then writeln('Nodul nu a fost gasit')
            else writeln('Done.');
         readln;
         meniu;
        end;
   'A' : begin
          clrscr;
          gotoxy(5,5);writeln('Insereaza arc');
          gotoxy(10,10);write('Cheia unu : ');readln(temp);
          gotoxy(10,11);write('Cheia doi : ');readln(temp1);
          found := false;
          for i:=1 to MaxN do if temp=Key[i] then begin found:=true;ind:=i;break;end;
          if found=false then begin gotoxy(10,12);writeln('Nodul ',temp,' nu a fost gasit');end
             else begin
                   found := false;
                   for i:=1 to MaxN do if temp1=Key[i] then begin found:=true;ind1:=i;break;end;
                   if found=false then begin gotoxy(10,12);writeln('Nodul ',temp1,' nu a fost gasit');end
                      else if MA[ind,ind1] then begin gotoxy(10,12);writeln('Arcul exista deja.');end
                              else begin MA[ind,ind1]:=true;MA[ind1,ind]:=true;end;
                  end;
           readln;
           meniu;
         end;
   'S' : begin
          clrscr;
          gotoxy(5,5);writeln('Sterge arc');
          gotoxy(10,10);write('Cheia unu : ');readln(temp);
          gotoxy(10,11);write('Cheia doi : ');readln(temp1);
          found := false;
          for i:=1 to MaxN do if temp=Key[i] then begin found:=true;ind:=i;break;end;
          if found=false then begin gotoxy(10,12);writeln('Nodul ',temp,' nu a fost gasit');end
             else begin
                   found := false;
                   for i:=1 to MaxN do if temp1=Key[i] then begin found:=true;ind1:=i;break;end;
                   if found=false then begin gotoxy(10,12);writeln('Nodul ',temp1,' nu a fost gasit');end
                      else if not MA[ind,ind1] then begin gotoxy(10,12);writeln('Arcul nu exista.');end
                              else begin MA[ind,ind1]:=false;MA[ind1,ind]:=false;end;
                  end;
           readln;
           meniu;
         end;
   'T','B','D' : begin
          clrscr;
          gotoxy(5,5);writeln('Traversare in adincime/Componente conexe/Padure de arbori de acoperire');
          for i:=1 to last do Mark[i]:=false;
          for i:=1 to last do if not Mark[i] then begin Adincime(i);writeln;i:=1;end;
          readln;
          meniu;
         end;
   'C' : begin
          clrscr;
          gotoxy(5,5);writeln('Traversare prin cuprindere');
          for i:=1 to MaxN do Mark[i] := false;
          for i:=1 to last do
              if not Mark[i] then begin for j:=1 to 100 do queue[j]:=0 ;cf := 0;cl := 0;Cuprindere(i);writeln;i:=0;end;
          readln;
          meniu;
         end;
  end;
 until keyp='X';
END.