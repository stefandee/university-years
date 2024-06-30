%{
#include "gramatica.tab.h"
int line;
%}
%option noyywrap
LITERA [A-Z]|[a-z]
CIFRA_ZEC [0-9]
CIFRA {CIFRA_ZEC}|[A-F]|[a-f]
DIGIT [1-9][0-9]*
EXPONENT {CIFRA_ZEC}+
SPATIIALBE [\n\t\r ]
DELIMITATOR ";"|"."|","|":"
MATRICE ".."
OPERATOR_SIMPLU "+"|"-"|"*"|"/"|"("|")"|"["|"]"|"<"|">"
MMICE "<="
MMAREE ">="
DIFERIT "<>"
ATRIBUIRE ":="
EGAL "="
ARRAY_SIGN ".."
SPEC_CHAR "\""|"\`"|"\!"|"\@"|"\#"|"\$"|"\%"|"\^"|"\&"|"\_"|"\|"|"\\"|"\?"
CARACTER_TIPARIBIL	{LITERA}|{DELIMITATOR}|{OPERATOR_SIMPLU}|{CIFRA_ZEC}|{SPEC_CHAR}|{MMAREE}|{MATRICE}|{MMICE}|{ATRIBUIRE}|{EGAL}
IDENT {LITERA}({LITERA}|{CIFRA_ZEC})*
%%
begin		{return KW_BEGIN;}
end		{return KW_END;}
program		{return KW_PROGRAM;}
read		{return KW_READ;}
const		{return KW_CONST;}
array		{return KW_ARRAY;}
function	{return KW_FUNCT;}
procedure	{return KW_PROC;}
var		{return KW_VAR;}
mod		{return KW_MOD;}
div		{return KW_DIV;}
if		{return KW_IF;}
then		{return KW_THEN;}
else		{return KW_ELSE;}
while		{return KW_WHILE;}
do		{return KW_DO;}
for		{return KW_FOR;}
repeat		{return KW_REPEAT;}
until		{return KW_UNTIL;}
to		{return KW_TO;}
downto		{return KW_DOWNTO;}
step		{return KW_STEP;}
case		{return KW_CASE;}
of		{return KW_OF;}
otherwise	{return KW_OTHERWISE;}
print		{return KW_PRINT;}
real		{return KW_REAL;}
integer		{return KW_INT;}
char		{return KW_CHAR;}
record		{return KW_RECORD;}
not		{return KW_NOT;}
and		{return KW_AND;}
or		{return KW_OR;} 
({CIFRA_ZEC}+"#"({CIFRA}+)*)				{return CONST_NUM;}
({DIGIT}+)"."({DIGIT}+)((E|e)("+"|"-")?{EXPONENT})?	{return CONST_NUM;}
{DIGIT}+						{return CONST_NUM;}
'({CARACTER_TIPARIBIL}|" ")'				{return CONST_CAR;}
"\""(({CARACTER_TIPARIBIL}+)|" ")*"\"" {return CONST_SIR;}
"{"(({CARACTER_TIPARIBIL}|{SPATIIALBE})*)"}"		{printf("Comentariu");}
"\n" 			{line++;}
{OPERATOR_SIMPLU}	{return yytext[0];}
{MMICE}			{return OP_REL_MMICEGAL;}
{MMAREE}		{return OP_REL_MMAREEGAL;}
{DIFERIT}		{return OP_REL_DIFERIT;} 
{EGAL}			{return OP_REL_EGAL;}
{ATRIBUIRE}		{return ATRIB_ATOM;}
{DELIMITATOR}		{return yytext[0];}
{ARRAY_SIGN}		{return DOUAP;}
{IDENT}			{return IDENT;}
%%
/*
main(argc, argv)
int argc;
char **argv;
	{
	++argv,--argc;
	if ( argc > 0 ) 
		yyin = fopen( argv[0], "r");
	else yyin = stdin;
	yylex();
	printf("There was %d lines\n", line);
	}
*/

