import ply.lex as lex
class Scanner:

    def find_tok_column(self, token):
        last_cr = self.lexer.lexdata.rfind('\n', 0, token.lexpos)
        if last_cr < 0:
            last_cr = 0
        return token.lexpos - last_cr


    def build(self):
        self.lexer = lex.lex(object=self)

    def input(self, text):
        self.lexer.input(text)

    def token(self):
        return self.lexer.token()

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


    def t_COMMENT(self, t):
        r'\#.*'
        pass

    def t_IDENTIFIER(self, t):
        r'[a-zA-Z_][a-zA-Z_0-9]*'
        t.type = self.reserved.get(t.value, 'ID')  # Check for reserved words
        return t


    # A regular expression rule with some action code
    def t_FLOATNUM(self, t):
        r'[+-]?(\d+\.\d*|\.\d+)([Ee][+-]\d+)?'
        t.value = float(t.value)
        return t

    # A regular expression rule with some action code
    def t_INTNUM(self, t):
        r'\d+'
        t.value = int(t.value)
        return t

    def t_STRING(self, t):
        r'"(.*?)"'
        t.value = t.value[1:-1]
        return t

    # Define a rule so we can track line numbers

    def t_newline(self, t):
        r'\n+'
        t.lexer.lineno += len(t.value)


    t_ignore = ' \t'


    # Error handling rule
    def t_error(self, t):
        raise SyntaxError('illegal character', (None, t.lineno, None, t.value))

