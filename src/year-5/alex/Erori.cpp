#include <stdio.h>
#include <stdlib.h>
#pragma hdrstop

#include "erori.h"

#define MAX_ERORI 79

char* Erori[MAX_ERORI] =
{
  "Success",
  "Eroare #1 : nu pot deschide fisierul de atomi .lex",
  "Eroare #2 : nu pot citi din fisierul .lex",
  "Eroare #3 : program expected",
  "Eroare #4 : identifier expected",
  "Eroare #5 : .lex file has invalid format",
  "Eroare #6 : ; expected",
  "Eroare #7 : . expected",
  "Eroare #8 : const, var, function, procedure or begin..end expected",
  "Eroare #9 : = expected",
  "Eroare #10 : begin expected",
  "Eroare #11 : ; or end expected",
  "Eroare #12 : , expected",
  "Eroare #13 : : expected",
  "Eroare #14 : array, record or one of real, char, integer expected",
  "Eroare #15 : [ expected",
  "Eroare #16 : ] expected",
  "Eroare #17 : integer number expected",
  "Eroare #18 : .. expected",
  "Eroare #19 : of expected",
  "Eroare #20 : integer, char or real expected",
  "Eroare #21 : ( expected",
  "Eroare #22 : ) expected",
  "Eroare #23 : Error in expression",
  "Eroare #24 : var expected",
  "Eroare #25 : Instruction expected",
  "Eroare #26 : Variable expected, sth else found",
  "Eroare #27 : Function is not welcomed here (Lvalue required)",
  "Eroare #28 : Relational operator expected here",
  "Eroare #29 : Then expected",
  "Eroare #30 : := expected",
  "Eroare #31 : to/downto expected",
  "Eroare #32 : do expected",
  "Eroare #33 : Syntax error...can't understand this",
  "Eroare #34 : of expected",
  "Eroare #35 : end expected",
  "Eroare #36 : otherwise expected",
  "Eroare #37 : Ordinal expression expected",
  "Eroare #38 : At least ONE ordinal expected",
  "TS#39 : Identifier not declared",
  "TS#40 : Multiple declaration for identifier",
  "TS#41 : Not enough room to store constants :-)",
  "TS#42 : Incompatible types in operation",
  "TS#43 : Divide by 0",
  "TS#44 : Identifier not defined",
  "TS#45 : Identifier is not a constant",
  "TS#46 : Array min index is greater than max index",
  "Eroare#47 : cowardly refuse to process an empty record :-)",
  "TS#48 : Not a member of record",
  "TS#49 : Procedure not declared",
  "Eroare #50 : Procedure call is not welcomed here ",
  "TS#51 : A function can be assigned a value only inside its code",
  "TS#52 : L-Value expected",
  "TS#53 : Program name cannot be assigned a value",
  "TS#54 : This is not an array",
  "TS#55 : Integer index expected for array",
  "TS#56 : This is not a record variable but it is used like one",
  "MV#57 : Opening object file failed",
  "MV#58 : Index overflow",
  "MV#59 : Reading object file failed",
  "MV#60 : Invalid object file",
  "MV#61 : Cannot load constant table from object file",
  "MV#62 : Cannot load the code",
  "MV#63 : Unknown instruction",
  "TS#64 : Need an integer in for index",
  "TS#65 : Integer expression/type expected",
  "TS#66 : Invalid parameter type in function call",
  "TS#67 : Too many parameters in function call",
  "TS#68 : Too few parameters in function call",
  "TS#69 : Cannot compare char with integer or real",
  "TS#70 : Array index underflow",
  "TS#71 : Array index overflow",
  "TS#72 : This cannot be evaluated",
  "TS#73 : Array must be indexed with [",
  "TS#74 : Assigning a function is possible only inside its scope",
  "TS#75 : Cannot read in a function name",
  "TS#76 : Cannot for with a function name as index",
  "Eroare#77 : Until expected",
  "Eroare#78 : For counter variable must be simple in this version"
};

void Eroare(int what)
{
  if (what < MAX_ERORI) printf("%s\n", Erori[what]);
  else printf("Cod de eroare nekunoskut %d\n", what);
}