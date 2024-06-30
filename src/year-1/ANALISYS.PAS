{   2. Se citeste un text terminat cu punct ce contine cuvinte separate prin
blanc, virgula sau terminator de linie. Se cere:
   a) sa se tipareasca in ordine alfabetica cuvintele din text si contoarele
      lor de aparitie
   b) sa se tipareasca toate grupele de anagrame din text.

   Indicatii: un cuvint e anagrama altuia, daca toate caracterele din primul
apar in al doilea si invers,altfel spus daca cuvintele obtinute prin ordonarea
literelor cuvintelor sint identice;
	      ex: Rac, Arc, car e un grup de anagrame
		  Rac => ACR
		  Arc => ACR
		  car => ACR}

program problema;

uses crt;

const n=15;

type reccuv=record
     wor:string;
     app:integer;
     end;
     arr=array[1..n] of reccuv;

var i,j,l,k:integer;
    sir,cuv:string;
    w:arr;

procedure insert(k:integer);

          begin
               for j:=n downto k+1 do w[j]:=w[j-1];
               w[k].wor:=cuv;
               w[k].app:=1;
          end;

procedure searchanag;

var a:arr;
    count:integer;
label x;

begin
a:=w;
writeln('mixed words:');
for i:=1 to n do
    if a[i].wor<>'' then begin
                               write(a[i].wor,' ');
                               for j:=i+1 to n do
                               if a[j].wor<>'' then
                                  if length(a[i].wor)=length(a[j].wor)
                                     then begin
                                          for k:=1 to length(a[i].wor) do
                                          begin
                                          count:=0;
                                          for l:=1 to length(a[i].wor) do
                                          if a[i].wor[l]=a[i].wor[k] then inc(count);
                                          for l:=1 to length(a[i].wor) do
                                          if a[i].wor[k]=a[j].wor[l] then dec(count);
                                          if count<>0 then goto x;
                                          end;
                                          write(a[j].wor,' ');
                                          a[j].wor:='';
                                          x:end;
                              writeln;
                              end;

          end;

label last;
begin
clrscr;
write('enter string for analisys:');
read(sir);

for i:=1 to n do
    with w[i] do
         begin
              w[i].wor:='';
              w[i].app:=0;
         end;
cuv:='';

for i:=1 to length(sir) do
case sir[i] of
'.': begin
     writeln;
     writeln('listing word of strings in alphabetical order:');
     for i:=1 to n do if w[i].wor<>'' then writeln('word ',w[i].wor,' appears ',w[i].app, ' time(s)');
     writeln;
     searchanag;
     exit;
     end;
',',' ': begin
         if cuv<w[1].wor then begin
                              insert(1);
                              goto last;
                              end;
         if cuv=w[1].wor then begin
                              inc(w[1].app);
                              goto last;
                              end;
         for l:=1 to n do
             begin
                  if (cuv>w[l].wor) and ((cuv<w[l+1].wor) or (w[l+1].wor=''))
                                        then begin
                                             insert(l+1);
                                             goto last;
                                             end;
                  if cuv=w[l].wor then begin
                                       inc(w[l].app);
                                       goto last;
                                       end;
             end;
        last:cuv:='';
           end;

    else cuv:=cuv+sir[i];
end;
readln;
end.
