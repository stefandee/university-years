program rot;

uses graph,crt;
Const l=100;
      z0=300;
      p=pi/180;
      nrpoint=10;

Type vect = array[1..nrpoint] of real;
Var x,y,z,q,w : vect;
    a,b,c     : real;
    j,i,v     : integer;
    cm        : char;
    sir       : string;
    ii,contor,gd,gm : integer;
    go:boolean;
    key:char;

Procedure InitCub;
var d : real;
begin
  d:=l/2;
  x[1]:=30;  y[1]:=30;  z[1]:=30;
  x[2]:=110; y[2]:=30;  z[2]:=30;
  x[3]:=110; y[3]:=30;  z[3]:=60;
  x[4]:=30;  y[4]:=30;  z[4]:=60;
  x[5]:=30;  y[5]:=45; z[5]:=60;
  x[6]:=30;  y[6]:=45; z[6]:=30;
  x[7]:=50;  y[7]:=30; z[7]:=30;
  x[8]:=30;  y[8]:=30; z[8]:=15;
  x[9]:=50;  y[9]:=30; z[9]:=60;
  x[10]:=30;  y[10]:=30; z[10]:=75;

end;



Procedure Rotate3D(a,b,c : real);
var sa,sb,sc   : real;
    ca,cb,cc,u : real;
    i          : integer;
begin
  a:=a*p; b:=b*p; c:=c*p;
  ca:=cos(a); sa:=sin(a);
  cb:=cos(b); sb:=sin(b);
  cc:=cos(c); sc:=sin(c);
  for i:=1 to nrpoint do
  begin
    if a<>0 then
    begin
      u:=y[i];
      y[i]:=u*ca+z[i]*sa;
      z[i]:=z[i]*ca-u*sa;
    end;
    if b<>0 then
    begin
      u:=z[i];
      z[i]:=u*cb+x[i]*sb;
      x[i]:=x[i]*cb-u*sb;
    end;
    if c<>0 then
    begin
      u:=x[i];
      x[i]:=u*cc+y[i]*sc;
      y[i]:=y[i]*cc-u*sc;
    end;
  end;
end;

Procedure Proiectie;

var fpr : real;
    i   : integer;
begin
  for i:=1 to nrpoint do
  begin
    fpr:=z0/(z0-z[i]);
    q[i]:=fpr*x[i]*GetMaxY/(2*z0*sin(10)/cos(10))+150;
    w[i]:=fpr*y[i]*GetMaxY/(2*z0*sin(10)/cos(10))+220;
  end;
end;


Procedure Desenare(cul: word);
begin
  SetColor(cul);               {baza 1}
  Line(round(q[1]),round(w[1]),round(q[8]),round(w[8]));
  Line(round(q[8]),round(w[8]),round(q[7]),round(w[7]));
  Line(round(q[1]),round(w[1]),round(q[7]),round(w[7]));
  Line(round(q[1]),round(w[1]),round(q[4]),round(w[4]));
  Line(round(q[1]),round(w[1]),round(q[6]),round(w[6]));
  Line(round(q[2]),round(w[2]),round(q[7]),round(w[7]));
  Line(round(q[2]),round(w[2]),round(q[3]),round(w[3]));
  Line(round(q[3]),round(w[3]),round(q[4]),round(w[4]));
  Line(round(q[4]),round(w[4]),round(q[5]),round(w[5]));
  Line(round(q[5]),round(w[5]),round(q[6]),round(w[6]));
  Line(round(q[4]),round(w[4]),round(q[10]),round(w[10]));
  Line(round(q[4]),round(w[4]),round(q[9]),round(w[9]));
  Line(round(q[9]),round(w[9]),round(q[10]),round(w[10]));
  Line(round(q[2]),round(w[2]),round(q[6]),round(w[6]));
  Line(round(q[3]),round(w[3]),round(q[5]),round(w[5]));
end;

procedure DETACH(step:byte);

begin

for i:=1 to nrpoint do
z[i]:=z[i]-step;

end;

procedure APPROACH(step:byte);

begin

for i:=1 to nrpoint do
z[i]:=z[i]+step;

end;

begin

gd:=detect;
initgraph(gd,gm,'c:\language\tp7\bgi');
initcub;
repeat

if keypressed then begin
                   key:=readkey;
                   if key='d' then go:=true;
                   if key='a' then go:=false;
                   if key='o' then rotate3d(0,pi/4,0);
                   if key='p' then rotate3d(0,-pi/4,0);
                   if key='q' then rotate3d(pi/4,0,0);
                   if key='z' then rotate3d(pi/4,0,0);
                   end;
if go=true then detach(1)
           else approach(1);
proiectie;
desenare(15);
delay(10);
proiectie;
desenare(0);

until key=#13;

end.