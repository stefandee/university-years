program hanoi_rezolvare;

uses crt,graph;

type tija=array[1..103] of integer;

var ndisk:byte;
    a,b,c:tija;
    gd,gm,i,j:integer;

procedure hanoi(n:integer;var a,b,c:tija);
begin
if n=1 then begin
            inc(b[100]);
            b[b[100]]:=1;
            setfillstyle(1,black);
            bar(a[101]-5*a[a[100]],100+10*(ndisk-a[100]+1),a[101]+5*a[a[100]],110+10*(ndisk-a[100]+1));
            setfillstyle(1,white);
            bar(b[101]-5*b[b[100]],100+10*(ndisk-b[100]+1),b[101]+5*b[b[100]],110+10*(ndisk-b[100]+1));
            dec(a[100]);
            repeat until readkey=#13;;
            end
       else begin
            hanoi(n-1,a,c,b);
            inc(b[100]);
            b[b[100]]:=n;
            setfillstyle(1,black);
            bar(a[101]-5*a[a[100]],100+10*(ndisk-a[100]+1),a[101]+5*a[a[100]],110+10*(ndisk-a[100]+1));
            setfillstyle(1,white);
            bar(b[101]-5*b[b[100]],100+10*(ndisk-b[100]+1),b[101]+5*b[b[100]],110+10*(ndisk-b[100]+1));
            dec(a[100]);
            repeat until readkey=#13;
            hanoi(n-1,c,b,a);
            end;
end;
begin
clrscr;
write(' cite diskuri ? ');readln(ndisk);
gd:=detect;
initgraph(gd,gm,'f:\bin\tp6\bgi');
a[100]:=ndisk;{nr de diskuri pe tija a}
a[101]:=100;{coord y}
b[100]:=0;
b[101]:=200;
c[100]:=0;
c[101]:=300;

for i:=1 to ndisk do
    begin
    a[ndisk-i+1]:=i;
    end;
setfillstyle(1,white);
for i:=1 to ndisk do bar(a[101]-5*a[i],100+10*a[i],a[101]+5*a[i],110+10*a[i]);
readln;
hanoi(ndisk,a,b,c);
end.