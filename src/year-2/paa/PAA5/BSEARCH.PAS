program
       test_B_search;

var
   list    : array[1..20] of integer;
   cheie,i,k,l,r,mid : integer;
   gasit : boolean;
begin
 for i:=1 to 20 do list[i]:=2*i;
 cheie := 100;
 k := 0;
 gasit := false;
 l := 1;r := 20;mid := (l+r) div 2;
 repeat
  if cheie>list[mid] then begin l:=mid;mid:=(l+r) div 2;end
     else if cheie<list[mid] then begin r:=mid;mid:=(l+r) div 2;end
          else begin gasit:= true;k:=mid end;
 until (l=mid) or (gasit);
 if gasit then writeln('gasit ',cheie,' pe pos ',k)
          else writeln('nu am gasit cheia');
end.
