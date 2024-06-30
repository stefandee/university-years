program conversie;
uses crt;
var st:string;
    i,j:integer;
    rez:integer;
    b:boolean;
begin
clrscr;
repeat
i:=1;rez:=0;st:='';b:=true;
write('sirul pt conversie ?');readln(st);
repeat
case upcase(st[i]) of
'I': case upcase(st[i+1]) of
     'V' : begin
           inc(rez,4);
           inc(i,2);
           end;
     'X' : begin
           inc(rez,9);
           inc(i,2);
           end;
     else begin
          inc(rez);inc(i);
          end;
     end;
'V' : begin
      inc(rez,5);
      inc(i);
      end;
'X' : case upcase(st[i+1]) of
     'C' : begin
           inc(rez,90);
           inc(i,2);
           end;
     'L' : begin
           inc(rez,40);
           inc(i,2);
           end;
     else begin
          inc(rez,10);inc(i);
          end;
     end;

'L' : begin
    inc(rez,50);
    inc(i);
    end;
'C' : begin
      case upcase(st[i+1]) of
     'M' : begin
           inc(rez,900);
           inc(i,2);
           end;
     else begin
          inc(rez,100);inc(i);
          end;
     end;
      end;
'M' : begin
      inc(rez,1000);
      inc(i);
      end;
else begin
     writeln('litere gresite !!!');
     i:=length(st)+1;
     b:=false;
     end;
end;
until i>length(st);
if b then writeln('rezultatul este ',rez);
until st='';
end.