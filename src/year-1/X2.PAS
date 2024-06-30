program cuvinte;
uses crt;
var f:text;
    dest,sursa:string;
    nr,ps,pd,ln:integer;
procedure cauta(st:string);
var i,j,k:integer;
begin
for i:=length(st) downto 1 do
    for j:=1 to length(st)-i do
        for k:=1 to length(dest)-i do
            begin
            if copy(st,j,i)=copy(dest,k,i)
            then begin
                 {se cauta un nucleu maxim }
                 pd:=k;
                 ps:=j;
                 ln:=i;
                 writeln('nucleul maxim e ',copy(st,k,i));
                 exit;
                 end;

    end;
end;

begin

clrscr;
assign(f,'cuvinte.dic');
reset(f);
readln(sursa);
while not eof(f) do
      begin
           read(f,dest);
           nr:=-100;
           cauta(sursa);
           repeat until readkey=#13;
      end;
readln;
close(f);
end.