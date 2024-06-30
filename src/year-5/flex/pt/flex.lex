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
begin		{return CUVINT_KHEIE_BEGIN;}
end		{return CUVINT_KHEIE_END;}
program		{return CUVINT_KHEIE_PROGRAM;}
read		{return CUVINT_KHEIE_READ;}
const		{return CUVINT_KHEIE_CONST;}
array		{return CUVINT_KHEIE_ARRAY;}
function	{return CUVINT_KHEIE_FUNCT;}
procedure	{return CUVINT_KHEIE_PROC;}
var		{return CUVINT_KHEIE_VAR;}
mod		{return CUVINT_KHEIE_MOD;}
div		{return CUVINT_KHEIE_DIV;}
if		{return CUVINT_KHEIE_IF;}
then		{return CUVINT_KHEIE_THEN;}
else		{return CUVINT_KHEIE_ELSE;}
while		{return CUVINT_KHEIE_WHILE;}
do		{return CUVINT_KHEIE_DO;}
for		{return CUVINT_KHEIE_FOR;}
repeat		{return CUVINT_KHEIE_REPEAT;}
until		{return CUVINT_KHEIE_UNTIL;}
to		{return CUVINT_KHEIE_TO;}
downto		{return CUVINT_KHEIE_DOWNTO;}
step		{return CUVINT_KHEIE_STEP;}
case		{return CUVINT_KHEIE_CASE;}
of		{return CUVINT_KHEIE_OF;}
otherwise	{return CUVINT_KHEIE_OTHERWISE;}
print		{return CUVINT_KHEIE_PRINT;}
real		{return CUVINT_KHEIE_REAL;}
integer		{return CUVINT_KHEIE_INT;}
char		{return CUVINT_KHEIE_CHAR;}
record		{return CUVINT_KHEIE_RECORD;}
not		{return CUVINT_KHEIE_NOT;}
and		{return CUVINT_KHEIE_AND;}
or		{return CUVINT_KHEIE_OR;} 
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

