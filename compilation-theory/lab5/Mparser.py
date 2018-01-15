#!/usr/bin/python

from scanner import Scanner
import ply.yacc as yacc
import ply.lex as lex
from AST import *


class Mparser:

    def __init__(self):
        self.scanner = Scanner()
        self.scanner.build()

    tokens = Scanner.tokens
    precedence = (
        # to fill ...
        ('nonassoc', 'IFX'),
        ('nonassoc', 'ELSE'),
        ("left", '+', '-', 'DOTADD', 'DOTSUB'),
        ("left", '*', '/', 'DOTMUL', 'DOTDIV'),
        ("right", "UMINUS", "'")
        # to fill ...
    )

    error = 0

    def p_error(self, p):
        self.error = 1
        if p:
            print("Syntax error at line {0}, column {1}: LexToken({2}, '{3}')".format(p.lineno,
                                                                                      self.scanner.find_tok_column(p),
                                                                                      p.type, p.value))
        else:
            raise SyntaxError('Unexpected EOF while parsing')

    def p_program(self, p):
        """program : instructions_opt"""
        p[0] = Program(p[1])
        p[0].line = self.scanner.lexer.lineno

    def p_instructions_opt_1(self, p):
        """instructions_opt : instructions """
        p[0] = p[1]
        p[0].line = self.scanner.lexer.lineno

    def p_instructions_opt_2(self, p):
        """instructions_opt : """
        p[0] = InstructionList([])
        p[0].line = self.scanner.lexer.lineno

    def p_instructions_1(self, p):
        """instructions : instructions instruction """
        if p[2]:
            p[0] = InstructionList(p[1].instructions + [p[2]])
        else:
            p[0] = p[1]
        p[0].line = self.scanner.lexer.lineno

    def p_instructions_2(self, p):
        """instructions : instruction """
        p[0] = InstructionList([p[1]])
        p[0].line = self.scanner.lexer.lineno

    def p_instruction(self, p):
        '''instruction : assignment ';'
                    | iteration_instruction
                    | selection_instruction
                    | print_instruction
                    | compound_statement
        '''
        p[0] = p[1]
        if (p[0]):
            p[0].line = self.scanner.lexer.lineno

    def p_instruction_break(self, p):
        '''
        instruction : BREAK ';'
        '''
        p[0] = BreakInst()
        p[0].line = self.scanner.lexer.lineno

    def p_instruction_continue(self, p):
        '''
        instruction : CONTINUE ';'
        '''
        p[0] = ContinueInst()
        p[0].line = self.scanner.lexer.lineno

    def p_instruction_return(self, p):
        '''
        instruction : RETURN ';'
        '''
        p[0] = ReturnInst()
        p[0].line = self.scanner.lexer.lineno

    def p_instruction_return_2(self, p):
        '''
        instruction : RETURN expr ';'
        '''
        p[0] = ReturnInst(p[2])
        p[0].line = self.scanner.lexer.lineno



    def p_compound_statement(self, p):
        '''
        compound_statement : '{' '}'
        '''
        p[0] = Empty()

    def p_compound_statement_2(self, p):
        '''
        compound_statement : '{' instructions '}'
        '''
        p[0] = p[2]
        p[0].line = self.scanner.lexer.lineno

    def p_expr_number(self, p):
        '''expr : INTNUM
        '''
        p[0] = IntNum(p[1])
        p[0].line = self.scanner.lexer.lineno

    def p_expr_float(self, p):
        '''expr : FLOATNUM
        '''
        p[0] = FloatNum(p[1])
        p[0].line = self.scanner.lexer.lineno

    def p_expr_string(self, p):
        '''expr : STRING
        '''
        p[0] = String(p[1])
        p[0].line = self.scanner.lexer.lineno

    def p_expr_binary(self, p):
        '''expr : expr '+' expr
                | expr '-' expr
                | expr '*' expr
                | expr '/' expr
                | expr DOTADD expr
                | expr DOTDIV expr
                | expr DOTMUL expr
                | expr DOTSUB expr
                '''
        p[0] = BinExpr(p[2], p[1], p[3])
        p[0].line = self.scanner.lexer.lineno

    def p_expr_relational(self, p):
        '''expr_rel : expr '>' expr
                | expr '<' expr
                | expr LE expr
                | expr GE expr
                | expr NE expr
                | expr EQ expr
                '''
        p[0] = RelExpr(p[2], p[1], p[3])
        p[0].line = self.scanner.lexer.lineno

    def p_expr_relational_2(self, p):
        '''expr_rel : expr'''
        p[0] = p[1]
        p[0].line = self.scanner.lexer.lineno

    def p_expr_logic(self, p):
        '''expr_logic : expr_rel  '''
        p[0] = p[1]
        p[0].line = self.scanner.lexer.lineno

    def p_expr_logic_2(self, p):
        '''expr_logic : expr_logic AND expr_rel
                | expr_logic OR expr_rel
                '''
        p[0] = LogExpr(p[2], p[1], p[3])
        p[0].line = self.scanner.lexer.lineno

    def p_expr_fcall(self, p):
        '''expr : ZEROS '(' argument_list_or_empty ')'
                | ONES '(' argument_list_or_empty ')'
                | EYE '(' argument_list_or_empty ')'
                '''
        p[0] = FCall(p[1], p[3])
        p[0].line = self.scanner.lexer.lineno

    def p_matris_1(self, p):
        '''expr : '[' matris ']'
        '''
        p[0] = Matris(p[2])
        p[0].line = self.scanner.lexer.lineno

    def p_matris_2(self, p):
        '''matris   : matris ';' vector
        '''
        p[0] = p[1] + [p[3]]

    def p_matris_3(self, p):
        '''matris   : vector
        '''
        p[0] = [p[1]]

    def p_vector(self, p):
        '''vector : vector_sub
        '''
        p[0] = Vector(p[1])
        p[0].line = self.scanner.lexer.lineno

    def p_vector_sub_1(self, p):
        '''vector_sub   : vector_sub ',' expr
        '''
        p[0] = p[1] + [p[3]]

    def p_vector_sub_2(self, p):
        '''vector_sub   : expr
        '''
        p[0] = [p[1]]

    def p_expr_id(self, p):
        '''expr : idexp
        '''
        p[0] = p[1]
        p[0].line = self.scanner.lexer.lineno

    def p_selection_instruction_1(self, p):
        '''
        selection_instruction : IF '(' expr_logic ')' instruction ELSE instruction
        '''
        p[0] = IfExpr(p[3], p[5], p[7])
        p[0].line = self.scanner.lexer.lineno


    def p_selection_instruction_2(self, p):
        '''
        selection_instruction : IF '(' expr_logic ')' instruction %prec IFX
        '''
        p[0] = IfExpr(p[3], p[5])
        p[0].line = self.scanner.lexer.lineno

    def p_selection_instruction_error(self, p):
        '''
        selection_instruction : IF '(' error ')' instruction ELSE instruction
                              | IF '(' error ')' instruction %prec IFX
        '''
        print("Expression expected")
        exit(0)

    def p_iteration_instruction_2(self, p):
        '''
        selection_instruction : WHILE '(' expr_logic ')' instruction
        '''
        p[0] = WhileLoop(p[3], p[5])
        p[0].line = self.scanner.lexer.lineno

    def p_iteration_instruction_error_2(self, p):
        '''
        selection_instruction : WHILE '(' error ')' instruction
        '''
        print("Expression expected")
        exit(0)

    def p_iteration_instruction_1(self, p):
        '''
            iteration_instruction : FOR ID '=' expr ':' expr instruction
        '''
        p[0] = ForLoop(Variable(p[2]), p[4], p[6], p[7])
        p[0].line = self.scanner.lexer.lineno


    def p_iteration_instruction_error(self, p):
        '''
            iteration_instruction : FOR ID expr ':' expr error
        '''
        print("Expected expression")
        exit(0)


    def p_argument_list_or_empty(self, p):
        """argument_list_or_empty : argument_list"""
        p[0] = ArgumentList(p[1], None)
        p[0].line = self.scanner.lexer.lineno

    def p_argument_list_or_empty_2(self, p):
        """argument_list_or_empty : """
        p[0] = ArgumentList(None, None)
        p[0].line = self.scanner.lexer.lineno

    def p_argument_list(self, p):
        '''argument_list :  expr '''
        p[0] = ArgumentList(None, p[1])
        p[0].line = self.scanner.lexer.lineno

    def p_argument_list_2(self, p):
        '''argument_list :  argument_list ',' expr'''
        p[0] = ArgumentList(p[1], p[3])
        p[0].line = self.scanner.lexer.lineno

    def p_print_instruction(self, p):
        '''
            print_instruction : PRINT argument_list_or_empty ';'
        '''
        p[0] = PrintExpr(p[2])
        p[0].line = self.scanner.lexer.lineno

    def p_print_instruction_error(self, p):
        '''
            print_instruction : PRINT argument_list_or_empty error
        '''
        print("Semicolon expected!")

    def p_id(self, p):
        '''idexp : ID'''
        p[0] = Variable(p[1])
        p[0].line = self.scanner.lexer.lineno

    def p_id_index(self, p):
        '''idexp : ID '[' expr ']'
        '''
        p[0] = IdRef(Variable(p[1]), p[3])
        p[0].line = self.scanner.lexer.lineno

    def p_id_index_2(self, p):
        '''idexp : ID '[' expr ',' expr ']'
        '''
        p[0] = IdRef(Variable(p[1]), p[3], p[5])
        p[0].line = self.scanner.lexer.lineno

    def p_expr_uminus(self, p):
        '''expr : - expr %prec UMINUS
        '''
        p[0] = UnaryExpr('UMINUS', p[2])
        p[0].line = self.scanner.lexer.lineno

    def p_expr_transpose(self, p):
        '''expr : expr "'"
        '''
        p[0] = UnaryExpr("TRANSPOSE", p[1])
        p[0].line = self.scanner.lexer.lineno

    def p_assignment(self, p):
        '''assignment : idexp '=' expr
                    |   idexp ADDASSIGN expr
                    |   idexp DIVASSIGN expr
                    |   idexp MULASSIGN expr
                    |   idexp SUBASSIGN expr
        '''
        p[0] = Assignment(p[1], p[2], p[3])
        p[0].line = self.scanner.lexer.lineno

    def p_instruction_error(self, p):
        '''
        instruction : BREAK error
                    | assignment error
        '''
        print('Semicolon is needed!')
        exit(0)
