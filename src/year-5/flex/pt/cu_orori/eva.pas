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
