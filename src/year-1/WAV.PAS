program wav;
var f:file of byte;
    speak:array[1..15000] of byte;
    w,size,i:word;
    b:byte;
    sz:word;
procedure outspeak(var sursa);
begin
asm
mov dx,ds;
lds si,sursa;
mov cx,sz;
mov al,$b6;
out 67,al
mov bx,0;
@loop:
mov al,ds:[si+bx];
out 66,al
inc bx
mov al,ds:[si+bx];
out 66,al;
inc bx
in al,97;
or al,3
out 97,al;
push cx
mov cx,0
mov dx,3000
mov ah,$86
int $15;
pop cx
loop @loop;
in al,97;
and al,$fc;
out 97,al;
mov ds,dx;
end;
end;
procedure read_file;
begin
for i:=1 to size do
    begin
         read(f,b);
         speak[i]:=b;
    end;
end;
begin
assign(f,'kitty.wav');
reset(f);
size:=filesize(f);
sz:=size div 2;
read_file;
outspeak(speak);
end.