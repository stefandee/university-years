program squadron;

uses squadvar,graph,crt;

var ch:char;
    is:boolean;

begin

initsoldiers;
initscreen;
testfield;

repeat

if keypressed then ch:=readkey
              else ch:=#0;
case upcase(ch) of
#72 : begin
      if gridtest=on then setcolor(gridc)
                     else setcolor(ground[cx,cy].color);
      rectangle((cx-1)*pasx,pasy*(cy-1),pasx*cx,pasy*cy);
      dec(cy);
      if cy<1 then cy:=m;
      setcolor(cursc);
      rectangle((cx-1)*pasx,pasy*(cy-1),pasx*cx,pasy*cy);
      testfield;
      end;
#80 : begin
      if gridtest=on then setcolor(gridc)
                     else setcolor(ground[cx,cy].color);
      rectangle((cx-1)*pasx,pasy*(cy-1),pasx*cx,pasy*cy);
      inc(cy);
      if cy>m then cy:=1;
      setcolor(cursc);
      rectangle((cx-1)*pasx,pasy*(cy-1),pasx*cx,pasy*cy);
      testfield;
      end;
#75 : begin
      if gridtest=on then setcolor(gridc)
                     else setcolor(ground[cx,cy].color);
      rectangle((cx-1)*pasx,pasy*(cy-1),pasx*cx,pasy*cy);
      dec(cx);
      if cx<1 then cx:=n;
      setcolor(cursc);
      rectangle((cx-1)*pasx,pasy*(cy-1),pasx*cx,pasy*cy);
      testfield;
      end;
#77 : begin
      if gridtest=on then setcolor(gridc)
                     else setcolor(ground[cx,cy].color);
      rectangle((cx-1)*pasx,pasy*(cy-1),pasx*cx,pasy*cy);
      inc(cx);
      if cx>n then cx:=1;
      setcolor(cursc);
      rectangle((cx-1)*pasx,pasy*(cy-1),pasx*cx,pasy*cy);
      testfield;
      end;
#32 : begin
      testfield;
      if ret_name<>'' then do_it(300,400,red,yellow);
      end;
end;
until ch=#27;

end.