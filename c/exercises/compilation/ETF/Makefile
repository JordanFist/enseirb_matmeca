all		:	lex.yy.c y.tab.c parse
lex.yy.c	:	calculette.l 
			lex calculette.l 
y.tab.c		:	calculette.y lex.yy.c
			bison -y -v calculette.y
parse		:	y.tab.c
			cc y.tab.c -lfl -o parse
clean		:	
			rm -f 	lex.yy.c y.tab.c parse *~ y.output
