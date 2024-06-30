program tcad;

uses struct,graph,crt;

type api=object(menus)
     procedure initmenu;virtual;
     procedure command(cmd:word);virtual;
     end;

     cr=record
     titlu:string[30];
     domeniu:string[30];
     pret:integer;
     impr:boolean;
     case tip:char of
     'c':(autor:string[30];pag:integer);
     'r':(an,luna:integer);
     end;

var apl:api;
    f:file of cr;
    ob:cr;
procedure api.initmenu;

begin
fmenu:=newmenu('functii',10,10,newsubmenu('introduce',100,
                              newsubmenu('domeniu',101,
                              newsubmenu('nume',102,
                              newsubmenu('imprumut',103,nil)))),
       newmenu('fisier',100,10,newsubmenu('iesire',quit,
                               newsubmenu('salvare',105,nil)),nil));

end;

procedure api.command(cmd:word);

var cod:integer;
    st:string;

procedure box(x,y,xf,yf,c:integer);
begin
setfillstyle(1,c);
bar(x,y,xf,yf);
end;

function data(x,y:integer;tip:byte;st:string):string;{0-sir,1-numar}

var s:string;
    ch:char;

begin
s:='';
setcolor(0);
outtextxy(x,y,st);
x:=x+length(st)*9;
repeat

if keypressed then ch:=readkey
              else ch:=#0;
if tip=0 then if (ch>='A') and (ch<='z') then begin
                                                        inc(x,8);
                                                        outtextxy(x,y,ch);
                                                        s:=s+ch;
                                                        end;
if tip=1 then if (ch>='0') and (ch<='9') then begin
                                                        inc(x,8);
                                                        outtextxy(x,y,ch);
                                                        s:=s+ch;
                                                        end;

until ch=#13;
data:=s;
end;
begin
case cmd of
1  :   halt;
100:   begin
       box(100,100,400,350,7);
       ob.titlu:=data(105,105,0,'titlu:');
       ob.domeniu:=data(105,115,0,'domeniu:');
       val(data(105,125,1,'pret:'),ob.pret,cod);
       repeat
       box(105,135,400,145,7);
       st:=data(105,135,0,'imprumutata?');
       until (st='y') or (st='n');
       if st='y' then ob.impr:=true
                 else ob.impr:=false;
       box(100,100,400,350,0);
       end;
end;
end;


begin
assign(f,'library.lib');
rewrite(f);
apl.init;
apl.initmenu;
apl.walk;
apl.done;
close(f);
end.