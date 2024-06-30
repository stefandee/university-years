program objph;
uses app,objects,menus,dialogs,views,drivers,editors;
const cmfopen=201;
      cmfsave=202;
      cmfadd=203;
      cmfmodify=204;
type tprg=object(Tapplication)
     procedure initmenubar;virtual;
     procedure initstatusline;virtual;
     procedure handleevent(var event:tevent);virtual;
     end;
procedure tprg.initmenubar;
var r:Trect;
begin
getextent(r);
r.b.y:=1;
menubar:=new(Pmenubar,init(r,newmenu(
newsubmenu('~F~ile',0,newmenu(
newitem('~O~pen','F3',kbf3,cmfopen,0,
newitem('~S~ave','F2',kbf2,cmfsave,0,nil))),
newsubmenu('~E~dit',0,newmenu(
newitem('~A~dd','',0,cmfadd,0,
newitem('~M~odify','',0,cmfmodify,0,nil))),nil)))));
end;
procedure tprg.initstatusline;
var r:trect;
begin
getextent(r);
r.a.y:=r.b.y-1;
statusline:=new(pstatusline,init(r,
newstatusdef(0,$ffff,
newstatuskey('~ESC~ to exit',kbesc,cmquit,
newstatuskey('~F10~ to menu',kbf10,cmmenu,nil)),nil)));
end;
procedure modify;
var edit:peditor;
    r:trect;
    ah,av:pscrollbar;
    ind:pindicator;
begin
r.assign(10,10,20,20);
new(edit,init(r,ah,av,ind,5000));
end;
procedure tprg.handleevent(var event:tevent);
begin
tapplication.handleevent(event);
if event.what=evcommand then begin
                             case event.command of
                             cmfmodify:modify;
                             end;
                             end
                        else exit;
end;
var  pprg:tprg;

begin
pprg.init;
pprg.run;
pprg.done;
end.