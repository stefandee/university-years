program teste;
uses graph,crt;
const puncte:integer=0;
      test:array[1..3,1..36] of integer=
      ((1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
       (0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
       (0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0));
var gd,gm:integer;
    NR,LANGUAGE:INTEGER;
    TEST_NAME,txt:string;
    key:char;
    f:text;
    i:integer;
BEGIN
gd:=detect;
initgraph(gd,gm,'');
NR:=1;LANGUAGE:=2;TEST_NAME:='';
settextstyle(2,0,7);
outtextxy(100,100,'apasa :');
outtextxy(120,120,'1 ¯ test de ms_dos');
outtextxy(120,140,'2 ¯ test de turbo pascal');
repeat
key:=readkey;
case key of
'1':TEST_NAME:='MS_DOS';
'2':TEST_NAME:='TPASCAL';
END;
until (TEST_NAME='MS_DOS') or (TEST_NAME='TPASCAL');
assign(f,'a:\my_progr\'+TEST_NAME+'.DAT');
reset(f);
cleardevice;
setcolor(red);
settextstyle(1,0,6);
TEST_NAME:='TEST DE '+TEST_NAME;
outtextxy(100,0,TEST_NAME);
settextstyle(2,0,7);
for i:=1 to 50 do begin
setcolor(yellow);
settextstyle(2,0,6);
readln(f,txt);
outtextxy(100,100,txt);
readln(f,txt);
outtextxy(100,150,txt);
readln(f,txt);
outtextxy(100,200,txt);
readln(f,txt);
outtextxy(100,250,txt);
repeat
key:=readkey;
case key of
'1':puncte:=puncte+test[1,i];
'2':puncte:=puncte+test[2,i];
'3':puncte:=puncte+test[3,i];
end;
until (key='1') or (key='2') or (key='3');
delay(200);
cleardevice;
setcolor(red);
settextstyle(1,0,6);
outtextxy(100,0,TEST_NAME);
end;
restorecrtmode;
textcolor(yellow);
gotoxy(20,10);
write('ai obtinut ',puncte,' puncte, adica nota ',trunc(int(10*puncte/36)));
readln;
END.