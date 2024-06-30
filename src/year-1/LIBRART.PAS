unit struct;
interface
uses graph,crt;
const esc=#27;
      quit=1;

type optname=string[10];
     psubmenu=^submenu;
     submenu=record
      name:optname;
      cmd:word;
      next:psubmenu;
     end;

    pmenu=^menu;
    menu=record
     name:optname;
     sbmenu:psubmenu;
     x,y:integer;
     next:pmenu;
    end;

    menus=object
     constructor init;
     procedure initmenu;virtual;
     procedure command(cmd:word);virtual;
     procedure walk;
     {procedure defbasickeys;virtual;}
     destructor done;
    end;

var tm1,fmenu:pmenu;
    m1:psubmenu;

function newmenu(name:optname;x,y:integer;sbmenu:psubmenu;next:pmenu):pmenu;
function newsubmenu(name:optname;cmd:word;next:psubmenu):psubmenu;

implementation

function newmenu(name:optname;x,y:integer;sbmenu:psubmenu;next:pmenu):pmenu;


begin

new(tm1);
tm1^.name:=name;
tm1^.x:=x;
tm1^.y:=y;
new(tm1^.sbmenu);
m1:=tm1^.sbmenu;
m1^.next:=nil;
m1:=m1^.next;
tm1^.sbmenu:=sbmenu;
tm1^.next:=next;
newmenu:=tm1;

end;

function newsubmenu(name:optname;cmd:word;next:psubmenu):psubmenu;

begin

new(m1);
m1^.name:=name;
m1^.cmd:=cmd;
m1^.next:=next;
newsubmenu:=m1;

end;

constructor menus.init;

var gd,gm:integer;

begin

gd:=detect;
initgraph(gd,gm,'');
new(fmenu);
tm1:=fmenu;
tm1^.next:=nil;
tm1:=tm1^.next;

end;

procedure menus.initmenu;

begin
fmenu:=newmenu('help',10,10,newsubmenu('help1',1,nil),nil);
end;

procedure menus.command(cmd:word);

begin
end;

procedure menus.walk;

var ch:char;
    yopt:integer;
begin

tm1:=fmenu;
setcolor(white);
while tm1<>nil do
begin
outtextxy(tm1^.x,tm1^.y,tm1^.name);
tm1:=tm1^.next;
end;
tm1:=fmenu;
setfillstyle(1,cyan);
bar(tm1^.x,tm1^.y,tm1^.x+length(tm1^.name)*10,tm1^.y+10);
outtextxy(tm1^.x,tm1^.y,tm1^.name);
repeat
if keypressed then ch:=readkey
              else ch:=#0;
if ch=#77 then begin
               setfillstyle(1,black);
               bar(tm1^.x,tm1^.y,tm1^.x+length(tm1^.name)*10,tm1^.y+10);
               outtextxy(tm1^.x,tm1^.y,tm1^.name);
               tm1:=tm1^.next;
               if tm1=nil then tm1:=fmenu;
               setfillstyle(1,cyan);
               bar(tm1^.x,tm1^.y,tm1^.x+length(tm1^.name)*10,tm1^.y+10);
               outtextxy(tm1^.x,tm1^.y,tm1^.name);
               end;
if ch=#13 then begin
               yopt:=tm1^.y+10;
               m1:=tm1^.sbmenu;
               while m1<>nil do
                     begin
                          setcolor(white);
                          outtextxy(tm1^.x,yopt,m1^.name);
                          inc(yopt,12);
                          m1:=m1^.next;
                     end;
              m1:=tm1^.sbmenu;
              yopt:=tm1^.y+10;
              setfillstyle(1,cyan);
              bar(tm1^.x,yopt,tm1^.x+length(m1^.name)*8,yopt+10);
              outtextxy(tm1^.x,yopt,m1^.name);
              repeat
              if keypressed then ch:=readkey
                            else ch:=#0;
              if ch=#80 then begin
                             setfillstyle(1,black);
                             bar(tm1^.x,yopt,tm1^.x+length(m1^.name)*8,yopt+10);
                             setcolor(white);
                             outtextxy(tm1^.x,yopt,m1^.name);
                             m1:=m1^.next;
                             inc(yopt,12);
                             if m1=nil then begin
                                            m1:=tm1^.sbmenu;
                                            yopt:=tm1^.y+10;
                                            end;
                             setfillstyle(1,cyan);
                             bar(tm1^.x,yopt,tm1^.x+length(m1^.name)*8,yopt+10);
                             setcolor(white);
                             outtextxy(tm1^.x,yopt,m1^.name);
                             end;
              if ch=#13 then command(m1^.cmd);
             until ch=#27;
             ch:=#0;
             setfillstyle(1,black);
             bar(tm1^.x,yopt,tm1^.x+length(m1^.name)*8,yopt+10);
             outtextxy(tm1^.x,yopt,m1^.name);
             setcolor(black);
             yopt:=tm1^.y+10;
             m1:=tm1^.sbmenu;
             while m1<>nil do
                     begin
                          outtextxy(tm1^.x,yopt,m1^.name);
                          inc(yopt,12);
                          m1:=m1^.next;
                     end;
            setcolor(white);
             end;
until ch=#27;

end;

destructor menus.done;

var tm2:pmenu;
    m2:psubmenu;
begin

tm1:=fmenu^.next;
m1:=fmenu^.sbmenu^.next;
dispose(fmenu^.sbmenu);
while m1<>nil do
      begin
           m2:=m1^.next;
           dispose(m1);
           m1:=m2;
      end;
dispose(fmenu);
while tm1<>nil do
      begin
           tm2:=tm1^.next;
           m1:=tm1^.sbmenu^.next;
           dispose(tm1^.sbmenu);
           while m1<>nil do
                 begin
                      m2:=m1^.next;
                      dispose(m1);
                      m1:=m2;
                 end;
           dispose(tm1);
           tm1:=tm2;
      end;
end;
end.