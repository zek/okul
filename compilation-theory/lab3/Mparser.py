#!/usr/bin/python

import scanner
import ply.yacc as yacc

tokens = scanner.tokens

precedence = (
    # to fill ...
    ('nonassoc', 'IFX'),
    ('nonassoc', 'ELSE'),
    ("left", '+', '-', 'DOTADD', 'DOTSUB'),
    ("left", '*', '/', 'DOTMUL', 'DOTDIV'),
    ("right", "UMINUS")
    # to fill ...
)


def p_error(p):
    if p:
        print("Syntax error at line {0}, column {1}: LexToken({2}, '{3}')".format(p.lineno, scanner.find_tok_column(p),
                                                                                  p.type, p.value))
    else:
        print("Unexpected end of input")



def p_program(p):
    """program : instructions_opt"""
    p[0] = p[1]

def p_instructions_opt_1(p):
    """instructions_opt : instructions """
    p[0] = p[1]

def p_instructions_opt_2(p):
    """instructions_opt : """


def p_instructions_1(p):
    """instructions : instructions instruction """
    p[0] = p[1] + [p[2]]

def p_instructions_2(p):
    """instructions : instruction """
    p[0] = [p[1]]

def p_instruction(p):
    '''instruction : assignment
                | iteration_instruction
                | selection_instruction
                | print_instruction
                | compound_statement
                | BREAK ';'
                | CONTINUE ';'
                | RETURN ';'
    '''
    p[0] = ('STATEMENT', p[1])

def p_compound_statement(p):
    '''
    compound_statement : '{' instructions '}'
                       | '{' '}'
    '''
    if(p.__len__() == 4):
        p[0] = p[2]


def p_expr_number(p):
    '''expr : INTNUM
            | FLOATNUM
    '''
    p[0] = ('NUM', p[1])

def p_expr_string(p):
    '''expr : STRING
    '''
    p[0] = ('STRING', p[1])


def p_expr_binary(p):
    '''expr : expr '+' expr
            | expr '-' expr
            | expr '*' expr
            | expr '/' expr
            | expr DOTADD expr
            | expr DOTDIV expr
            | expr DOTMUL expr
            | expr DOTSUB expr
            '''
    p[0] = ('BINOP', p[2], p[1], p[3])


def p_expr_relational(p):
    '''expr_rel : expr
            | expr '>' expr
            | expr '<' expr
            | expr LE expr
            | expr GE expr
            | expr NE expr
            | expr EQ expr
            '''
    if(p.__len__() == 4):
        p[0] = ('REL', p[2], p[1], p[3])
    else:
        p[0] = p[1]


def p_expr_logic(p):
    '''expr_logic : expr_rel
            | expr_logic AND expr_rel
            | expr_logic OR expr_rel
            '''
    if(p.__len__() == 4):
        p[0] = ('LOG', p[2], p[1], p[3])
    else:
        p[0] = p[1]



def p_expr_fcall(p):
    '''expr : ZEROS '(' expr ')'
            | ONES '(' expr ')'
            | EYE '(' expr ')'
            '''
    p[0] = ('FCALL', p[1], p[3])


def p_matris_1(p):
    '''expr : '[' matris ']'
    '''
    p[0] = ('MATRIS', p[2])

def p_matris_2(p):
    '''matris   : matris ';' matris_sub
                | matris_sub
    '''
    if(p.__len__() == 2):
        p[0] = [p[1]]
    if(p.__len__() == 4):
        p[0] = p[1] + [p[3]]

def p_matris_3(p):
    '''matris_sub   : matris_sub ',' expr
                | expr
    '''
    if(p.__len__() == 2):
        p[0] = [p[1]]
    if(p.__len__() == 4):
        p[0] = p[1] + [p[3]]

def p_expr_id(p):
    '''expr : idexp
    '''
    p[0] = ('ID', p[1])


def p_selection_instruction_1(p):
    '''
    selection_instruction : IF '(' expr_logic ')' instruction ELSE instruction
                          | IF '(' expr_logic ')' instruction %prec IFX
    '''
    if(p.__len__() == 8):
        p[0] = ('IF_ELSE', p[3], p[5], p[7])
    else:
        p[0] = ('IF', p[3], p[5])

def p_iteration_instruction_2(p):
    '''
    selection_instruction : WHILE '(' expr_logic ')' instruction
    '''
    p[0] = ('WHILE', p[3], p[5])


def p_iteration_instruction_1(p):
    '''
        iteration_instruction : FOR ID '=' expr ':' expr instruction
    '''
    p[0] = ('FOR', p[2], p[4], p[6], p[7])

def p_argument_list(p):
    '''argument_list :  expr
                     |  argument_list ',' expr'''
    if(p.__len__() == 2):
        p[0] = [p[1]]
    else:
        p[0] = p[1] + [p[3]]


def p_print_instruction(p):
    '''
        print_instruction : PRINT argument_list ';'
    '''
    p[0] = ('PRINT', p[2])

def p_id(p):
    '''idexp : ID'''
    p[0] = ('ID', p[1])

def p_id_index(p):
    '''idexp : ID '[' expr ']'
            | ID '[' expr ',' expr ']'
    '''
    if(p.__len__() == 5):
        p[0] = ('ID_INDEX', p[1], p[3])
    if(p.__len__() == 7):
        p[0] = ('ID_INDEX', p[1], p[3], p[5])

def p_expr_uminus(p):
    '''expr : - expr %prec UMINUS
    '''
    p[0] = ('UMINUS', p[2])

def p_expr_transpose(p):
    '''expr : expr "'"
    '''
    p[0] = ('TRANSPOSE', p[1])

def p_assignment(p):
    '''assignment : idexp '=' expr ';'
                |   idexp ADDASSIGN expr ';'
                |   idexp DIVASSIGN expr ';'
                |   idexp MULASSIGN expr ';'
                |   idexp SUBASSIGN expr ';'
    '''
    p[0] = ('ASSIGN', p[1], p[2], p[3])



parser = yacc.yacc()

