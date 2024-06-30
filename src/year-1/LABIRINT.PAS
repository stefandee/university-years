program labirint;
uses crt;

const a:array[1..4] of integer=(1,0,-1,0);
      b:array[1..4] of integer=(0,1,0,-1);

var h:array[1..24] of string[80];
    i,j:integer;
    f:text;

procedure drum(x,y:integer);

var u,v,k:integer;
    found:boolean;

begin

k:=0;
gotoxy(x,y);write('*');
h[y,x]:='*';
found:=false;

repeat
k:=k+1;
u:=x+a[k];
v:=y+b[k];
if (u>80) or (v>24) or (u<1) or (v<1) then begin
                                           gotoxy(x,y);
                                           write('!');
                                           found:=true;
                                           end
   else begin
        if h[v,u]='.' then begin
                           gotoxy(u,v);write('*');
                           gotoxy(x,y);write(' ');
                           delay(10);
                           drum(u,v);
                           end;
        end;
until k=4;
if not found then gotoxy(x,y);write(' ');
end;



begin
clrscr;
assign(f,'labirint.dat');
reset(f);
for i:=1 to 24 do
        begin
             readln(f,h[i]);
             for j:=1 to 80 do
                 case h[i,j] of
                 'P':write('Û');
                 '.':write(' ');
                 end;
        end;
close(f);
drum(40,12);
readln;

end.

