program decoder;
uses crt;
var pos:integer;
    let,semn_morse,afis,mesaj,st:string;
function decode(let:string):char;
begin
decode:=' ';
if semn_morse='l' then decode:='a';
if semn_morse='lppp' then decode:='b';
end;
function search:string;
var posi:integer;
begin
posi:=pos;
let:='';
repeat
let:=let+mesaj[pos];
inc(pos);
until mesaj[pos]<>mesaj[posi];
search:=let;
end;
begin
clrscr;
pos:=1;
mesaj:='111000111010101000111010101000111000001110000000';
semn_morse:='';afis:='mesajul este : ';
repeat
st:=search;
if st='0000000' then begin
                     afis:=afis+decode(semn_morse);
                     writeln(afis);
                     readln;
                     halt;
                     end;

if st='00000' then begin
                   afis:=afis+decode(semn_morse)+' ';
                   semn_morse:='';
                   end;

if st='000' then begin
                 afis:=afis+decode(let);
                 semn_morse:='';
                 end;

if st='111' then semn_morse:=semn_morse+'l';

if st='1' then semn_morse:=semn_morse+'p';

until pos>length(mesaj);
readln;

end.
