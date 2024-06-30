program encoder;

uses crt;
const n=3;
var s:string;
    lit:array[1..n,1..n] of char;
    cif:array[1..n,1..n] of byte;
    i,j,k,u,v,min:integer;

begin
clrscr;
writeln('matr de litere');
for i:=1 to n do
    for j:=1 to n do
        readln(lit[i,j]);
writeln('matr de cifre');
for i:=1 to n do
     for j:=1 to n do
         read(cif[i,j]);

writeln('sirul de codat este');
read(s);
for i:=1 to length(s) do
    begin
    for j:=1 to n do
        for k:=1 to n do
            if lit[j,k]=s[i] then begin
                                  min:=10000;
                                  for u:=j-1 to j+1 do
                                      for v:=k-1 to k+1 do
                                          if (u>0) and (u<n+1) and
                                             (v>0) and (v<n+1) and
                                             (u<>j) and (v<>k) then
                                             if cif[u,v]<min then min:=cif[u,v];
                                  write(min,' ');
                                  end;
   end;
readln;
readln;
end.
