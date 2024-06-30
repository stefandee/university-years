%{
#include <stdio.h>
#include <stdlib.h>
#define YYDEBUG 1

#define TIP_INT  1
#define TIP_REAL 2
#define TIP_CAR  3

double stiva[20];
int sp;

extern int linie;

void err(char *msg)
{
  fprintf(stderr, "Eroare sintactica la linia: %d ->> ", linie);
  yyerror(msg);
}

void push(double x)
{ stiva[sp++]=x; }

double pop()
{ return stiva[--sp]; }

%}

%union {
  	int l_val;
	char *p_val;
}

%token BEGINN
%token CASE
%token CONST
%token DO
%token DOWNTO
%token ELSE
%token END
%token FOR
%token FUNCTION
%token IF
%token OF
%token PROCEDURE
%token PRINT
%token PROGRAM
%token READ
%token REPEAT
%token THEN
%token UNTIL
%token VAR
%token WHILE
%token ARRAY
%token RECORD
%token TO
%token STEP
%token OTHERWISE

%token ID
%token <p_val> CONST_INT
%token <p_val> CONST_REAL
%token <p_val> CONST_CAR
%token CONST_SIR

%token CHAR
%token INTEGER
%token REAL

%token ATRIB
%token NE
%token LE
%token GE
%token DOTDOT

%left '+' '-'
%left DIV MOD '*' '/'
%left OR
%left AND
%left NOT

%type <l_val> expr_stat factor_stat constanta
%%

prog_sursa:	PROGRAM ID ';' bloc '.'
		| error {err("lipseste PROGRAM ");} ID ';' bloc '.'	
		| PROGRAM error {err("lipseste ID");} ';' bloc '.'
		| PROGRAM ID error {err("lipseste ;");} bloc '.'
		| PROGRAM ID ';' error {err("bloc");} '.'
		;
bloc:		sect_const sect_var sect_subprog instr_comp
		;
sect_const:	/* empty */
		| CONST lista_const
		;
lista_const:	decl_const
		| lista_const decl_const
		;
sect_var:	/* empty */
		| VAR lista_var
		;
lista_var:	decl_var
		| lista_var decl_var
		;
decl_const:	ID '=' {sp=0;} expr_stat ';'	{
		  printf("in linia %d se declara: *** %d %g ***\n", linie, $4, pop());
		}
		| error {err("lipseste ID");} '=' {sp=0;} ';'
		| ID error {err("lipseste ="); sp=0;} ';'
		;
decl_var:	lista_id ':' tip ';'
                | lista_id ':'  error {err("tip");} ';'
		;
lista_id:	ID
		| lista_id ',' ID
		| lista_id error {err("lipseste ,");} ID
		;
sect_subprog:	/* empty */
		| sect_func_proc
		| sect_subprog sect_func_proc
		;
sect_func_proc:	PROCEDURE antet_proc bloc ';'
		| FUNCTION antet_func bloc ';'
		;
antet_proc:	ID parametri ';'
		| ID error {err("parametri");} ';'
		| error {err("lipseste ID");}parametri ';'
		;
antet_func:	ID parametri ':' tip_simplu ';'
		| error {err("lipseste ID");}  parametri ':' tip_simplu ';'
		| ID error {err("parametri");} ':' tip_simplu ';'
		| ID parametri ':' error {err("tip_simplu");} ';'
		;
tip:		tip_simplu
		| tip_tablou
		| tip_record
		;
tip_simplu:	INTEGER
		| REAL
		| CHAR
		;
parametri:	/* empty */
		| '(' sect_decl_param ')'
		| error {err("lipseste (");}  sect_decl_param ')'
		| '(' error {err("sect_decl_param");} ')'
		| '(' sect_decl_param error {err("lipseste )");}
		;
sect_decl_param: decl_param
		|sect_decl_param ';' decl_param
		|sect_decl_param error {err("lipseste ;");} decl_param
		;
decl_param:	lista_id ':' tip_simplu
		| VAR lista_id ':' tip_simplu
		;
tip_tablou:	ARRAY '[' CONST_INT DOTDOT CONST_INT ']' OF tip_simplu
		| error {err("lipseste ARRAY");} '[' CONST_INT DOTDOT CONST_INT ']' OF tip_simplu	
		| ARRAY error {err("lipseste [");} CONST_INT DOTDOT CONST_INT ']' OF tip_simplu	
		| ARRAY '[' error {err("CONST_INT");} DOTDOT CONST_INT ']' OF tip_simplu	
		| ARRAY '[' CONST_INT error {err("lipseste ..");} CONST_INT ']' OF tip_simplu	
		;
tip_record:	RECORD sect_decl_cimp END
	        | RECORD error {err("sect_decl_cimp");} END 
		;
sect_decl_cimp:	decl_cimp
		| sect_decl_cimp ';' decl_cimp
		;
decl_cimp:	lista_id ':' tip_simplu
                | lista_id error {err("lipseste :");} tip_simplu
		;
