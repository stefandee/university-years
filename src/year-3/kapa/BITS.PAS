program
       test_bits_operations;
uses
    utils,crt;
var
   b : byte;
begin
 clrscr;
 b := 0;
 setbit(b,0,1);
 setbit(b,15,1);
 writeln(b,' ',GetBit(b,0),' ',GetBit(b,15));
 setbit(b,0,0);
 writeln(b,' ',GetBit(b,0),' ',GetBit(b,15));
end.
