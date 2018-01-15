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
    'AND','OR', 'STRING'
         ] + list(reserved.values())

t_DOTADD = r'\.\+'
t_DOTSUB = r'\.\-'
t_DOTDIV = r'\.\/'
t_DOTMUL = r'\.\*'

t_ADDASSIGN = r'\+\='
t_MULASSIGN = r'\*\='
t_DIVASSIGN = r'\/\='
t_SUBASSIGN = r'\-\='

literals = ['{', '}', '(', ')', '[', ']', '=', '*', '/', '+', '-', ';', '\'', '<', '>', ':', ',']

t_LE = r'\<\='
t_GE = r'\>\='
t_NE = r'\!\='
t_EQ = r'\=\='

t_AND = '\&\&'
t_OR = '\|\|'


def t_COMMENT(t):
    r'\#.*'
    pass

def t_IDENTIFIER(t):
    r'[a-zA-Z_][a-zA-Z_0-9]*'
    t.type = reserved.get(t.value, 'ID')  # Check for reserved words
    return t


# A regular expression rule with some action code
def t_FLOATNUM(t):
    r'[+-]?(?:(?:\d+\.\d*)|(?:\.\d+))(?:e[+-]\d*)?'
    t.value = float(t.value)
    return t

# A regular expression rule with some action code
def t_INTNUM(t):
    r'\d+'
    t.value = int(t.value)
    return t

def t_STRING(t):
    r'"(.*?)"'
    t.value = t.value[1:-1]
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


lexer = lex.lex()


def find_tok_column(token):
    last_cr = lexer.lexdata.rfind('\n', 0, token.lexpos)
    column = (token.lexpos - last_cr)
    return column

