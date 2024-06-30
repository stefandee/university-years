UNIT
    COMPRESS;

INTERFACE
{$R+}
USES
    F_Table,Utils,Dos,Crt;

CONST
     STORED = 0;
     PAK_1  = 1;
     NONE   = 255;

TYPE
    TSign = array[1..8] of char;
    Code_Entry = record
               code    : longint;
               clength : byte;
               end;
    Aux_Code_Entry = record
                   whatchar: char;
                   code    : longint;
                   clength : byte;
                   end;
    Header = record
           sign    : TSign;
           unpak   : longint;
           pak     : longint;
           method  : byte;
           Attr    : Byte;
           Time    : Longint;
           Name    : string [12];
           end;
    Code_Array = array[1..32] of byte;

CONST
     Sign   : TSign = 'KAPA!;-)';
     
VAR
   Code_Table     : array[0..255] of Code_Entry;
   Aux_Code_Table : array[0..255] of Aux_Code_Entry;
   PackedLen      : comp;
   Hdr            : Header;

FUNCTION  Build_Huffmann_Tree : boolean;
PROCEDURE Build_Code_Table(index : integer;clen : integer);
PROCEDURE Code_To_File; { for verify *only* }
PROCEDURE Huffmann_Pack(Paths,Pathd : PathStr);
PROCEDURE Huffmann_UnPak(PathS,PathD : PathStr);
PROCEDURE Huffmann_List(PathS : PathStr);

IMPLEMENTATION

VAR
   CA : Code_Array;

FUNCTION Build_Huffmann_Tree : boolean;
VAR
   fbuffer   : array[1..2] of longint;
   ibuffer   : array[1..2] of longint;
   use1,use2 : boolean;
   i         : integer;
BEGIN
 Build_Huffmann_Tree := false;
 fbuffer[1] := -100;ibuffer[1] :=  -100;fbuffer[2] := -100;ibuffer[2] :=  -100;
 use1 := true;use2 := true;
 { se afla cele mai mici frecvente ; use1 si use2 se folosesc pentru
   a optimiza cautarea }
 for i:=0 to lastindex do
     with FTab[i] do
           if use
              then if use1
                      then begin
                            use1       := false;
                            fbuffer[1] := freq;
                            ibuffer[1] := i;
                           end
                      else if use2
                           then begin
                                 use2       := false;
                                 fbuffer[2] := freq;
                                 ibuffer[2] := i;
                                end
                           else if freq<fbuffer[2]
                                   then begin
                                         fbuffer[2] := freq;
                                         ibuffer[2] := i;
                                        end
                                   else if freq<fbuffer[1]
                                           then begin
                                                 fbuffer[1] := freq;
                                                 ibuffer[1] := i;
                                                end;

 if not use1 then FTab[ibuffer[1]].use := false;
 if not use2 then FTab[ibuffer[2]].use := false;

 {for i:=0 to lastindex do
     with FTab[i] do
           if use
              then if use2
                      then begin
                            use2       := false;
                            fbuffer[2] := freq;
                            ibuffer[2] := i;
                           end
                      else if freq<fbuffer[2]
                              then begin
                                    fbuffer[2] := freq;
                                    ibuffer[2] := i;
                                   end;}

 if use1 or use2
    then begin
          Build_Huffmann_Tree := true;
          exit;
         end;

 inc(lastindex);
 with FTab[lastindex] do
      begin
       l    := ibuffer[1];
       r    := ibuffer[2];
       c    := #0;
       freq := fbuffer[1] + fbuffer[2];
       use  := true;
      end;
END;

PROCEDURE Build_Code_Table;
VAR
   i : integer;
