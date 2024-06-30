program stars;
uses graph,crt;
const n=100;
      colors:array[1..6] of integer=(3,14,15,10,13,8);
var gd,gm,i,j:integer;
    ch:char;
    a:array[1..n,1..5] of integer;
    speeddim:integer;
    dist,decfactor,planetx,planety:integer;
procedure verify(i:integer);
begin
if a[i,1]<=40 then begin
                 a[i,1]:=round(random*70)+270;
                 a[i,2]:=round(random*50)+80;
                 a[i,3]:=round(random*speeddim)+1;
                 a[i,4]:=round(random*speeddim)+1;
                 a[i,5]:=colors[round(random*6)+1];
                 end;
if a[i,1]>=getmaxx-40 then begin
                          a[i,1]:=round(random*70)+270;
                          a[i,2]:=round(random*50)+80;
                          a[i,3]:=round(random*speeddim)+1;
                          a[i,4]:=round(random*speeddim)+1;
                          a[i,5]:=colors[round(random*6)+1];
                          end;
if a[i,2]>=300 then begin
                          a[i,1]:=round(random*70)+270;
                          a[i,2]:=round(random*50)+80;
                          a[i,3]:=round(random*speeddim)+1;
                          a[i,4]:=round(random*speeddim)+1;
                          a[i,5]:=colors[round(random*6)+1];
                          end;
if a[i,2]<=10 then begin
                          a[i,1]:=round(random*70)+270;
                          a[i,2]:=round(random*50)+80;
                          a[i,3]:=round(random*speeddim)+1;
                          a[i,4]:=round(random*speeddim)+1;
                          a[i,5]:=colors[round(random*6)+1];
                          end;
putpixel(a[i,1],a[i,2],a[i,5]);
end;
procedure verify1;
begin
if speeddim<=1 then speeddim:=1;
if speeddim<=1 then speeddim:=1;
if speeddim>=10 then speeddim:=10;
if speeddim>=10 then speeddim:=10;
end;
procedure hyperspace;
const radius:array[1..6] of integer=(50,53,55,57,59,61);
var i,j,k:integer;
begin
setcolor(15);
for i:=1 to 6 do
for j:=1 to 6 do
for k:=1 to 6 do begin
circle(305,105,radius[j]+i*k);
end;
end;
label cont;
BEGIN
gd:=detect;
initgraph(gd,gm,'c:\language\tp7\bgi');
speeddim:=10;
dist:=200;
decfactor:=1;
for i:=1 to n do begin
a[i,1]:=round(random*70)+270;
a[i,2]:=round(random*50)+80;
a[i,3]:=round(random*speeddim)+1;
a[i,4]:=round(random*speeddim)+1;
a[i,5]:=colors[round(random*6)+1];
end;
setcolor(15);
rectangle(38,8,getmaxx-38,302);
setviewport(39,9,getmaxx-39,301,clipon);
cont:dec(dist,decfactor);
decfactor:=decfactor+5*dist div 1000;
if dist<=5 then begin
               decfactor:=1;
               dist:=200;
               end;
setcolor(15);
circle(250,100,1000 div dist);
for i:=1 to n do begin
if a[i,1]<305 then begin
                             putpixel(a[i,1],a[i,2],0);
                             dec(a[i,1],a[i,3]);
                             verify(i);
                             end;
if a[i,1]>305 then begin
                             putpixel(a[i,1],a[i,2],0);
                             inc(a[i,1],a[i,3]);
                             verify(i);
                             end;
if a[i,2]>105 then begin
                   putpixel(a[i,1],a[i,2],0);
                   inc(a[i,2],a[i,4]);
                   verify(i);
                   end;
if a[i,2]<105 then begin
                   putpixel(a[i,1],a[i,2],0);
                   dec(a[i,2],a[i,4]);
                   verify(i);
                   end;
if keypressed then ch:=readkey
              else ch:=#0;
if ch='q' then for j:=1 to n do begin
               putpixel(a[j,1],a[j,2],0);
               dec(a[j,2],10);
               putpixel(a[j,1],a[j,2],14);
               end;
if ch='z' then for j:=1 to n do begin
               putpixel(a[j,1],a[j,2],0);
               inc(a[j,2],10);
               putpixel(a[j,1],a[j,2],14);
               end;
if ch=' ' then  begin
                inc(speeddim);
                verify1;
                end;
if ch='s' then  begin
                dec(speeddim);
                verify1;
                end;
if ch='h' then hyperspace;
end;

setcolor(0);
circle(250,100,1000 div dist);
goto cont;
end.