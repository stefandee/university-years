%{
#include <stdio.h>
extern int line;
%}


/*%union {
  int    intVal;
  char*  chpVal;
  double dblVal;
}
*/

%token CUVINT_KHEIE_BEGIN
%token CUVINT_KHEIE_END
%token CUVINT_KHEIE_PROGRAM
%token CUVINT_KHEIE_READ
%token IDENT
%token OP_REL_MMICEGAL
%token OP_REL_MMAREEGAL
%token OP_REL_EGAL
%token OP_REL_DIFERIT
%token ATRIB_ATOM
%token CUVINT_KHEIE_CONST
%token CUVINT_KHEIE_INT
%token CUVINT_KHEIE_REAL
%token CUVINT_KHEIE_CHAR
%token DOUAP
%token CUVINT_KHEIE_ARRAY
%token CUVINT_KHEIE_FUNCT
%token CUVINT_KHEIE_PROC
%token CUVINT_KHEIE_VAR
%token CUVINT_KHEIE_MOD
%token CUVINT_KHEIE_DIV
%token CUVINT_KHEIE_IF
%token CUVINT_KHEIE_THEN
%token CUVINT_KHEIE_ELSE
%token CUVINT_KHEIE_WHILE
%token CUVINT_KHEIE_DO
%token CUVINT_KHEIE_FOR
%token CUVINT_KHEIE_REPEAT
%token CUVINT_KHEIE_UNTIL
%token CUVINT_KHEIE_TO
%token CUVINT_KHEIE_DOWNTO
%token CUVINT_KHEIE_STEP
%token CUVINT_KHEIE_CASE
%token CUVINT_KHEIE_OF
%token CUVINT_KHEIE_OTHERWISE
%token CUVINT_KHEIE_PRINT
%token CUVINT_KHEIE_READ
%token CONST_SIR
%token CONST_CAR
%token CONST_NUM
%token CUVINT_KHEIE_RECORD
%token CUVINT_KHEIE_NOT
%token CUVINT_KHEIE_AND
%token CUVINT_KHEIE_OR

%%

program_sursa: CUVINT_KHEIE_PROGRAM IDENT ';' Bloc '.';

Bloc: Sectiune_const Sectiune_var Sectiune_decl_subprog Instr_comp;

Sectiune_const:	/* empty */
		| CUVINT_KHEIE_CONST Lista_decl_const;

Lista_decl_const: Declar_const
                  | Lista_decl_const Declar_const;

Sectiune_var: /* empty */ 
              | CUVINT_KHEIE_VAR Lista_decl_var;

Lista_decl_var: Declar_var 
                | Lista_decl_var Declar_var;

Sectiune_decl_subprog: /* empty */
                       | Lista_decl_subprog;

Lista_decl_subprog: Decl_subprog
                    | Lista_decl_subprog Decl_subprog;

Decl_subprog: Declar_functie
              | Declar_procedura;

Declar_const: IDENT OP_REL_EGAL Expresie_statica ';';

Declar_var: Lista_id ':' Tip ';';

Lista_id: IDENT
          | Lista_id ',' IDENT;

Tip: Tip_simplu | Tip_tablou | Tip_struct;

Tip_simplu: CUVINT_KHEIE_REAL | CUVINT_KHEIE_INT | CUVINT_KHEIE_CHAR;

Tip_tablou: CUVINT_KHEIE_ARRAY '[' Expresie_statica DOUAP Expresie_statica ']' CUVINT_KHEIE_OF Tip_simplu;

Tip_struct: CUVINT_KHEIE_RECORD Lista_cimp CUVINT_KHEIE_END;

Lista_cimp: Decl_simpla
            | Lista_cimp ',' Decl_simpla;

Decl_simpla: Lista_id ':' Tip_simplu;

Declar_functie: CUVINT_KHEIE_FUNCT Antet_subprog ':' Tip_simplu ';' Bloc ';';

Declar_procedura: CUVINT_KHEIE_PROC Antet_subprog ';' Bloc ';';

Antet_subprog: IDENT Param_form;

Param_form: /* empty */
            | '(' Lista_param_form ')';

Lista_param_form: Declar_par
                  | Lista_param_form ';' Declar_par;
Declar_par: Decl_simpla
            | CUVINT_KHEIE_VAR Decl_simpla;