BEGIN
 if (FTab[index].l<0) and (Ftab[index].r<0)
    then begin
          { s-a ajuns la nod terminal }
          Code_Table[index].code := 0;
          Code_Table[index].clength := clen-1;
          for i:=1 to clen-1 do
              case CA[i] of
               0 : begin
                    {Code_Table[index].code := Code_Table[index].code or 0;}
                    Code_Table[index].code := Code_Table[index].code shl 1;
                   end;
               1 : begin
                    Code_Table[index].code := Code_Table[index].code shl 1;
                    Code_Table[index].code := Code_Table[index].code or 1;
                   end;
              end;
         end
    else begin
          {if clen>8
             then begin
                   Code_To_File;
                   writeln('Code overflow at index ',index);
                   halt;
                  end;}
          CA[clen] := 1;
          Build_Code_Table(FTab[index].l,clen+1);
          CA[clen] := 0;
          Build_Code_Table(FTab[index].r,clen+1);
         end;
END;

PROCEDURE Code_To_File;
VAR
   F      : Text;
   i      : integer;
   sum    : longint;
BEGIN
 Assign(F,'codes.txt');
 ReWrite(F);
 sum := 0;
 for i:=0 to 255 do
     begin
      if i<32
         then writeln( F,'(',Int2Str(i),')','...',Int2Str(FTab[i].freq),'...',Int2Str(Code_Table[i].code),'...',
                       Int2Str(Code_Table[i].clength))
         else writeln( F,char(i),'...',Int2Str(FTab[i].freq),'...',Int2Str(Code_Table[i].code),'...',
                       Int2Str(Code_Table[i].clength));
      sum := Code_Table[i].clength*FTab[i].freq+sum
     end;
 writeln(' ',Int2Str(sum),' biti(',Int2Str(sum div 8),' bytes)');
 close(F);
END;

PROCEDURE Huffmann_Pack(Paths,Pathd : PathStr);
VAR
   FS,FD      : FILE;
   F          : SearchRec;
   Pack_F_Num : longint;
   DirS       : DirStr;
   NameS      : NameStr;
   ExtS       : ExtStr;
   DirD       : DirStr;
   NameD      : NameStr;
   ExtD       : ExtStr;
   FSize      : longint;
   ignore     : boolean;
   Delta,i,j  : longint;
   crt_bit    : longint;
   proc_bit   : longint;

