program drumul_nebunului;

uses graph,crt;

const n=10;

type table=array[1..n,1..n] of byte;
     way=array[1..n*n,1..2] of byte;

var i,j,gd,gm,err:integer;
    tab:table;
    st1,st2:string;
    b1,b2,ppx,ppy,psx,psy:byte;

procedure algoritm;

var valc,cx,cy:integer;
    modify:boolean;

label found;

begin

tab[ppx,ppy]:=1;valc:=1;

repeat
modify:=false;
for i:=1 to n do
    for j:=1 to n do
        if tab[i,j]=valc then begin
                              modify:=true;
                              if (i>1) and (j>1) then if tab[i-1,j-1]=0 then tab[i-1,j-1]:=valc+1;
                              if (i<10) and (j<10) then if tab[i+1,j+1]=0 then tab[i+1,j+1]:=valc+1;
                              if (i<10) and (j>1) then if tab[i+1,j-1]=0 then tab[i+1,j-1]:=valc+1;
                              if (i>1) and (j<10) then if tab[i-1,j+1]=0 then tab[i-1,j+1]:=valc+1;
                              end;
if not modify then begin
                   outtextxy(0,180,'nu exista drum !!!');
                   repeat
                   until readkey=#13;
                   halt;
                   end;

inc(valc);
until tab[psx,psy]<>0;

{for i:=1 to n do
    for j:=1 to n do
        begin
             str(tab[i,j],st1);
             outtextxy(150+j*20,150+i*20,st1);
        end;}

valc:=tab[psx,psy]-1;cx:=psx;cy:=psy;
setfillstyle(1,lightred);
bar((psx-1)*10,(psy-1)*10,psx*10,psy*10);
setfillstyle(1,red);

repeat
if (cx>1) and (cy>1) then if tab[cx-1,cy-1]=valc then begin
                                                    dec(cx);
                                                    dec(cy);
                                                    bar((cx-1)*10,(cy-1)*10,cx*10,cy*10);
                                                    dec(valc);
                                                    {goto found};
                                                    end;
if (cx<10) and (cy<10) then if tab[cx+1,cy+1]=valc then begin
                                                      inc(cx);
                                                      inc(cy);
                                                      dec(valc);
                                                      bar((cx-1)*10,(cy-1)*10,cx*10,cy*10);
                                                      {goto found};
                                                      end;
if (cx<10) and (cy>1) then if tab[cx+1,cy-1]=valc then begin
                                                     inc(cx);
                                                     dec(cy);
                                                     bar((cx-1)*10,(cy-1)*10,cx*10,cy*10);
                                                     dec(valc);
                                                     {goto found};
                                                     end;
if (cx>1) and (cy<10) then if tab[cx-1,cy+1]=valc then begin
                                                     dec(cx);
                                                     inc(cy);
                                                     dec(valc);
                                                     bar((cx-1)*10,(cy-1)*10,cx*10,cy*10);
                                                     {goto found};
                                                     end;
found:until valc=1;
setfillstyle(1,lightred);
bar((ppx-1)*10,(ppy-1)*10,ppx*10,ppy*10);

end;

function data(x,y:integer;tip:byte):string;{0-sir,1-numar}

var s:string;
    ch:char;

begin
s:='';
setcolor(white);
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
gd:=detect;
initgraph(gd,gm,'c:\bin\tp7\bgi');
for i:=1 to n do for j:=1 to n do tab[i,j]:=0;
setcolor(white);
for i:=0 to n do line(i*10,0,i*10,n*10);
for i:=0 to n do line(0,i*10,n*10,i*10);
outtextxy(0,180,'obstacolele ?');
i:=200;
repeat
st1:=data(0,i,1);
st2:=data(50,i,1);
val(st1,b1,err);
val(st2,b2,err);
if (b1<11) and (b1>0) and (b2<11) and (b1>0) then begin
                                                  tab[b1,b2]:=255;
                                                  setfillstyle(1,white);
                                                  bar((b1-1)*10,(b2-1)*10,b1*10,b2*10);
                                                  end;
inc(i,10);
if i>250 then begin
              i:=200;
              setfillstyle(1,black);
              bar(0,200,110,260);
              end;

until (b1=255) and (b2=255);

setfillstyle(1,black);
bar(0,180,110,260);
outtextxy(0,180,'plecare ?');

repeat     {punct plecare}
st1:=data(0,190,1);
st2:=data(50,190,1);
val(st1,b1,err);
val(st2,b2,err);
setfillstyle(1,black);
bar(0,190,110,260);
until (b1<11) and (b2<11) and (tab[b1,b2]<>254);

ppx:=b1;
ppy:=b2;
setfillstyle(1,black);
bar(0,180,110,260);

outtextxy(0,180,'sosire ?');

repeat     {punct sosire}
st1:=data(0,190,1);
st2:=data(50,190,1);
val(st1,b1,err);
val(st2,b2,err);
setfillstyle(1,black);
bar(0,190,110,260);
until (b1<11) and (b2<11) and (tab[b1,b2]<>255);
psx:=b1;
psy:=b2;
setfillstyle(1,black);
bar(0,180,110,260);

algoritm;
repeat
until readkey=#13;

end.