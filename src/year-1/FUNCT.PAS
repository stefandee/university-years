unit funct;
{+R}
interface
uses graph,crt;
var zoom,funcount:integer;
    drawover,drawtype:boolean;
    paramval:array[1..6] of integer;
procedure fusee(beg,fin:real);
procedure strofoida(beg,fin:real);
procedure cicloida(beg,fin:real);
procedure astroida(beg,fin:real);
procedure trismac(beg,fin:real);
procedure lemniscata(beg,fin:real);
procedure trilong(beg,fin:real);
procedure epicicl(beg,fin:real);
procedure hipocicl(beg,fin:real);
procedure concoida(beg,fin:real);
implementation
var points:array[1..900,1..2] of longint;
    i:integer;
    count:real;
procedure delant;
begin
setfillstyle(1,black);
bar(getmaxx div 2-150,getmaxy div 2-100,getmaxx div 2+150,getmaxy div 2+100);
end;
procedure putpoint(pos:integer);
begin
if drawtype=true then begin
                    setviewport(getmaxx div 2-150,getmaxy div 2-100,getmaxx div 2+150,getmaxy div 2+100,clipon);
                    putpixel(points[pos,1],points[pos,2],white);
                    setviewport(0,0,getmaxx,getmaxy,clipon);
                    end;
if drawtype=false then if (pos<>1) and (pos<900) then
                       begin
                       setviewport(getmaxx div 2-150,getmaxy div 2-100,getmaxx div 2+150,getmaxy div 2+100,clipon);
                       setcolor(15);
                       moveto(points[pos-1,1],points[pos-1,2]);
                       lineto(points[pos,1],points[pos,2]);
                       setviewport(0,0,getmaxx,getmaxy,clipon);
                       end;
end;
procedure fusee(beg,fin:real);
begin
if drawover=false then delant;
count:=beg;
i:=0;
repeat
inc(i);
count:=count+1;
points[i,1]:=150+round(zoom*cos((paramval[1]/10)*count)*cos(count)*cos(count));
points[i,2]:=100+round(zoom*cos((paramval[1]/10)*count)*cos(count)*sin(count));
putpoint(i);
until count>abs(fin)+abs(beg)
end;
procedure strofoida(beg,fin:real);
begin
if drawover=false then delant;
count:=beg;
i:=0;
repeat
inc(i);
count:=count+1;
points[i,1]:=150+round(zoom*(paramval[1]/10)*(1+sin(count)));
points[i,2]:=100+round(zoom*(paramval[1]/10)*(sin(count)/cos(count)+sin(count)*sin(count)/cos(count)));
putpoint(i);;
until count>abs(fin)+abs(beg)
end;
procedure astroida(beg,fin:real);
begin
if drawover=false then delant;
count:=beg;
i:=0;
repeat
inc(i);
count:=count+1;
points[i,1]:=150+round(zoom*(paramval[1]/10)*cos(count)*cos(count)*cos(count));
points[i,2]:=100+round(zoom*(paramval[1]/10)*sin(count)*sin(count)*sin(count));
putpoint(i);;
until count>abs(fin)+abs(beg)
end;
procedure cicloida(beg,fin:real);
begin
if drawover=false then delant;
count:=beg;
i:=0;
repeat
inc(i);
count:=count+1;
points[i,1]:=150+round(zoom*((paramval[1]/10)*count-(paramval[2]/10)*sin(count)));
points[i,2]:=100+round(zoom*((paramval[1]/10)*count-(paramval[2]/10)*cos(count)));
putpoint(i);;
until count>abs(fin)+abs(beg)
end;
procedure trismac(beg,fin:real);
begin
if drawover=false then delant;
count:=beg;
i:=0;
repeat
inc(i);
count:=count+1;
points[i,1]:=150+round(zoom*(paramval[1]/10)*(4*cos(count)*cos(count)-1));
points[i,2]:=100+round(zoom*(paramval[1]/10)*(4*cos(count)*cos(count)-1)*sin(count)/cos(count));
putpoint(i);;
until count>abs(fin)+abs(beg)
end;
procedure lemniscata(beg,fin:real);
begin
if drawover=false then delant;
count:=beg;
i:=0;
repeat
inc(i);
count:=count+1;
points[i,1]:=150+round(zoom*(paramval[1]/10)*cos(count)*sqrt(2*abs(cos(2*count))));
points[i,2]:=100+round(zoom*(paramval[1]/10)*sin(count)*sqrt(2*abs(cos(2*count))));
putpoint(i);;
until count>abs(fin)+abs(beg)
end;
procedure trilong(beg,fin:real);
begin
if drawover=false then delant;
count:=beg;
i:=0;
repeat
inc(i);
count:=count+1;
points[i,1]:=150+round(zoom*(paramval[1]/10)/(4*cos(count)*cos(count)-3));
points[i,2]:=100+round(zoom*(paramval[1]/10)*(sin(count)/cos(count))/(4*cos(count)*cos(count)-3));
putpoint(i);;
until count>abs(fin)+abs(beg)
end;
procedure epicicl(beg,fin:real);
begin
if drawover=false then delant;
count:=beg;
i:=0;
repeat
inc(i);
count:=count+1;
points[i,1]:=150+round(zoom*(((paramval[1]/10)+(paramval[2]/10))*cos((paramval[2]/10)*count/(paramval[1]/10))-
             (paramval[2]/10)*cos(count+(paramval[2]/10)*count/(paramval[1]/10))));
points[i,2]:=100+round(zoom*(((paramval[1]/10)+(paramval[2]/10))*sin((paramval[2]/10)*count/(paramval[1]/10))-
             (paramval[2]/10)*sin(count+(paramval[2]/10)*count/(paramval[1]/10))));
putpoint(i);;
until count>abs(fin)+abs(beg)
end;
procedure hipocicl(beg,fin:real);
begin
if drawover=false then delant;
count:=beg;
i:=0;
repeat
inc(i);
count:=count+1;
points[i,1]:=150+round(zoom*(((paramval[1]/10)-(paramval[2]/10))*cos((paramval[2]/10)*count/(paramval[1]/10))+
             (paramval[2]/10)*cos(count+(paramval[2]/10)*count/(paramval[1]/10))));
points[i,2]:=100+round(zoom*(((paramval[1]/10)-(paramval[2]/10))*sin((paramval[2]/10)*count/(paramval[1]/10))-
             (paramval[2]/10)*sin(count+(paramval[2]/10)*count/(paramval[1]/10))));
putpoint(i);;
until count>abs(fin)+abs(beg)
end;
procedure concoida(beg,fin:real);
begin
if drawover=false then delant;
count:=beg;
i:=0;
repeat
inc(i);
count:=count+1;
points[i,1]:=150+round(zoom*((paramval[1]/10)-(paramval[2]/10)*cos(count)));
points[i,2]:=100+round(zoom*((paramval[1]/10)*(sin(count)/cos(count))-(paramval[2]/10))*sin(count));
putpoint(i);;
until count>abs(fin)+abs(beg)
end;
end.