BEGIN
 for i:=1 to length(PathS) do PathS[i]:=UPCASE(PathS[i]);
 for i:=1 to length(PathD) do PathD[i]:=UPCASE(PathD[i]);
 FSplit(PathS,DirS,NameS,ExtS);
 FSplit(PathD,DirD,NameD,ExtD);
 if ExtD='' then ExtD:='.K';
 PathD := DirD+NameD+ExtD;
 if DirS=DirD then ignore := true
    else ignore := false;
 Pack_F_Num := 0;
 CreateFile(Fd,PathD);
 {SeekFile(Fd,SizeFile(Fd));}
 Hdr.Sign:=Sign;
 FindFirst(PathS,$3F,F);
 while (doserror=0) do
       begin
        if ((F.Name<>'.') and (F.Name<>'..')) then
           if ((F.Name<>NameD+ExtD) and (ignore=true)) or (ignore=false)
           then begin
                 inc(Pack_F_Num);
                 OpenFile(Fs,DirS+F.Name);
                 { allign the messages }
                 write('Adding   '+F.Name);
                 for i:=1 to 12-length(F.Name) do write(' ');

                 { do the analyzeof file }
                 Analyze_4_Frequency(DirS+F.Name);
                 repeat
                 until Build_Huffmann_Tree;
                 Build_Code_Table(lastindex,1);

                 { fill in the header }
                 with Hdr do
                      begin
                       Time   := F.Time;
                       UnPak  := F.Size*8;
                       Pak    := 0;{ !!! }
                       Attr   := F.Attr;
                       Name   := F.Name;
                      end;

                 { compute the length of the encoded file in bits }
                 for i:=0 to 255 do
                      Hdr.Pak := Code_Table[i].clength*FTab[i].freq+Hdr.Pak;

                 { choose the method : storage or pak }
                 if Hdr.Pak+Sizeof(Code_Table)*8+SizeOf(Hdr)*8>=Hdr.UnPak
                    then begin
		           Hdr.method := STORED;
                           Hdr.Pak    := Hdr.UnPak;
                          end
                    else Hdr.method := PAK_1;
                 { header is complete, write it to file }
                 WriteFile(Fd,Hdr,SizeOf(Hdr));

                 { another allign }
                 write('   00.0');
                 FSize := 0;
                 SeekFile(Fs,0);

                 case Hdr.method of
                  PAK_1  : begin
                            { pak the file }
                            proc_bit := 0;
                            WriteFile(Fd,Code_Table,SizeOf(Code_Table));
                            repeat
                             if filesize(Fs)-FSize>65000
                                then begin
                                      Delta := 65000;
                                      ReadFile(Fs,InBuf^,65000);
                                      inc(FSize,65000);
                                     end
                                else begin
                                      Delta := SizeFile(Fs)-FSize;
                                      ReadFile(Fs,InBuf^,Delta);
                                      FSize := SizeFile(Fs);
                                    end;
                             { packing }
                             crt_bit := 0;
                             for i:=1 to Delta do
                                 begin
                                  for j:=Code_Table[inbuf^[i]].clength-1 downto 0 do
                                      begin
                                       SetBit(outbuf^[1+crt_bit div 8],7-crt_bit mod 8,getbit(Code_Table[inbuf^[i]].code,j));
                                       inc(crt_bit);
                                       inc(proc_bit);
                                       if crt_bit>=8*65000
                                          then begin
                                                WriteFile(Fd,outbuf^,65000);
                                                crt_bit := 0;
                                               end;
                                      end;
                                  if proc_bit+1024<Hdr.UnPak
                                     then begin
                                           write(#8#8#8#8#8);
                                           write(proc_bit*100/Hdr.UnPak:4:1,'%');
                                          end;
                                 end;
                             if crt_bit<>0 then WriteFile(Fd,outbuf^,crt_bit div 8+1);
                            until FSize = SizeFile(Fs);
                           end;
                  STORED : begin
                            { store the file }
                            repeat
                             if filesize(Fs)-FSize>65000
                                then begin
                                      ReadFile(Fs,InBuf^,65000);
                                      WriteFile(Fd,InBuf^,65000);
                                      inc(FSize,65000);
                                     end
                                else begin
                                      ReadFile(Fs,InBuf^,SizeFile(Fs)-FSize);
                                      WriteFile(Fd,InBuf^,SizeFile(Fs)-FSize);
                                      FSize := SizeFile(Fs);
                                      {write(#8#8#8#8#8);
                                      write(FSize*100/SizeFile(Fs):4:1,'%');
                                      }
                                    end;
                             write(#8#8#8#8#8);
                             if SizeFile(Fs)<>0 then write(FSize*100/SizeFile(Fs):4:1,'%')
                                else write(FSize*100/(SizeFile(Fs)+1):4:1,'%');
                            until FSize=SizeFile(Fs);
                            write(' Stored');
                           end;
                 end;
                 close(Fs);
                 writeln;
                end;
        FindNext(F);
       end;

 case Pack_F_Num of
  0 : writeln('   No files found.');
  1 : writeln('   1 file.');
  else begin
        writeln('   ',Pack_F_Num,' files.');
       end;
 end;
 close(Fd);
END;


PROCEDURE Huffmann_List(PathS : PathStr);
VAR
   DirS       : DirStr;
   NameS      : NameStr;
   ExtS       : ExtStr;
   FS         : FILE;
   FPos       : longint;
   i          : integer;
   Pack_F_Num : longint;
BEGIN
 FSplit(PathS,DirS,NameS,ExtS);
 if ExtS='' then ExtS:='.k';
 PathS := DirS+NameS+ExtS;
 Pack_F_Num := 0;
 OpenFile(FS,PathS);
 writeln('Archive ',PathS,' contains : ');
 TextColor(15);
 writeln('Files         UnPacked     Packed       Ratio');
 writeln('------------- ------------ ------------ ------');
 TextColor(7);
 repeat
  ReadFile(FS,Hdr,sizeof(Hdr));

  { check the signature }
  for i:=1 to 8 do
      if Sign[i]<>Hdr.Sign[i]
         then begin
               writeln('Huffmann_List error : cannot recognize signature.');
               halt;
              end;

  { write the info }
  inc(Pack_F_Num);
  write(Hdr.Name);
  for i:=1 to 2+12-length(Hdr.Name) do write(' ');
  write(Hdr.UnPak div 8);
  for i:=1 to 13-length(Int2Str(Hdr.UnPak div 8)) do write(' ');
  write(Hdr.Pak div 8);
  for i:=1 to 13-length(Int2Str(Hdr.Pak div 8)) do write(' ');
  writeln(100*Hdr.Pak/Hdr.UnPak:3:1,'%');

  { seek the next record }
  if Hdr.method=PAK_1
     then SeekFile(FS,FilePos(FS)+Hdr.Pak div 8+1+Sizeof(Code_Table))
     else SeekFile(FS,FilePos(FS)+Hdr.UnPak div 8);

 until FilePos(FS)=FileSize(FS);

 case Pack_F_Num of
  0 : writeln('   No files found.');
  1 : writeln('   1 file.');
  else begin
        writeln('   ',Pack_F_Num,' files.');
       end;
 end;
END;

PROCEDURE Sort_Aux_Code_Table;
VAR
   i,j : integer;
   Ace : Aux_Code_Entry;
BEGIN
 for i:=0 to 255 do
     begin
      Aux_Code_Table[i].whatchar:= char(i);
      Aux_Code_Table[i].code    := Code_Table[i].code;
      Aux_Code_Table[i].clength := Code_Table[i].clength;
     end;
 for i:=0 to 254 do
     for j:=i+1 to 255 do
         if Aux_Code_Table[i].clength>Aux_Code_Table[j].clength
            then begin
                  Ace := Aux_Code_Table[i];
                  Aux_Code_Table[i] := Aux_Code_Table[j];
                  Aux_Code_Table[j] := Ace;
                 end;
END;

PROCEDURE Huffmann_UnPak(PathS,PathD : PathStr);
VAR
   DirS       : DirStr;
   NameS      : NameStr;
   ExtS       : ExtStr;
   FS,FD      : FILE;
   FPos       : longint;
   i,j        : longint;
   Pack_F_Num : longint;
   FSize,FEnd : longint;
   crt_bit    : longint;
   crt_byte   : longint;
   TotalLen   : longint;
   CurentLen  : longint;
   octet1     : longint;
   octet2     : longint;
   pos        : longint;
   code_temp  : longint;
   counters   : array[1..8] of longint;
   xcount     : byte;

LABEL
     nextcode,anotheread;

BEGIN
 FSplit(PathS,DirS,NameS,ExtS);
 if ExtS='' then ExtS:='.K';
 PathS := DirS+NameS+ExtS;
 Pack_F_Num := 0;
 OpenFile(FS,PathS);
 if PathD<>'' then if PathD[length(PathD)]<>'\' then PathD:=PathD+'\';
 repeat
  ReadFile(FS,Hdr,sizeof(Hdr));

  { check the signature }
  for i:=1 to 8 do
      if Sign[i]<>Hdr.Sign[i]
         then begin
               writeln('Huffmann_List error : cannot recognize signature.');
               halt;
              end;
  inc(Pack_F_Num);
  CreateFile(Fd,PathD+Hdr.Name);
  write('Extracting ',Hdr.Name);
  for i:=1 to 13-length(Hdr.Name) do write(' ');
  write(' to ',PathD+Hdr.Name);

  { another allign }
  write('   00.0');

  { seek the next record }
  if Hdr.method=PAK_1
     then begin
           ReadFile(FS,Code_Table,sizeof(Code_table));
           Sort_Aux_Code_Table;
           FSize    := FilePos(Fs);
           FEnd     := FSize+Hdr.Pak div 8+1;
           TotalLen := Hdr.UnPak div 8;
           CurentLen:= 0;
           crt_bit  := 0;
           crt_byte := 1;

           repeat
            if FEnd-FSize>65004
               then begin
                     blockread(Fs,InBuf^,65004);
                     inc(FSize,65004);
                    end
               else begin
                     blockread(Fs,InBuf^,FEnd-FSize);
                     FSize := FEnd;
                    end;

            for i:=0 to 7 do counters[i+1] := 32*i;
            xcount := 1;

            repeat
             for j:=Aux_Code_Table[counters[xcount]].clength-1 downto 0 do
                 begin
                  octet1 := InBuf^[(Aux_Code_Table[counters[xcount]].clength-1-j+crt_bit) div 8 +1];
                  pos := 7-(Aux_Code_Table[counters[xcount]].clength-1-j+crt_bit) mod 8;
                  pos := 1 shl pos;
                  octet1 := octet1 and pos;

                  octet2 := Aux_Code_Table[counters[xcount]].code;
                  pos := j;
                  pos := 1 shl pos;
                  octet2 := octet2 and pos;
                  if ((octet1=0) and (octet2<>0)) or
                     ((octet1<>0) and (octet2=0))
                     then goto nextcode;
                 end;
                 {if GetBit(InBuf^[(Code_Table[i].clength-1-j+crt_bit) div 8+1],7-(Code_Table[i].clength-1-j+crt_bit) mod 8) <>
                    GetBit(Code_Table[i].code,j)
                    then goto nextcode;}

             OutBuf^[crt_byte] := byte(Aux_Code_Table[counters[xcount]].whatchar);

             inc(CurentLen);
             inc(crt_byte);
             if crt_byte>65004
                then begin
                      WriteFile(Fd,OutBuf^,65004);
                      crt_byte := 1;
                     end;

             inc(crt_bit,Aux_Code_Table[counters[xcount]].clength);
             if crt_bit>=Hdr.Pak
                then begin
                     { still to come ... for 64k pak files}
                     WriteFile(Fd,OutBuf^,crt_byte-1);
                     goto anotheread;
                     end;

            if CurentLen<TotalLen
               then begin
                     write(#8#8#8#8#8#8);
                     write(CurentLen*100/TotalLen:5:1,'%');
                    end;
             counters[xcount] := (xcount-1)*32-1;
            nextcode:
             inc(counters[xcount]);
             if counters[xcount]>=xcount*32 then counters[xcount] := (xcount-1)*32;
             inc(xcount);
             if xcount>8 then xcount := 1;
            until counters[8]>255;
            writeln(#13#10'Huffmann_UnPak error : Bad Huffmann code !');
            halt;
           {SeekFile(FS,FilePos(FS)+Hdr.Pak div 8+1);}
           anotheread:
           until FEnd=FSize;
           close(Fd);
           writeln;
          end
     else begin
           { store the file }
           FSize := Utils.FilePos(Fs);
           FEnd  := FSize+Hdr.Unpak div 8;
           repeat
            if FEnd-FSize>65000
               then begin
                     ReadFile(Fs,InBuf^,65000);
                     WriteFile(Fd,InBuf^,65000);
                     inc(FSize,65000);
                    end
               else begin
                     ReadFile(Fs,InBuf^,FEnd-FSize);
                     WriteFile(Fd,InBuf^,FEnd-FSize);
                     FSize := FEnd;
                   end;
            write(#8#8#8#8#8);
            if FEnd<>0 then write(FSize*100/FEnd:4:1,'%')
               else write(FSize*100/(FEnd+1):4:1,'%');
           until FSize=FEnd;
           {SeekFile(FS,FilePos(FS)+Hdr.UnPak div 8);}
           close(Fd);
           writeln;
          end;

 until FilePos(FS)=FileSize(FS);

 case Pack_F_Num of
  0 : writeln('   No files found.');
  1 : writeln('   1 file.');
  else begin
        writeln('   ',Pack_F_Num,' files.');
       end;
 end;
END;

BEGIN
END.