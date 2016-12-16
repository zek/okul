all: lex.yy.c 15290090.tab.c 15290090.tab.h
	g++ 15290090.tab.c lex.yy.c -ll -o 15290090
	./15290090 < input


15290090.tab.c 15290090.tab.h: 15290090.y
	bison -d 15290090.y

lex.yy.c: 15290090.l 15290090.tab.h
	flex 15290090.l
