#!/usr/bin/python


class Symbol:
    def __init__(self, name, type):
        self.name = name
        self.type = type


class VariableSymbol(Symbol):
    pass

class FunctionSymbol(Symbol):
    def __init__(self, name, type, arguments):
        self.name = name
        self.type = type
        self.arguments = arguments

class SymbolTable(object):

    def __init__(self, parent, name): # symbol table name
        self.symbols = {}
        self.name = name
        self.parent = parent

    def put(self, symbol): # put variable symbol or fundef under <name> entry
        if self.symbols.__contains__(symbol.name):
            return False
        else:
            self.symbols[symbol.name]= symbol
            return True

    def get(self, name): # get variable symbol or fundef from <name> entry
        if self.symbols.__contains__(name):
            return self.symbols[name]
        elif self.parent:
            return self.parent.get(name)
        else:
            return None


    def getParentScope(self):
        return self.parent
