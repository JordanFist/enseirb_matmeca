all		:	var-cal

y.tab.h y.tab.c :	reg-cal.y
			bison -y  -d  reg-cal.y
lex.yy.c	:	reg-cal.l y.tab.h
			flex reg-cal.l 
var-cal		:	lex.yy.c y.tab.c Table_des_symboles.c Table_des_chaines.c
			gcc -o var-cal lex.yy.c y.tab.c Table_des_symboles.c Table_des_chaines.c
clean		:	
			rm -f 	lex.yy.c *.o y.tab.h y.tab.c var-cal *~ y.output
