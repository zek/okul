%{
#include <cstdio>
#include <iostream>
using namespace std;

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

extern "C" char* yytext;
extern "C" int yylineno;

void yyerror(const char *s);

%}

%union {
	int ival;
	char *sval;
	char cval;
}

%token TYPE_INT TYPE_FLOAT TYPE_CHAR TYPE_DOUBLE TYPE_VOID
%token LPAREN RPAREN
%token FOR WHILE
%token IF ELSE PRINTF
%token STRUCT
%token NUM ID
%token INCLUDE
%token DOT COMMA SEMICOLON
%token LCURLY RCURLY
%token READ PRINT OUTPUT OUTPUTC READC
%token RETURN ASSIGN, MAIN


%right '='
%left AND OR
%left MUL DIV ADD SUB MOD
%left LE GE EQ NE LT GT

%token INT CHAR STRING IDENTIFIER

%start program;

%%

// KURALLAR

program
    : includes decls procedure main
    | includes procedure main
;

includes
    : INCLUDE STRING
    | includes INCLUDE STRING
    | /* EMPTY */
;

main:
    MAIN LPAREN RPAREN body
;


procedure
    : typedident LPAREN args RPAREN body
    | procedure typedident LPAREN args RPAREN body
    | /* EMPTY */
;

body
    : LCURLY decls stmlist RCURLY
;

decls
    : typedident SEMICOLON
    | decls typedident SEMICOLON
    | /* empty */
;

args
    : typedident
    | args COMMA typedident
    | /* empty */
;

typedident
    : TYPE_INT IDENTIFIER
    | TYPE_CHAR IDENTIFIER
;

stmlist
    : stmt
    | stmt stmlist
    | /* empty */
;

stmt
    : LCURLY stmlist RCURLY
    | WHILE LPAREN exp RPAREN stmt
    | IF LPAREN exp RPAREN stmt ELSE stmt
    | IF LPAREN exp RPAREN stmt
    | IDENTIFIER ASSIGN lexp SEMICOLON
    | READ LPAREN IDENTIFIER RPAREN SEMICOLON
    | OUTPUT LPAREN IDENTIFIER RPAREN SEMICOLON
    | PRINT LPAREN STRING RPAREN SEMICOLON
    | RETURN SEMICOLON
    | RETURN lexp SEMICOLON;
    | READC LPAREN IDENTIFIER RPAREN SEMICOLON
    | OUTPUTC LPAREN IDENTIFIER RPAREN SEMICOLON
    | IDENTIFIER LPAREN params RPAREN SEMICOLON
;

exp
    : lexp GT lexp
    | lexp LT lexp
    | lexp LE lexp
    | lexp GE lexp
    | lexp NE lexp
    | lexp EQ lexp
    | lexp
	;

lexp
    : term
    | lexp ADD term
    | lexp SUB term
	;

term
    : factor
    | term MUL factor
    | term DIV factor
    | term MOD factor
	;

factor
    : LPAREN lexp RPAREN
    | SUB IDENTIFIER
    | SUB number
    | number
    | IDENTIFIER
    | CHAR
    | IDENTIFIER LPAREN params RPAREN
	;

params
    : IDENTIFIER
    | IDENTIFIER COMMA params
	;


number
    : INT
	;

%%

int main() {
	do {
		yyparse();
	} while (!feof(stdin));
    cout << "Success!" << endl;
}

void yyerror(const char *s) {
    cout << s << " on line " << yylineno << endl << "Unexpected: " << yytext << "\n";
	exit(-1);
}
