program p;
const
   cti = 2;
var
   c1, c2 : char;
   i1, i2 : integer;
   r1, r2 : real;
   s1, s2 : record
      c	: char;
      i	: integer;
      r	: real
   end;
   a : array[1..10] of real;

procedure proc0;
var
   c : char;
begin
   c:=c1;
end; { proc1 }

procedure proc1(i : integer);
begin
   i1:=i;
end; { proc1 }

procedure proc4(i1_in, i2_in : integer; var i1_out, i2_out:integer);
begin
   i1_out := i1_in;
   i2_out := i2_in;
end; { proc4 }

procedure procA;
  var p:char;
  procedure procB;
  var p:char;
  begin
  end; { procB }
  procedure procC;
    procedure procC1;
    begin
    end; { procC1 }
    procedure procC2;
    begin
       procA;
       procB;
       procC;
       procC1;
       procC2;
    end; { procC2 }
  begin
  end; { procC }
begin
   procA;
   procB;
   procC;
end; { procA }
    
function f:char;
begin
   f := 'c';
end; { f }

function f1(i :integer ):integer;
begin
   if i=1 then
   begin
      f1:=3;
      procA;
   end
   else
      f1:=f1(i-1);
end; { f1 }

function f3(	i1, i2 : real; var r:real):char;
begin
   r := i1+i2;
   f3 := 'D';
end; { f3 }

begin
   i1 := f3(i1, i2, r1);
   c2 := f3(s1.i, i1, s1.r);
   i1 := f1(a[3]);
   c1 := f3(i1, s1.i, a[3]);
   c1 := f3(i1+i2/r2, i2, s1.r);
   while i < j do
{   while i1 < f1(i2) and c1 <> c2 do}
   begin
      i1 := cti;
      procA;
   end;
   repeat
      proc1(i1)
   until i1 = i2;
   for i1 := cti to i2 do
      proc4(1, 2, i1, i2);
end.



