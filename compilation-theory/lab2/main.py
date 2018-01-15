import sys
import ply.lex as lex
import scanner

if __name__ == '__main__':

    filename = sys.argv[1] if len(sys.argv) > 1 else "example.txt"
    try:
        file = open(filename, "r")
    except IOError:
        print("Cannot open {0} file".format(filename))
        sys.exit(0)

    text = file.read()
    lexer = scanner.build()

    # Give the lexer some input
    lexer.input(text)

    # Tokenize
    while True:
        tok = lexer.token()
        if not tok:
            break  # No more input
        column = scanner.find_column(text, tok)
        print("(%d,%d): %s(%s)" % (tok.lineno, column, tok.type, tok.value))