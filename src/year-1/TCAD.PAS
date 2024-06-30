program cv;
uses graph,crt;
type omenu=string[10];
     popt= ^topt;
     topt=record
           name:string[10];
           cmd:word;
           help:word;
           next:popt;
     end;
     tcad= object
           first,last:popt;
           procedure init(x1,y1,x2,y2,xm,ym:integer);
           procedure run;
           function online(nohelp:word):string;
           function createmenu(name:omenu;cmd:word;help:word;next:popt):popt;
           procedure done;
     private
            x,y,ymenu,xmenu,xhw,yhw:integer;
            m1,m2:popt;
     end;

function tcad.createmenu(name:omenu;cmd:word;help:word;next:popt):popt;

begin
new(last);
last^.name:=name;
last^.cmd:=cmd;
last^.help:=help;
last^.next:=next;
createmenu:=last;
end;

procedure tcad.init(x1,y1,x2,y2,xm,ym:integer);
var gd,gm:integer;

begin
gd:=detect;
initgraph(gd,gm,'c:\language\tp7\bgi');
setfillstyle(1,red);
bar(x1,y1,x2,y2);
xmenu:=xm;
ymenu:=ym;
xhw:=100;
yhw:=200;
new(first);
last:=first;
last^.next:=nil;
last:=last^.next;
first:= createmenu('one',234,0,
        createmenu('two',235,1,
        createmenu('three',236,1,
        createmenu('four',237,0,
        createmenu('five',238,1,
        createmenu('six',239,0,nil))))));

end;

procedure tcad.run;
var i:integer;
    ch:char;
begin
m1:=first;
i:=ymenu;
while m1<>nil do
      begin
           outtextxy(xmenu,i,m1^.name);
           inc(i,15);
           m1:=m1^.next;
       end;
m1:=first;
i:=ymenu;
setfillstyle(1,cyan);
bar(xmenu,i,length(m1^.name)*8+xmenu,i+8);
outtextxy(xmenu,i,m1^.name);
repeat
if keypressed then ch:=readkey
              else ch:=#0;
if ch=#13 then begin
               setfillstyle(1,black);
               bar(xmenu,i,length(m1^.name)*8+xmenu,i+8);
               outtextxy(xmenu,i,m1^.name);
               m1:=m1^.next;
               inc(i,15);
               if m1=nil then begin
                              m1:=first;
                              i:=ymenu;
                              end;
               setfillstyle(1,cyan);
               bar(xmenu,i,length(m1^.name)*8+xmenu,i+8);
               outtextxy(xmenu,i,m1^.name);
               outtextxy(xhw,yhw,online(m1^.help));
               end;



until ch=#27;

end;

function tcad.online(nohelp:word):string;
begin
case nohelp of
235: begin
     online:='optiune';
     exit;
     end;
end;
end;

procedure tcad.done;

begin
m1:=first^.next;
dispose(first);
while m1^.next<>nil do
      begin
           m2:=m1^.next;
           dispose(m1);
           m1:=m2;
      end;
end;

var appcad:tcad;

BEGIN

appcad.init(60,40,640,480,0,50);
appcad.run;
appcad.done;

END.