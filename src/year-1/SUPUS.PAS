program supus;

var
   x,y : longint;
   z   : longint;
   min : longint;

begin
 write('Baga pe x : ');readln(x);
 write('Baga pe y : ');readln(y);
 if x>y then min:=y
        else min:=x;
 for z:=min downto 1 do
     if (x and z=z) and (y and z=z)
        then begin
              writeln('z este : ',z);
              readln;
              halt;
             end;
end.


