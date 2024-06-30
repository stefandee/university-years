uses crt;
var f,t:string;
    vt:real;

function vl(s:string):real;
var cod:integer;
    f:real;
begin
     if s='t' then begin vl:=vt;exit; end;
     val(s,f,cod);
     vl:=f;
end;
function ifci(c:char):boolean;
begin
     if (c in ['0'..'9','t']) then ifci:=true
     else ifci:=false;
end;

function power(x:real; y:integer):real;
var i:integer;
    r:real;
begin
if y<0 then begin sound(400);delay(400);nosound;end;
r:=1;
if y=0 then begin power:=1;exit;end;
if y>0 then begin for i:=1 to abs(y) do r:=r*x;power:=r;exit;end;
if y<0 then begin
            for i:=1 to abs(y) do r:=r*x;
            r:=1/r;power:=r;
            end;
end;

function recfun(s:string):real;
var i:integer;
    sir,sinum:string;
    num:real;
begin
     sir:='';
     sinum:='';
     i:=1;
     while not(ifci(s[i])) do
     begin
          sir:=sir+s[i];
          inc(i);
     end;
     while i<=length(s) do
     begin
          sinum:=sinum+s[i];
          inc(i);
     end;
     num:=vl(sinum);
     if sir='' then recfun:=num;
     if sir='ln' then recfun:=ln(num);
     if sir='sin' then recfun:=sin(num);
     if sir='cos' then recfun:=cos(num);
     if sir='tg' then recfun:=sin(num)/cos(num);
     if sir='ctg' then recfun:=cos(num)/sin(num);
     if sir='arcsin' then recfun:=arctan (num/sqrt (1-sqr (num)));
     if sir='arccos' then recfun:=arctan (sqrt (1-sqr (num)) /num);
     if sir='arctg' then recfun:=arctan(num);
     if sir='arcctg' then recfun:=1/arctan(num);
end;

function calcul(s:string):real;
var i,j,k,cod:integer;
    op2:string[100];
    num:array[1..100] of real;
    nusi:string;
    lo:char;
    valo:real;

begin
     op2:='';
     nusi:='';
     lo:=' ';
     j:=1;
     k:=0;
     i:=1;
     while i<=length(s) do
     begin
          if (s[i]<>'*') and (s[i]<>'/')
          and (s[i]<>'+') and (s[i]<>'-')
          and (s[i]<>'^') then
             nusi:=nusi+s[i]
          else
          begin
          if (lo='+') or (lo='-') then
              begin
                 inc(j);
                 num[j]:=recfun(nusi);
                 nusi:='';
              end;
          case lo of
                   '*':begin
                       num[j]:=num[j]*recfun(nusi);
                       nusi:='';
                       end;
                   '/':begin
                       num[j]:=num[j]/recfun(nusi);
                       nusi:='';
                       end;
                   '^':begin
                       num[j]:=power(num[j],round(recfun(nusi)));
                       nusi:='';
                       end;
          end;
          if lo=' ' then
          begin
                   num[j]:=recfun(nusi);
                   nusi:='';
          end;
          lo:=s[i];
          if (lo='-') or (lo='+') then
          begin
                   inc(k);
                   op2[k]:=s[i];
          end;
          end;
          inc(i);
     end;
          case lo of
                   '*':begin
                       num[j]:=num[j]*recfun(nusi);
                       nusi:='';
                       end;
                   '/':begin
                       num[j]:=num[j]/recfun(nusi);
                       nusi:='';
                       end;
                   '^':begin
                       num[j]:=power(num[j],round(recfun(nusi)));
                       nusi:='';
                       end;

          end;
          if (lo='+') or (lo='-') then
              begin
                 inc(j);
                 num[j]:=recfun(nusi);
                 nusi:='';
              end;
          if lo=' ' then
          begin
                   num[j]:=recfun(nusi);
                   nusi:='';
          end;
     valo:=num[1];
     for i:=2 to j do
          case op2[i-1] of
               '+':valo:=valo+num[i];
               '-':valo:=valo-num[i];
          end;
     calcul:=valo;
end;

procedure paran(var s:string);
var par:array[1..100] of integer;
    i,k,lim:integer;
    sir,si:string;
begin
     sir:='';
     si:='';
     k:=0;
     lim:=length(s);
     i:=1;
     while(i<=lim) do
     begin
          if s[i]='(' then
          begin
               inc(k);
               par[k]:=i;
          end;
          if s[i]=')' then
          begin
               si:=copy(s,par[k]+1,i-par[k]-1);
               str(calcul(si):5:3,sir);
               delete(s,par[k],i-par[k]+1);
               insert(sir,s,par[k]);
               i:=par[k];
               dec(k);
               lim:=length(s);
          end;
     inc(i);
     end;
end;

begin
     clrscr;
     write('t=');readln(vt);
     repeat
     f:='';
     write('Functia : ');
     readln(f);
     f:='('+f+')';
     writeln(f);
     paran(f);
     writeln(f);
     until false;
end.