Expresie_statica: Termen_static | Expresie_statica Op_ad Termen_static;

Termen_static: Factor_static 
               | Termen_static Op_mul Factor_static;

Factor_static: IDENT
               | Constanta
               | '(' Expresie_statica ')';

Op_ad: '+'
       | '-';

Op_mul: '*'
       | '/'
       | CUVINT_KHEIE_DIV
       | CUVINT_KHEIE_MOD;

Constanta: CONST_NUM
           | CONST_CAR;

Instr_comp: /*empty*/
	    | CUVINT_KHEIE_BEGIN Lista_instr CUVINT_KHEIE_END
            | CUVINT_KHEIE_BEGIN Lista_instr ';' CUVINT_KHEIE_END;

Lista_instr: Instr
             | Lista_instr ';' Instr;

Instr: Instr_atrib
       | Instr_If
       | Instr_while
       | Instr_repeat
       | Instr_for
       | Instr_case
       | Instr_comp
       | Apel_proc
       | Instr_read
       | Instr_print;

Instr_atrib: Variabila ATRIB_ATOM Expresie;

Variabila: IDENT 
           | IDENT '[' Expresie ']'
           | IDENT '.' IDENT;

Expresie: Termen
          | Expresie Op_ad Termen;

Termen: Factor
        | Termen Op_mul Factor;

Factor: IDENT
        | Constanta
        | IDENT '(' Lista_expresii ')'
        | '(' Expresie ')'
        | IDENT '[' Expresie ']'
        | IDENT '.' IDENT;

Lista_expresii: Expresie
                | Lista_expresii ',' Expresie;

Instr_If: CUVINT_KHEIE_IF Conditie CUVINT_KHEIE_THEN Instr Ramura_else;

Ramura_else: /* empty */
             | CUVINT_KHEIE_ELSE Instr;

Conditie: Expr_logica 
          | CUVINT_KHEIE_NOT Expr_logica;

Expr_logica: Expr_rel
             | Expr_logica Op_log Expr_logica;

Op_log: CUVINT_KHEIE_AND
        | CUVINT_KHEIE_OR;

Expr_rel: Expresie Op_rel Expresie
          | '(' Conditie ')';

Op_rel: '<'
        | '>'
        | OP_REL_MMAREEGAL
        | OP_REL_MMICEGAL
        | OP_REL_EGAL
        | OP_REL_DIFERIT;

Instr_while: CUVINT_KHEIE_WHILE Conditie CUVINT_KHEIE_DO Instr;

Instr_repeat: CUVINT_KHEIE_REPEAT Instr CUVINT_KHEIE_UNTIL Conditie;

Instr_for: CUVINT_KHEIE_FOR Variabila ATRIB_ATOM Expresie Sens Expresie Pas CUVINT_KHEIE_DO Instr;

Sens: CUVINT_KHEIE_TO 
      | CUVINT_KHEIE_DOWNTO;

Pas: /* empty */
     | CUVINT_KHEIE_STEP Expresie;

Instr_case: CUVINT_KHEIE_CASE Expresie CUVINT_KHEIE_OF Lista_altern CUVINT_KHEIE_END;

Lista_altern: Lista_ramuri
              | Lista_ramuri CUVINT_KHEIE_OTHERWISE ':' Instr;

Lista_ramuri: Ramura 
              | Lista_ramuri Ramura;

Ramura: Lista_val ':' Instr ';';

Lista_val: Constanta 
           | Lista_val ',' Constanta;

Instr_print: CUVINT_KHEIE_PRINT '(' Lista_elem ')';

Lista_elem: Element
            | Lista_elem ',' Element;

Element: Expresie
         | CONST_SIR;

Instr_read: CUVINT_KHEIE_READ '(' Lista_variab ')';

Lista_variab: Variabila
              | Lista_variab ',' Variabila;

Apel_proc: IDENT
           | IDENT '(' Lista_expresii ')';

%%

extern FILE* yyin; 

void main(argc, argv)
int argc;
char** argv;
{
  line = 1;
  if (argc != 2) fprintf(stderr, "Usage asin filename.\n");
  if (argc > 1) yyin = fopen(argv[1], "r"); 
  yyparse();
}

int yyerror(char* s)
{
  printf("Eroare %s in linia %d\n", s, line);
}








