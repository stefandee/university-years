program sin_taylor;
uses crt;
const eps=0.05;
var deg,i:integer;
    valrad,ant,val:real;

begin

clrscr;
write('valoarea argumentului:');
read(deg);
valrad:=pi*deg/180;
ant:=valrad;
val:=valrad;
i:=3;
repeat
ant:=(-1)*ant*valrad*valrad/(i*(i-1));
val:=val+ant;
inc(i,2);
until (i>10) or (sin(valrad)-ant<eps);
writeln(' valoarea lui sin de ',deg,' grade este ',val:6:4);
readln;
readln;

end.
