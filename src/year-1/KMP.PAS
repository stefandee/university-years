const mmax=5{lungime maxima model};
      nmax=50{lungime maxima sir sursa};
var
    p:array [0..mmax-1] of char;{model}
    s:array [0..nmax-1] of char;{sir}
    d:array [0..mmax-1] of integer;{tabela de deplasari}
    i,m,n:integer;
    aux:string;

function CautareKMP(var poz:integer):boolean;
  var i,j,k:integer;
  begin
     {citire sir}
     {citire model}
     j:=0;k:=-1;d[0]:=-1;  {compilare model}
     while j<m-1 do
          begin
               while (k>=0) and (p[j]<>p[k]) do k:=d[k];
               j:=j+1;k:=k+1;
               if p[j]=p[k] then d[j]:=d[k]
               else d[j]:=k
          end;
     i:=0;j:=0;  {cautare model}
     while (j<m) and (i<n) do
          begin
               while (j>=0) and (s[i]<>p[j]) do j:=d[j];
	       j:=j+1;i:=i+1;
          end;
     poz:=i-m;
     CautareKMP:=j=m
  end;

begin
 m:=mmax;n:=nmax;
 aux:='Un sir aa de aabbc cautat';
 for i:=1 to length(aux) do s[i-1]:=aux[i];
 aux:='aabbc';
 for i:=1 to length(aux) do p[i-1]:=aux[i];
 CautareKMP(i);
end.