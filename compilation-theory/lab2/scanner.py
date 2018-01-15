import ply.lex as lex

reserved = {
    'if': 'IF',
    'else': 'ELSE',
    'for': 'FOR',
    'while': 'WHILE',

    'break': 'BREAK',
    'continue': 'CONTINUE',
    'return': 'RETURN',

    'eye': 'EYE',
    'zeros': 'ZEROS',
    'ones': 'ONES',

    'print': 'PRINT',

    'int': 'INT',
    'float': 'FLOAT',
    'string': 'STRING',

}

# A string containing ignored characters (spaces and tabs)

# List of token names.   This is always required
tokens = [
             'INTNUM',
             'FLOATNUM',
             'ID',

             'DOTADD',
             'DOTDIV',
             'DOTMUL',
             'DOTSUB',

             'ADDASSIGN',
             'DIVASSIGN',
             'MULASSIGN',
             'SUBASSIGN',

             'LE',
             'GE',
             'NE',
             'EQ',
         ] + list(reserved.values())

t_DOTADD = r'\.\+'
t_DOTSUB = r'\.\-'
t_DOTDIV = r'\.\/'
t_DOTMUL = r'\.\*'

t_ADDASSIGN = r'\+\='
t_MULASSIGN = r'\*\='
t_DIVASSIGN = r'\/\='
t_SUBASSIGN = r'\-\='

literals = ['{', '}', '(', ')', '[', ']', '=', '*', '/', '+', '-', ';', '\'', '<', '>', ':']

t_LE = r'<='
t_GE = r'>='
t_NE = r'!='
t_EQ = r'=='


def t_IDENTIFIER(t):
    r'[a-zA-Z_][a-zA-Z_0-9]*'
    t.type = reserved.get(t.value, 'ID')  # Check for reserved words
    return t

def t_FLOATNUM(t):
    r'[+-]?(?:(?:\d+\.\d*)|(?:\.\d+))(?:e[+-]\d*)?'
    t.value = float(t.value)
    return t


def t_INTNUM(t):
    r'\d+'
    t.value = int(t.value)
    return t


# Define a rule so we can track line numbers

def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

t_ignore = ' \t'


# Error handling rule
def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)


def find_column(input, token):
    last_cr = input.rfind('\n', 0, token.lexpos)
    column = (token.lexpos - last_cr)
    return column


def t_COMMENT(t):
    r'\#.*'
    pass


def build():
    return lex.lex()
