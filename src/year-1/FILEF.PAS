program ff;
{$M 65520,0,0}

uses dos,crt;
var fis:pathstr;
    i:integer;
procedure searchr(path:string);
var f:searchrec;
begin
findfirst(path+'\*',directory,f);
while doserror=0 do
begin
if (f.name<>'.') and (f.name<>'..') then begin
                                         gotoxy(1,1);
                                         write('                                             ');
                                         gotoxy(1,1);
                                         writeln(path+'\'+f.name);
                                         searchr(path+'\'+f.name);
                                         end;
findnext(f);
end;
doserror:=0;
findfirst(path+'\'+fis,$3f,f);
while doserror=0 do
begin
writeln(path+'\'+f.name);
findnext(f);
end;
doserror:=0;
end;
BEGIN
clrscr;
if paramcount<1 then begin
                     writeln('No parameters on command line.No file search will proceed');
                     writeln('Type the file name you want to search');
                     halt;
                     end
                else begin
                     for i:=1 to paramcount do begin
                     fis:=paramstr(i);
                     searchr('c:');
                     writeln('End of searching for file no',i);
                     end;
                     end;
readln;
END.