expr_stat:	factor_stat
		| expr_stat '+' expr_stat	{
			if($1==TIP_REAL || $3==TIP_REAL) $$=TIP_REAL;
			else if($1==TIP_CAR) $$=TIP_CAR;
				else $$=TIP_INT;
			push(pop()+pop());
						}
		| expr_stat '-' expr_stat	{
			if($1==TIP_REAL || $3==TIP_REAL) $$=TIP_REAL;
			else if($1==TIP_CAR) $$=TIP_CAR;
				else $$=TIP_INT;
			push(-pop()+pop());
						}
		| expr_stat '*' expr_stat	{
			if($1==TIP_REAL || $3==TIP_REAL) $$=TIP_REAL;
			else if($1==TIP_CAR) $$=TIP_CAR;
				else $$=TIP_INT;
			push(pop()*pop());
						}
		| expr_stat '/' expr_stat	
		| expr_stat DIV expr_stat
		| expr_stat MOD expr_stat
		;
factor_stat:	ID		{}
		| constanta
		| '(' expr_stat ')'	{$$ = $2;}
		| '(' error {err("expr_stat");} ')'
		| error {err("lipseste (");} expr_stat ')' {}
		;
constanta:	CONST_INT	{
			$$ = TIP_INT;
			push(atof($1));
				}
		| CONST_REAL	{
			$$ = TIP_REAL;
			push(atof($1));
				}
		| CONST_CAR	{
			$$ = TIP_CAR;
			push((double)$1[0]);
				}
		;
instr_comp:	BEGINN lista_instr END
		| BEGINN error {err("lista_instr");} END
		;
lista_instr:	instr
		| lista_instr ';' instr
		;
instr:		/* empty */
		| instr_atrib
		| instr_while
		| instr_repeat
		| instr_for
		| instr_case
		| instr_comp
		| apel_proced
		| instr_print
		| instr_read
		| instr_if
		;
instr_atrib:	variabila ATRIB expresie
		;
variabila:	ID
		| ID '[' expresie ']'
		| error {err("ID");} '[' expresie ']'
		| ID error {err("lipseste [");} expresie ']'
		| ID '.' ID
		| error {err("ID");} '.' ID
		| ID '[' error {err("expresie");} ']'
		;
expresie:	factor
		| expresie '+' expresie
		| expresie '-' expresie
		| expresie '*' expresie
		| expresie '/' expresie
		| expresie DIV expresie
		| expresie MOD expresie
		;
factor:		ID
		| ID '[' expresie ']'
		| error {err("ID");} '[' expresie ']'
		| ID error {err("lipseste [");} expresie ']'
		| ID '.' ID
		| error {err("ID");} '.' ID
		| constanta {}
		| ID '(' lista_expr ')'
		| '(' expresie ')'
		| ID '[' error {err("expresie");} ']'
		| ID '(' error {err("lista_expr");} ')'
		| '(' error {err("expresie");} ')'
		;
lista_expr:	expresie
		| lista_expr ',' expresie
		| error {err("lista_expr");} ',' expresie
		;
instr_if:	IF conditie THEN instr ramura_else
		| IF error {err("conditie");} THEN instr ramura_else
		;
ramura_else:	/* empty */
		| ELSE instr
		;
conditie:	expr_logica
		| expresie op_rel expresie
		;
expr_logica:	factor_logic
		| expr_logica AND expr_logica
		| expr_logica OR expr_logica
		;
factor_logic:	'(' conditie ')'
		| NOT factor_logic
 		/*| '(' error {err("conditie");} ')'}*/
		;
op_rel:		'='
		| '<'
		| '>'
		| NE
		| LE
		| GE
		;
instr_while:	WHILE conditie DO instr
		| WHILE error {err("conditie");} DO instr
		;
instr_repeat:	REPEAT instr UNTIL conditie
		| REPEAT error {err("instr");} UNTIL conditie
		;
instr_for:	FOR variabila ATRIB expresie to_downto expresie step DO instr
		| FOR error {err("variabila");} ATRIB expresie to_downto expresie step DO instr
		;
to_downto:	TO
		| DOWNTO
		;
step:		/* empty */
		| STEP expresie
		;
instr_case:	CASE expresie OF lista_altern END
		CASE error {err("expresie");} OF lista_altern END
		CASE expresie OF error {err("lista_altern");} END
		;
lista_altern:	altern otherwise
		;
altern:		lista_nr_zec ':' instr
		| altern ';' lista_nr_zec ':' instr
		;
lista_nr_zec:	CONST_INT {}
		| lista_nr_zec ',' CONST_INT
		;
otherwise:	/* empty */
		| OTHERWISE instr
		;
apel_proced:	ID
		| ID '(' lista_expr ')'
		| ID '(' error {err("lista_expr");} ')'
		;
instr_print:	PRINT '(' lista_elem ')'
		;
lista_elem:	element
		| lista_elem ',' element
		;
element:	expresie
		| CONST_SIR
		;
instr_read:	READ '(' lista_variab ')'
		;
lista_variab:	variabila
		| lista_variab ',' variabila
		;

%%

int yyerror(char *s)
{
  fprintf(stderr, "%s a aparut\n", s);
  return 0;
}

extern FILE *yyin;

int main(int argc, char **argv)
{
  if(argc>1) yyin = fopen(argv[1], "r");
  if((argc>2)&&(!strcmp(argv[2],"-d"))) yydebug = 1;
  if(!yyparse()) fprintf(stderr,"\nTerminare analiza.\n");
  return 0;
}


