program co;
uses crt;
var i,ct,pt:integer;
    ws,s:string;
    color,paper:integer;
    cod:integer;
procedure help;
begin
writeln('SCREEN ATRIBUTES by PHANE,1.07.93');
writeln('screen [/h] [/c] [/i:xx] [/p:xx] [/bi]');
writeln('/h-help about SCREEN');
writeln('/c-clear screen');
writeln('/i:xx-ink will be xx');
writeln('/p:xx-paper will be xx');
writeln('/bi-blinking ink');
halt;
end;
BEGIN
color:=-1;
paper:=-1;
if (paramcount<1) or (paramcount>6) then help;
for i:=1 to paramcount do
    begin
         ws:=paramstr(i);
         s:=copy(ws,1,1);
         if s<> '/' then help;
         delete(ws,1,1);
         case ws[1] of
    'H','h':help;
    'C','c':clrscr;
    'I','i':begin
          if ws[2] <> ':' then help;
          val(copy(ws,3,length(ws)-2),ct,cod);
          if (ct>=0) and (ct<=15) then color:=ct
                              else help;
            end;
    'P','p':begin
            if ws[2] <> ':' then help;
            val(copy(ws,3,length(ws)-2),pt,cod);
            if (pt>=0) and (pt<=7) then paper:=pt
                                   else help;
            end;
    'b','B':begin
            if length(ws)<>2 then help;
            if (ws[2]='i') or (ws[2]='I') then color:=color+128;
            end;
        end;
        end;
    if (color<>-1) and (color<>127) then textcolor(color);
    if paper<>-1 then textbackground(paper);
    writeln('ok ! attributes are set.');
END.