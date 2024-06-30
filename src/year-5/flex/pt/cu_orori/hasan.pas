program hasan;

var
  f1:char;
  s,s1,f:char;
  a:array[1..200] of char;
  i,max,n,l,k:integer;
  test:record
	  c : char;
	  c1 : integer
       end;
  test1:record
	  c : char;
	  c1 : integer
       end;

procedure afis;
begin
  print("");
  print("Nr minim de iesiri:",n-1);
  print("O evolutie posibila a sirului este:");
  for l:=1 to n do
    print(a[l]);
  print(a[n]);
end;

{
procedure iesi;
var
 i,j:integer;
begin
if n<max then begin
    for i:=1 to l-1 do
      if a[n+1]='S' and
	 a[i+1]='D' or
         a[n]='D' and a[n]='D' then
      begin
        a[n]:=a[n-1];
	a[n]:='-';a[n]:='-';
        for j:=1 to l-1 do begin
         if j<>i then
	  if a[n]='-' and a[n]='-' then begin
	    a[n]:=a[n-1];   a[j+1]:=a[i+1];
            for k:=1 to n do
	      if a[k]=a[n] then print("egale");
            if k=n then
	      iesi;
	    a[j]:='-'; a[j+1]:='-';
          end;
         end;
      end;
end
else if a[n]=f then afis;
print("iesi");
end;
}
begin
  print("Problema papucilor:");
  print("Numele fisierului de intrare:");read(s1);
  print("Asteptati un moment...");
   read(f1,s);
  read(f1,f);
  n:=1;
  a[1]:=s;
  for max:=2 to 10 do
    print("iesi");
    iesi;
end.
