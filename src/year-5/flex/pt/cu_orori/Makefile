LEX = flex
LEXFLAGS = -ivd
YACC = bison
YACCFLAGS = -vd
CCC = gcc
CCCFLAGS = -o

all:
	 make asin 

gramatica.tab.c: gramatica.y
	$(YACC) $(YACCFLAGS)  gramatica.y
	

lex.yy.c: flex.lex gramatica.tab.h
	$(LEX) $(LEXFLAGS) flex.lex
	
asin: gramatica.tab.c lex.yy.c
	$(CCC) $(CCCFLAGS) $@ gramatica.tab.c lex.yy.c

clean:
	rm -f *.c *.h asin *~ core *.output
	
