UNIT
       F_Table;

INTERFACE

USES
    UTILS,DOS;

TYPE
    Node = record
         c    : char;
         l,r  : integer;
         freq : longint;
         use  : boolean;
         end;
    Frequency_Table = array[0..512] of Node;

VAR
   FTab            : Frequency_Table;
   LastIndex       : longint;

PROCEDURE Analyze_4_Frequency(FStr : PathStr);

IMPLEMENTATION


PROCEDURE Analyze_Buffer_Frequency(Size : word);
VAR
   i   : longint;
   s,o : word;
BEGIN
 s := seg(FTab);o := ofs(FTab);
 asm
  push ds
  push es
  lds si,inbuf
  mov ax,s
  mov es,ax
  mov di,o
  mov dx,1
  xor ax,ax

  mov cx,Size
@ABF:
  xor bh,bh
  mov bl,ds:[si]
  mov ax,10
  mul bx
  mov bx,ax
  mov dx,1
  add es:[di+bx+5],dx
  xor dx,dx
  adc es:[di+bx+7],dx
  inc si
  loop @ABF
  pop es
  pop ds
 end;
 {for i:=1 to Size do inc(FTab[InBuf^[i]].freq);}
END;

PROCEDURE Init_F_Table;
VAR
   i : integer;
BEGIN
 for i:=0 to 512 do
     with FTab[i] do
          begin
           freq := 0;
           l    := -100;{ nil pointer - terminal node }
           r    := -100;
           c    := char(i mod 256);
           use  := true;
          end;
END;

PROCEDURE Analyze_4_Frequency(FStr : PathStr);
VAR
   F      : FILE;
   FSize  : longint;
   FRes   : Text;
   i      : integer;
   verify : longint;
BEGIN
 Init_F_Table;
 OpenFile(F,FStr);
 FSize := 0;
 repeat
  if filesize(F)-FSize>65000
     then begin
           ReadFile(F,InBuf^,65000);
           Analyze_Buffer_Frequency(65000);
           inc(FSize,65000);
          end
    else begin
          ReadFile(F,InBuf^,filesize(F)-FSize);
          Analyze_Buffer_Frequency(filesize(F)-FSize);
          FSize := filesize(F);
         end;
 until FSize=filesize(F);
 close(F);
 lastindex := 255;
 { visual part - remove it any time }
 {assign(FRes,'result.txt');
 rewrite(FRes);
 verify := 0;
 for i:=0 to 255 do
     begin
      if i<32 then writeln(FRes,'(',Int2Str(i),')','.....',Int2Str(FTab[i].freq))
         else writeln(FRes,char(i),'.....',Int2Str(FTab[i].freq));
      verify := verify + FTab[i].freq;
     end;
 writeln(FRes,'Sum of frequencies ',Int2Str(verify),' File length ',FSize);
 close(FRes);}
END;

BEGIN
 new(InBuf);
 new(OutBuf);
END.