%{
#include "gramatica.tab.h"
int linie=1;
%}

%option noyywrap

LITERA		[A-Za-z_]
CIFRA		[0-9A-Fa-f]
CIFRA_ZEC	[0-9]
IDENTIFICATOR	{LITERA}({LITERA}|{CIFRA_ZEC})*
NR_BAZA10	{CIFRA_ZEC}+
EXPON		(E|e)(\+|-)?{CIFRA_ZEC}{1,2}
NR_REAL		{NR_BAZA10}"."{NR_BAZA10}{EXPON}?
DELIMIT_1	[;.,:]
OPERATOR_1	[+*/()<>=]|"-"|"["|"]"
COMENT		"{"[^}]*"}"
SIR_CAR		\"[^\n"]*\"
CARACTER	'[^\n]'
BAZA		{CIFRA_ZEC}{1,2}
CONST_NUM	{NR_INTREG}|{NR_REAL}
NR_INTREG	{BAZA}#{CIFRA}{CIFRA}*

%%

[ \t]
[\n]	{printf("linia: %d\n", linie++);}
{COMENT}

begin		{return BEGINN;}
case		{return CASE;}
const		{return CONST;}
do		{return DO;}
downto		{return DOWNTO;}
else		{return ELSE;}
end		{return END;}
for		{return FOR;}
function	{return FUNCTION;}
if		{return IF;}
of		{return OF;}
procedure	{return PROCEDURE;}
print		{return PRINT;}
program		{return PROGRAM;}
read		{return READ;}
repeat		{return REPEAT;}
then		{return THEN;}
until		{return UNTIL;}
var		{return VAR;}
while		{return WHILE;}
array		{return ARRAY;}
record		{return RECORD;}
to		{return TO;}
step		{return STEP;}
otherwise	{return OTHERWISE;}

char		{return CHAR;}
integer		{return INTEGER;}
real		{return REAL;}

":="		{return ATRIB;}
"<>"		{return NE;}
"<="		{return LE;}
">="		{return GE;}
".."		{return DOTDOT;}
div		{return DIV;}
mod		{return MOD;}
or		{return OR;}
and		{return AND;}
not		{return NOT;}

{IDENTIFICATOR}	{return ID;}
{NR_BAZA10}	{
	yylval.p_val = yytext;
	return CONST_INT;
		}
  /* verificare cifre baza */
{NR_INTREG}	{
	yylval.p_val = yytext;
	return CONST_INT;
		}
{NR_REAL}	{
	yylval.p_val = yytext;
	return CONST_REAL;
		}
{CARACTER}	{
	yylval.p_val = yytext;
	return CONST_CAR;
		}
{SIR_CAR}	{return CONST_SIR;}

{DELIMIT_1}	{return yytext[0];}
{OPERATOR_1}	{return yytext[0];}

%%




