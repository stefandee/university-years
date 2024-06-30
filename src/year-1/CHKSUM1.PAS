program checksum;
var f:file of byte;
    b,rez,op:byte;
    filename:string;
begin
filename:='256col.pas';
assign(f,filename);
reset(f);
rez:=0;
op:=0;
while not eof(f) do
      begin
           read(f,b);
           case op of
           1:rez:=rez or b;
           2:rez:=rez xor b;
           3:rez:=rez and not b;
           end;
           inc(op);
           if op>3 then op:=0;
      end;
writeln('checsum for '+filename+' is ',rez);
readln;
end.