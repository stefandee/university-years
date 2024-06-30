#crap chars
echo TESTING INTEGER CAPABILITIES
echo ----------------------------
int:
=10
*7
-60
/10
printon
nameof
echo TESTING STRING CAPABILITIES
echo ---------------------------
str:
nameof
=laboratorul
+ 5 de
+ IP
<=abo
printon
echo TESTING COLLECTION CAPABILITIES
echo -------------------------------
col:
nameof
add 1
add 5
add 10
add 4
add aabb
printon
detach 4
printon
detach aabb
printon
echo TESTING QUEUE MEMBERS
echo -------------------
queue:
nameof
put 1
put 2
put 3
put 5
printon
get
printon
head
echo TESTING STACK MEMBERS
echo ---------------------
stack:
nameof
pushx 1
push 3
push 7
printon
pop
printon
top
#end of script