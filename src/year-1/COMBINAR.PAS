program combinari;

var sta:array[1..100] of integer;
    sp,n,p:integer;

function continuare(k:integer):boolean;
var i:integer;
begin
continuare:=true;
for i:=1 to k-1 do if (sta[k]<=sta[i]) then begin
                                       continuare:=false;
                                       exit;
                                       end;
end;

procedure tipareste;
var i:integer;
begin
for i:=1 to p do write(sta[i],' ');
writeln;
readln;
end;


begin


readln(n,p);
sta[1]:=0;
sp:=1;
while sp>0 do
begin
while sta[sp]<n-p+sp do
begin
inc(sta[sp]);
if continuare(sp) then if sp=p then tipareste
                               else begin
                                    inc(sp);
                                    sta[sp]:=0;
                                    end;
end;
sta[sp]:=0;
dec(sp);
end;
end.
