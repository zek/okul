%{
#include <iostream>
#include <string>
#include "15290090.tab.h"

using namespace std;

#define YY_ALWAYS_INTERACTIVE 1

#define YY_DECL extern "C" int yylex()

int line_num = 1;


string lex_string;

int Lex_CharEsc(char *str)
{
	 int a,c;
	 char *p;

	 a=str[1];
	 switch(a) {
		case 'n':
			c='\n';
			break;
		case 'r':
			c='\r';
			break;
		case 't':
			c='\t';
			break;
		case '\\':
			c='\\';
			break;
		case '\'':
			c='\'';
			break;
		default:
			if (a>='0' && a<='7') {
				 c=a - '0';
				 p=&str[2];
				 while ( *p >= '0' && *p <='7' ) {
						c=c*8 + (*p - '0');
						p++;
				 }
			} else {
				 c=0;
			}
			break;
	 }
	 return c;
}



%}


hexdigit [0-9A-Fa-f]
char_esc n|t|v|b|r|f|a|\\|\?|\"|\'|[0-7]+|x{hexdigit}+

%option yylineno

%x _STRING
%x COMMENT
%x PREPROCESS
%%

\"                 {
	 BEGIN(_STRING);
	 lex_string = std::string("");
}

<_STRING>[^\"\\]      {
	 lex_string += yytext[0];
}

<_STRING>\\{char_esc} {
	 lex_string += Lex_CharEsc(yytext);
}

<_STRING>\"         {
	 BEGIN(INITIAL);
	 yylval.sval = strdup(lex_string.c_str());
	 return STRING;
}


"/*"                   { BEGIN(COMMENT);}
<COMMENT>[^*\n]*       { }
<COMMENT>"*"+[^*/\n]*  { }
<COMMENT>\n            { }
<COMMENT>"*/"          { BEGIN(INITIAL); }

"//"          { BEGIN(PREPROCESS);}
<PREPROCESS>.  { }
<PREPROCESS>\n { BEGIN(INITIAL); }


0[xX]{hexdigit}+ {
	 char* pEnd;
	 yylval.ival = strtol(yytext + 2, &pEnd, 16); return INT;
}

[1-9][0-9]*  {
	 char* pEnd;
	 yylval.ival = strtol(yytext, &pEnd, 10); return INT;
}

[0-7]+ {
	 char* pEnd;
	 yylval.ival = strtol(yytext, &pEnd, 8); return INT;
}



[ \t]		;
[\n]        ;

int	return TYPE_INT;
char return TYPE_CHAR;
void return TYPE_VOID;
double return TYPE_DOUBLE;
for 	return FOR;
while	return WHILE;
if	return IF;
else	return ELSE;
printf  return PRINTF;
struct 	return STRUCT;
return 	return RETURN;
main 	return MAIN;

read 	return READ;
output 	return OUTPUT;
print 	return PRINT;
readc 	return READC;
outputc return OUTPUTC;



"#include" { return INCLUDE; }

[a-zA-z_]([a-zA-Z0-9_]*) {
    yylval.sval = strdup(yytext);
    return IDENTIFIER;
}


";"    return SEMICOLON;
","    return COMMA;
"."     return DOT;

"{"    return LCURLY;
"}"    return RCURLY;

"*"    return MUL;
"/"    return DIV;
"+"    return ADD;
"-"    return SUB;
"%"    return MOD;

"="    return ASSIGN;
"<="    return LE;
">="    return GE;
"=="    return EQ;
"!="    return NE;
">"	return GT;
"<"	return LT;

\(   {return LPAREN;}
\)   {return RPAREN;}


\'.\'            {
    yylval.cval = yytext[1];
    return CHAR;
}
\'\\{char_esc}\' {
    yylval.cval = Lex_CharEsc(yytext+1);
    return CHAR;
}

\'.\' {
      	yylval.cval = yytext[1];
      	return CHAR;
      }

.       return yytext[0];
%%
