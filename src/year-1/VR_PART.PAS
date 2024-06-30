program vr;
{$n+}
uses graph,crt;
Const l=100;
      z0=300;
      rad=pi/180;
      nrpart=12;
      eps=100;
      tau=0.01;

Type vect = array[1..nrpart] of real;
     part = record
            fx,fy,fz:comp;
            x,y,z   :comp;
            vx,vy,vz:comp;
            m,q     :comp;
         end;
Var q,w       : vect;
    a,b,c     : real;
    j,i,v     : integer;
    key       : char;
    gd,gm     : integer;
    pg      :integer;
    zoomf     :real;
    zf        :string;
    p         :array [1..nrpart] of part;
    page      :integer;

function Power(x,y:integer):real;

var i:integer;
    t,p:real;


begin
p:=1;
if y<0 then begin
            t:=1/x;
            for i:=1 to abs(y) do p:=p*t;
            power:=p;
            end
       else begin
            t:=x;
            for i:=1 to abs(y) do p:=p*t;
            power:=p;
            end
end;
procedure Points(color:integer);

var i:integer;

begin
setactivepage(page);
cleardevice;
for i:=1 to nrpart do putpixel(round(p[i].x),round(p[i].y),color);
setvisualpage(page);
inc(page);
if page>1 then page:=0;

end;

BEGIN
gd:=vga;
gm:=vgamed;
initgraph(gd,gm,'c:\bin\tp7\bgi');
randomize;
for i:=4 to nrpart do
    with p[i] do
         begin
              fx:=random(3);fy:=random(3);fz:=random(4);
              x:=320+random(15);
              y:=150+random(15);
              z:=random(5);
              vx:=random(4)+1;vy:=random(4)+1;vz:=random(4)+1;
              q:=-1;
              m:=random(8)+1;
         end;
randomize;
for i:=1 to 3 do
    with p[i] do
         begin
              fx:=random(5);fy:=random(3);fz:=random(3);
              x:=320+random(15);
              y:=150+random(15);
              z:=random(5);
              vx:=random(4)+1;vy:=random(4)+1;vz:=random(4)+1;
              q:=1;
              m:=random(6)+1;
         end;
zoomf:=1;
page:=0;
repeat
      for i:=1 to nrpart do
          begin
          for j:=1 to nrpart do
              begin
                   if p[i].x<>p[j].x then begin
                                          p[i].fx:=p[i].q*p[j].q*eps/((p[i].x-p[j].x)*(p[i].x-p[j].x))+p[i].fx;
                                          p[j].fx:=p[i].q*p[j].q*eps/((p[i].x-p[j].x)*(p[i].x-p[j].x))+p[j].fx;
                                          end;
                   if p[i].y<>p[j].y then begin
                                          p[i].fy:=p[i].q*p[j].q*eps/sqr(p[i].y-p[j].y)+p[i].fy;
                                          p[j].fy:=p[i].q*p[j].q*eps/sqr(p[i].y-p[j].y)+p[j].fy;
                                          end;
                   if p[i].z<>p[j].z then begin
                                          p[i].fz:=p[i].q*p[j].q*eps/sqr(p[i].z-p[j].z)+p[i].fz;
                                          p[j].fz:=p[i].q*p[j].q*eps/sqr(p[i].z-p[j].z)+p[j].fz;
                                          end;


              end;
          p[i].vx:=tau*p[i].fx/p[i].m+p[i].vx;
          p[i].vy:=tau*p[i].fy/p[i].m+p[i].vy;
          p[i].vz:=tau*p[i].fz/p[i].m+p[i].vz;
          p[i].x:=tau*p[i].vx+p[i].x;
          p[i].y:=tau*p[i].vy+p[i].y;
          p[i].z:=tau*p[i].vz+p[i].z;
          points(15);
          end;

if keypressed then key:=readkey
              else key:=#0;

until key=#13;

END.