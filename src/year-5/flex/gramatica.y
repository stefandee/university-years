%{
#include <stdio.h>
#include "lex.yy.c" 
%}


/*%union {
  int    intVal;
  char*  chpVal;
  double dblVal;
}
*/

%token KW_BEGIN
%token KW_END
%token KW_PROGRAM
%token KW_READ
%token IDENT
%token OP_REL_MMICEGAL
%token OP_REL_MMAREEGAL
%token OP_REL_EGAL
%token OP_REL_DIFERIT
%token ATRIB_ATOM
%token KW_CONST
%token KW_INT
%token KW_REAL
%token KW_CHAR
%token DOUAP
%token KW_ARRAY
%token KW_FUNCT
%token KW_PROC
%token KW_VAR
%token KW_MOD
%token KW_DIV
%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_DO
%token KW_FOR
%token KW_REPEAT
%token KW_UNTIL
%token KW_TO
%token KW_DOWNTO
%token KW_STEP
%token KW_CASE
%token KW_OF
%token KW_OTHERWISE
%token KW_PRINT
%token KW_READ
%token CONST_SIR
%token CONST_CAR
%token CONST_NUM
%token KW_RECORD
%token KW_NOT
%token KW_AND
%token KW_OR
%%
program_sursa:	KW_PROGRAM IDENT ';' Bloc '.';
Bloc:		Sectiune_const Sectiune_var Sectiune_decl_subprog Instr_comp;
Sectiune_const:	/* empty */
		| KW_CONST Lista_decl_const ';';
Lista_decl_const:	Declar_const
                        | Lista_decl_const Declar_const;
Sectiune_var:/* empty */ 
             | KW_VAR Lista_decl_var;
Lista_decl_var: Declar_var 
                | Lista_decl_var Declar_var;
Sectiune_decl_subprog: /* empty */
                       | Lista_decl_subprog;
Lista_decl_subprog: Decl_subprog
                    | Lista_decl_subprog Decl_subprog;
Decl_subprog: Declar_functie
              | Declar_procedura;
Declar_const: IDENT '=' Expresie_statica ';';
Declar_var: Lista_id ':' Tip ';';
Lista_id: IDENT
          | Lista_id ',' IDENT;
Tip: Tip_simplu | Tip_tablou | Tip_struct;
Tip_simplu: KW_REAL | KW_INT | KW_CHAR;
Tip_tablou: KW_ARRAY '[' Expresie_statica DOUAP Expresie_statica ']' Tip_simplu;
Tip_struct: KW_RECORD Lista_cimp KW_END;
Lista_cimp: Decl_simpla
            | Lista_cimp ';' Decl_simpla;
Decl_simpla: Lista_id ';' Tip_simplu;
Declar_functie: KW_FUNCT Antet_subprog ':' Tip_simplu ';' Bloc ';';
Declar_procedura: KW_PROC Antet_subprog ';' Bloc ';';
Antet_subprog: IDENT Param_form;
Param_form: /* empty */
            | '(' Lista_param_form ')';
Lista_param_form: Declar_par
                  | Lista_param_form ';' Declar_par;
Declar_par: Decl_simpla
            | KW_VAR Decl_simpla;
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
       | KW_DIV
       | KW_MOD;
Constanta: CONST_NUM
           | CONST_CAR;
Instr_comp: KW_BEGIN Lista_instr KW_END
            | KW_BEGIN Lista_instr ';' KW_END;
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
Instr_If: KW_IF Conditie KW_THEN Instr Ramura_else;
Ramura_else: /* empty */
             | KW_ELSE Instr;
Conditie: Expr_logica 
          | KW_NOT Expr_logica;
Expr_logica: Expr_rel
             | Expr_logica Op_log Expr_logica;
Op_log: KW_AND
        | KW_OR;
Expr_rel: Expresie Op_rel Expresie
          | '(' Conditie ')';
Op_rel: '<'
        | '>'
        | OP_REL_MMAREEGAL
        | OP_REL_MMICEGAL
        | OP_REL_EGAL
        | OP_REL_DIFERIT;
Instr_while: KW_WHILE Conditie KW_DO Instr;
Instr_repeat: KW_REPEAT Instr KW_UNTIL Conditie;
Instr_for: KW_FOR Variabila ATRIB_ATOM Expresie Sens Expresie Pas KW_DO Instr;
Sens: KW_TO 
      | KW_DOWNTO;
Pas: /* empty */
     | KW_STEP Expresie;
Instr_case: KW_CASE Expresie KW_OF Lista_altern KW_END;
Lista_altern: Lista_ramuri
              | Lista_ramuri KW_OTHERWISE ':' Instr;
Lista_ramuri: Ramura 
              | Lista_ramuri Ramura;
Ramura: Lista_val ':' Instr ';';
Lista_val: Constanta 
           | Lista_val ',' Constanta;
Instr_print: KW_PRINT '(' Lista_elem ')';
Lista_elem: Element
            | Lista_elem ',' Element;
Element: Expresie
         | CONST_SIR;
Instr_read: KW_READ '(' Lista_variab ')';
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








