{$M 65520,0,655360}
{$R+}
{$S+}
Program
       Use;
Uses
    F_Table,Compress,Dos,Utils,crt;
Var
   i : word;
   F : TEXT;
Begin
 FileMode := 0;
 InTheBeggining;
 if paramcount=0
    then begin
          Help;
          halt;
         end;
 if paramcount=1
    then if (paramstr(1)='?') or (paramstr(1)='-?') or
            (paramstr(1)='/?') or (paramstr(1)='-h') or
            (paramstr(1)='/h')
            then begin
                  Help;
                  halt;
                 end;

 if paramstr(1)='e'
    then begin
          case paramcount of
           3 : HuffMann_UnPak(paramstr(3),paramstr(2));
           2 : HuffMann_UnPak(paramstr(2),'');
           1 : begin
                TextColor(15);
                writeln('MAIN error : missing source/destination files');
                TextColor(7);
                halt;
               end;
          end;
         end
    else if paramstr(1)='a'
            then HuffMann_Pack(paramstr(3),paramstr(2))
            else if paramstr(1)='l'
                    then HuffMann_List(paramstr(2))
                    else begin
                          TextColor(15);
                          writeln('MAIN error : unknown command "'+paramstr(1),'"');
                          TextColor(7);
                          writeln;
                          Help;
                          halt;
                         end;

End.