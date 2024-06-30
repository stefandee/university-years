program postfix_infix;
const n=100;
      litere=['a'..'z'];
var s1,s2:string;
    as:boolean;
    plop:byte;
    i:integer;
    sta:array[1..n] of char;
    sp:integer;
begin
sp:=1;s2:='';as:=boolean;
write('sirul in forma postfix ?');readln(s1);
for i:=1 to length(s1) do
    begin
         if s1[i] in litere then begin
                                 sta[sp]:=s1[i];
                                 inc(sp);
                                 end;

         case s1[i] of
         '+','-': begin
                  plop:=length(s2);{??!}
                  s2:=s2+sta[sp]+s1[i]+sta[sp-1];
                  dec(sp);
                  as:=true;
                  end;
        '*','/' : begin
                  if as then begin
                             insert(s2,'(',plop);
                             s2:=s2+')';
                             end;


