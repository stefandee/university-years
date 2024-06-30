PROGRAM x;

uses crt;

type rez=(gresit,intreg,nr_real,cuvant,gata);


var cnti,cntc,cntr,cntg:integer;
    suma,nr:real;
    lin:rez;

function CITLIN:rez;

var s:string;
    cifr,litr,point,i:integer;
begin

 readln(s);
 cifr:=0;litr:=0;point:=0;
 citlin:=gresit;
 if length(s)=0 then begin
                     citlin:=gata;
                     exit;
                     end;
 
 for i:=1 to length(s) do
     begin
          if (ord(s[i])<=ord('9')) and (ord(s[i])>=ord('0')) then inc(cifr);
          if (ord(s[i])<=ord('z')) and (ord(s[i])>=ord('A')) then inc(litr);
          if s[i]='.' then inc(point);
     end;

 if cifr=length(s) then begin
                        citlin:=intreg;
                        exit;
                        end;
 if (point=1) and (cifr=length(s)-1) and (cifr<>0) then begin
                                      citlin:=nr_real;
                                      val(s,nr,i);
                                      exit;
                                      end;
 if litr=length(s) then begin
                        citlin:=cuvant;
                        exit;
                        end;
 

end;

BEGIN

clrscr;
cntg:=0;cnti:=0;cntc:=0;cntr:=0;
suma:=0;
lin:=citlin;

while lin<>gata do
      begin
           case lin of
           gresit:inc(cntg);
           intreg:inc(cnti);
           nr_real:begin
                   inc(cntr);
                   suma:=suma+nr;
                   end;
           cuvant:inc(cntc);
           end;
      lin:=citlin;
      end;

writeln('nr.de intregi este ',cnti);
if cntr<>0 then writeln('nr.de reali este ',cntr,' si media lor este ',suma/cntr:3:3)
           else writeln('nr.de reali este 0');
writeln('nr.de cuvinte este ',cntc);
writeln('nr.de greseli este ',cntg);
readln;

END.
