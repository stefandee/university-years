unit turtle;
interface
uses graph,crt;
const
    midox=320;
    midoy=200;
    ox:integer=320;
    oy:integer=200;
    ang:real=270;
procedure forward(i:integer);
procedure cls;
procedure left(i:real);
procedure right(i:real);
implementation
    procedure forward;
    begin
    moveto(ox,oy);
    ox:=ox+round(i*cos(pi*ang/180));
    oy:=oy+round(i*sin(pi*ang/180));
    linerel(round(i*cos(pi*ang/180)),round(i*sin(pi*ang/180)));
    end;
    procedure cls;
    begin
    cleardevice;
    ox:=midox;
    oy:=midoy;
    moveto(ox,oy);
    end;
    procedure left;
    begin
    ang:=ang-i;
    end;
    procedure right;
    begin
    ang:=ang+i;
    end;
end.

