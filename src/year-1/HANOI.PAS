program hanoi_rezolvare;
uses crt;
var ndisk:byte;
procedure hanoi(n:integer;a,b,c:char);
begin
if n=1 then begin
            write('se muta diskul ',n,' de pe ',a,' pe ',b);
            readln;
            end
       else begin
            hanoi(n-1,a,c,b);
            write('se muta diskul ',n,' de pe ',a,' pe ',b);
            readln;
            hanoi(n-1,c,b,a);
            end;
end;
begin
clrscr;
write(' cite diskuri ? ');readln(ndisk);
hanoi(ndisk,'a','b','c');
readln;
end.