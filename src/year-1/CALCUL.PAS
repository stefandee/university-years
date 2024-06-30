program calcul;

uses crt;
const found:boolean=false;
type stack=array[1..10] of integer;
var nr,op:stack;
    mask:array[1..10] of boolean;
    {operatorii au codificarea:
    0-nimic;
    1-inmultire;
    2-impartire;
    3-adunare;
    4-scadere}
    sum,numar,cite,i:integer;


function evaluation(nr,op:stack):integer;
var i,j:integer;
    fmul,fsum:boolean;
begin
repeat
fmul:=false;
for i:=1 to cite-1 do
    begin
    if op[i]=1 then begin
                 nr[i]:=nr[i]*nr[i+1];
                 for j:=i+1 to 9 do nr[j]:=nr[j+1];
                 for j:=i to 9 do op[j]:=op[j+1];
                 mask[i]:=true;
                 fmul:=true;
                 end;
    if op[i]=2 then begin
                 if nr[i+1]<>0 then nr[i]:=nr[i] div nr[i+1];
                 for j:=i+1 to 9 do nr[j]:=nr[j+1];
                 for j:=i to 9 do op[j]:=op[j+1];
                 mask[i]:=true;
                 fmul:=true;
                 end;
    end;
until not fmul;
repeat
fsum:=false;
for i:=1 to cite-1 do
    begin
    if op[i]=3 then begin
                 nr[i]:=nr[i]+nr[i+1];
                 for j:=i+1 to 9 do nr[j]:=nr[j+1];
                 for j:=i to 9 do op[j]:=op[j+1];
                 mask[i]:=true;
                 fsum:=true;
                 end;
    if op[i]=4 then begin
                 nr[i]:=nr[i]-nr[i+1];
                 for j:=i+1 to 9 do nr[j]:=nr[j+1];
                 for j:=i to 9 do op[j]:=op[j+1];
                 mask[i]:=true;
                 fsum:=true;
                 end;
    end;
until not fsum;
j:=0;
for i:=1 to cite do j:=nr[i]+j;
evaluation:=j;
end;

procedure algoritm;
var k,i:integer;
begin
for k:=1 to cite-1 do op[k]:=-1;
k:=1;
while k>0 do
      begin
           while (op[k]<5) and (k<5) do
                 begin
                      for i:=1 to 10 do mask[i]:=false;
                      inc(op[k]);
                      if evaluation(nr,op)=sum then
                         begin
                         found:=true;
                         for i:=1 to 10 do write(nr[i]);
                             {if mask[i] then begin
                                               write(nr[i]);
                                               if mask[i+1] then
                                                             case op[i] of
                                                             1:write('*');
                                                             2:write('/');
                                                             3:write('+');
                                                             4:write('-');
                                                             end{case}
                                                             {else write('+');
                                               end;{if}

                         writeln;
                         end

                 else inc(k);
                 end;
      op[k]:=-1;
      dec(k);
      end;

end;

Begin
clrscr;
for i:=1 to 10 do
    begin
         nr[i]:=0;
         op[i]:=0;
    end;
nr[1]:=8;nr[2]:=2;nr[3]:=8;nr[4]:=16;nr[5]:=1;
cite:=5;
sum:=1024;
algoritm;
if not found then writeln('nu se poate forma numarul !');
readln;
End.
