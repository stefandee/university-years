program x;
uses graph,turtle;
var i,gd,gm:integer;
begin
gd:=detect;
initgraph(gd,gm,'c:\bin\tp7\bgi');
for i:=1 to 6 do
    begin
         right(60);
         forward(60);
    end;
readln;
end.