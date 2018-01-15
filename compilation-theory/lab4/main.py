import sys
import ply.yacc as yacc
from Mparser import Mparser
from TreePrinter import TreePrinter
import traceback

if __name__ == '__main__':
    filename = sys.argv[1] if len(sys.argv) > 1 else "example.txt"
    try:
        file = open(filename, "r")
    except IOError:
        print("Cannot open {0} file".format(filename))
        sys.exit(0)

    try:
        Mparser = Mparser()
        parser = yacc.yacc(module=Mparser)
        text = file.read()
        ast = parser.parse(text, lexer=Mparser.scanner)
        ast.printTree()
    except SyntaxError as e:
        print(e, 'column', e.offset, ":", e.text)
