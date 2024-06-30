UNIT
    UTILS;

INTERFACE

USES
    DOS,CRT;

TYPE
    FileStr = string[12];{ nume(8) + extensie(3) }
    Buffer = array[1..65004] of byte;

VAR
   InBuf,OutBuf    : ^Buffer;
   

FUNCTION Int2Str(v : longint) : STRING;
PROCEDURE OpenFile(var F : FILE;Path : PathStr);
PROCEDURE CreateFile(var F : FILE;Path : PathStr);
PROCEDURE ReadFile(var F : FILE;var buf;count : word);
PROCEDURE WriteFile(var F : FILE;var buf;count : word);
PROCEDURE SeekFile(var F : FILE;pos : longint);
FUNCTION FileExist(Path : PathStr) : boolean;
FUNCTION FilePos(var F : FILE) : longint;
FUNCTION SizeFile(var F : FILE) : longint;
PROCEDURE EraseFile(var F : FILE);
PROCEDURE SetBit(var octet : byte;pos : longint;val : byte);
FUNCTION GetBit(octet : longint;pos : longint) : byte;
FUNCTION What_DosError(de : integer) : boolean;
PROCEDURE InTheBeggining;
PROCEDURE Help;

IMPLEMENTATION

function What_DosError(de : integer) : boolean;
BEGIN
 What_DosError := true;
 case de of
   2 : writeln('IO error : File not found');
   3 : writeln('IO error : Path not found');
   5 : writeln('IO error : Access denied');
   6 : writeln('IO error : Invalid handle');
   8 : writeln('IO error : Not enough memory');
  10 : writeln('IO error : Invalid environment');
  11 : writeln('IO error : Invalid format');
  18 : writeln('IO error : No more files');
   else What_DosError := false;
 end;
END;

FUNCTION Int2Str(v : longint) : STRING;
VAR
   aux : string;
BEGIN
 Str(v,aux);
 Int2Str:=aux;
END;

PROCEDURE OpenFile(var F : FILE;Path : PathStr);
var
   de : integer;
BEGIN
 Assign(F,Path);
 {$I-}
 Reset(F,1);
 if ioresult<>0
    then begin
          writeln('OPENFILE error : Unable to handle file '+Path);
          halt;
         end;
 {$I+}
END;

PROCEDURE ReadFile(var F : FILE;var buf;count : word);
BEGIN
 {$I-}
 blockread(f,buf,count);
 if ioresult<>0
    then begin
          writeln('READFILE error : Unable to read from file ');
          halt;
         end;
 {$I+}
END;

PROCEDURE WriteFile(var F : FILE;var buf;count : word);
BEGIN
 {$I-}
 blockwrite(f,buf,count);
 if ioresult<>0
    then begin
          writeln('WRITEFILE error : Unable to write to file ');
          halt;
         end;
 {$I+}
END;

PROCEDURE InTheBeggining;
BEGIN
 TextColor(15);write('Ka');TextColor(7);write('rg''s ');TextColor(15);write('Pa');TextColor(7);writeln('cker');
 TextColor(14);
 writeln('Utilitar pentru compresia fisierelor.');
 writeln('Realizat in martie ''97 pentru scopuri exclusiv didactice.');
 writeln( 'Programul este freeware,putind fi folosit sau raspindit fara nici o aprobare din'+
          'partea autorului.');
 TextColor(12);
 writeln('***Programul este furnizat AS IS si nu implica nici o garantie de calitate'+
           ' din partea autorului.Prin urmare, nu poate fi invinuit de nici o stricaciune'+
           ' pe care ar provoaca-o datelor/computerului dv.Adica il folositi pe raspunderea dv!***');
 writeln('***Folositi acest program cu foarte mare grija si salvati-va datele cit de des puteti.***');
 TextColor(7);write(' ');writeln;
END;

PROCEDURE SetBit(var octet : byte;pos : longint;val : byte);
BEGIN
 case val of
  0 : begin
       pos := 1 shl pos;
       pos := not pos;
       octet := octet and pos;
      end;
  1 : begin
       pos := 1 shl pos;
       octet := octet or pos;
      end;
 end;
END;

FUNCTION GetBit(octet : longint;pos : longint) : byte;
BEGIN
 pos := 1 shl pos;
 octet := octet and pos;
 if octet=0 then GetBit := 0
    else GetBit := 1;
END;

FUNCTION SizeFile(var F : FILE) : longint;
BEGIN
 {$I-}
 SizeFile := filesize(F);
 if ioresult<>0
    then begin
          writeln('FILESIZE error : Unable to handle file.');
          halt;
         end;
 {$I+}
END;

FUNCTION FileExist(Path : PathStr) : boolean;
VAR
   Dir   : DirStr;
   Name  : NameStr;
   Ext   : ExtStr;

BEGIN
 FSplit(Fexpand(Path),Dir,Name,Ext);
 Path:=FSearch(Dir+Name+Ext,'');
 if Path='' then FileExist:=false
    else FileExist := true;
END;

PROCEDURE CreateFile(var F : FILE;Path : PathStr);
VAR
   key : char;
LABEL
     again;
BEGIN
again:
 if FileExist(Path)
    then begin
          repeat
           write('File '+Path+' already exist.');TextColor(15);write('O');TextColor(7);
           write('verwrite,');TextColor(15);write('r');TextColor(7);write('ename,');TextColor(15);
           write('q');TextColor(7);writeln('uit ?');
           key := UPCASE(readkey);
          until (key='O') or (key='Q') or (key='R');
          case key of
           'O' : begin
                  Assign(F,Path);
                  EraseFile(F);
                  {$I-}
                  Rewrite(F,1);
                  if ioresult<>0
                     then begin
                           writeln('CREATEFILE error : Unable to create file '+Path);
                           halt;
                          end;
                  {$I+}
                 end;
           'Q' : begin
                  writeln('Exiting by user request on CREATEFILE...');
                  halt;
                 end;
           'R' : begin
                  write('Enter ');TextColor(15);write('new');TextColor(7);write(' name : ');readln(Path);
                  goto again;
                 end;
          end;
         end
    else begin
          Assign(F,Path);
          {$I-}
          Rewrite(F,1);
          if ioresult<>0
             then begin
                   writeln('CREATEFILE error : Unable to create file '+Path);
                   halt;
                  end;
          {$I+}
         end;
END;

FUNCTION FilePos(var F : FILE) : longint;
BEGIN
 {$I-}
 FilePos := System.FilePos(F);
 if ioresult<>0
    then begin
          writeln('FILEPOS error : Unable to find out position in file.');
          halt;
         end;
 {$I+}
END;

PROCEDURE SeekFile(var F : FILE;pos : longint);
BEGIN
 {$I-}
 Seek(F,pos);
 if ioresult<>0
    then begin
          writeln('SEEKFILE error : Unable to seek in file.');
          halt;
         end;
 {$I+}
END;

PROCEDURE EraseFile(var F : FILE);
BEGIN
 {$I-}
 Erase(F);
 if ioresult<>0
    then begin
          writeln('ERASEFILE error : Unable to erase file.');
          halt;
         end;
 {$I+}
END;

PROCEDURE Help;
BEGIN
 writeln('Command line should look like :');
 TextColor(15);
 writeln('kapa <command> <destination file> <source file(s)>');
 TextColor(7);
 writeln;
 writeln('Commands are :');
 writeln('?,/?,-?,/h,-h   - shows this help screen');
 writeln('a               - add files _source file(s)_ to archive _destination file_');
 writeln('l               - list the contents of _source file_ archive');
 writeln('e               - extract files from _source file_ archive');
END;

BEGIN
END.
