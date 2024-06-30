program songs;
{$F+,S-}
uses dos,crt;

const timerctrl=67;
      timerdata=66;
      sysctrl=97;
      intctrl=$20;
      kbdata=$60;
      kbctrl=$61;
      c:byte=0;
      p:byte=0;

var oldc:byte;
    vectoff:integer absolute $0:$24;
    vectseg:integer absolute $0:$26;
    oldvectoff,oldvectseg,octave:integer;
    regs1,regs2:registers;
    ch:char;
    int9orig:pointer;


procedure getch;interrupt;
begin
     {inline($50/$51/$52/$53/$56/$57/$1e/$06);}
     c:=port[kbdata];
     p:=port[kbctrl];
     port[kbctrl]:=p or $80;
     port[kbctrl]:=p and $7f;
     port[kbctrl]:=$20;
     {inline($07/$1f/$5f/$5e/$5b/$5a/$59/$58/$8b/$e5/$5d/$cf);}
end;

procedure play;

const note:array[0..11] of integer=( 4554,4292,4058,3824,3616,3409,3225,3044,
                                     2868,2712,2560,2415);
var i:integer;

begin
while true do
      begin
            repeat until c<>oldc;
           case c of
           65:i:=0;
           66:i:=1;
           67:i:=2;
           68:i:=3;
           69:i:=4;
           70:i:=5;
           71:i:=6;
           72:i:=7;
           73:i:=8;
           74:i:=9;
           75:i:=10;
           76:i:=11;
           27:exit;
           146..165:port[sysctrl]:=port[sysctrl] and $fc;
           end;{case}
           oldc:=c;
           if c in [65..76] then begin
                                 port[timerctrl]:=$b6;
                                 port[timerdata]:=lo(note[i]);
                                 port[timerdata]:=hi(note[i]);
                                 port[sysctrl]:=port[sysctrl] or 3;
                                 end;
      end;{while}
end;{play}

begin{pp}
getintvec($09,int9orig);
setintvec($09,addr(getch));
{oldc:=c;}
{oldvectoff:=vectoff;
oldvectseg:=vectseg;
inline($fa);
vectoff:=ofs(getch);
vectseg:=cseg;
inline($fb);}

octave:=1;
port[sysctrl]:=port[sysctrl] and $fc;
play;
port[sysctrl]:=port[sysctrl] and $fc;
setintvec($09,int9orig);

{inline($fa);
vectoff:=oldvectoff;
vectseg:=oldvectseg;
inline($fb);}

end.


