from __future__ import print_function
import AST


def addToClass(cls):
    def decorator(func):
        setattr(cls, func.__name__, func)
        return func

    return decorator


filler = '|  '


def indented(k):
    print(k * filler, end='')


class TreePrinter:
    @addToClass(AST.InstructionList)
    def printTree(self, indent=0):
        for instr in self.instructions:
            instr.printTree(indent)

    @addToClass(AST.Program)
    def printTree(self, indent=0):
        self.instruction_list.printTree(indent)

    @addToClass(AST.PrintExpr)
    def printTree(self, indent=0):
        indented(indent)
        print("PRINT")
        self.arguments.printTree(indent + 1)

    @addToClass(AST.ArgumentList)
    def printTree(self, indent=0):
        if (self.arg):
            self.arg.printTree(indent)
        if (self.argList):
            self.argList.printTree(indent)

    @addToClass(AST.ForLoop)
    def printTree(self, indent=0):
        indented(indent)
        print("FOR")
        self.var_name.printTree(indent + 1)
        indented(indent + 1)
        print("RANGE")
        self.left.printTree(indent + 2)
        self.right.printTree(indent + 2)
        self.instructions.printTree(indent + 1)

    @addToClass(AST.Node)
    def printTree(self, indent=0):
        raise Exception("printTree not defined in class " + self.__class__.__name__)

    @addToClass(AST.Assignment)
    def printTree(self, indent=0):
        indented(indent)
        print(self.op)
        self.var_name.printTree(indent + 1)
        self.expr.printTree(indent + 1)

    @addToClass(AST.Variable)
    def printTree(self, indent=0):
        indented(indent)
        print(self.name)

    @addToClass(AST.FCall)
    def printTree(self, indent=0):
        indented(indent)
        print(self.fn_name)
        self.arg.printTree(indent + 1)

    @addToClass(AST.IntNum)
    def printTree(self, indent=0):
        indented(indent)
        print(self.value)

    @addToClass(AST.FloatNum)
    def printTree(self, indent=0):
        indented(indent)
        print(self.value)

    @addToClass(AST.ReturnInst)
    def printTree(self, indent=0):
        indented(indent)
        print("RETURN")
        if (self.expr):
            self.expr.printTree(indent + 1)

    @addToClass(AST.BreakInst)
    def printTree(self, indent=0):
        indented(indent)
        print("BREAK")

    @addToClass(AST.ContinueInst)
    def printTree(self, indent=0):
        indented(indent)
        print("CONTINUE")

    @addToClass(AST.String)
    def printTree(self, indent=0):
        indented(indent)
        print(self.value)

    @addToClass(AST.IdRef)
    def printTree(self, indent=0):
        indented(indent)
        print("REF")
        self.name.printTree(indent + 1)
        self.left.printTree(indent + 1)
        if self.right:
            self.right.printTree(indent + 1)

    @addToClass(AST.Matris)
    def printTree(self, indent=0):
        indented(indent)
        print("MATRIX")
        for v in self.values:
            v.printTree(indent + 1)

    @addToClass(AST.Empty)
    def printTree(self, indent=0):
        pass

    @addToClass(AST.Vector)
    def printTree(self, indent=0):
        indented(indent)
        print("VECTOR")
        for v in self.values:
            v.printTree(indent + 1)

    @addToClass(AST.BinExpr)
    def printTree(self, indent=0):
        indented(indent)
        print(self.op)
        self.left.printTree(indent + 1)
        self.right.printTree(indent + 1)

    @addToClass(AST.RelExpr)
    def printTree(self, indent=0):
        indented(indent)
        print(self.op)
        self.left.printTree(indent + 1)
        self.right.printTree(indent + 1)

    @addToClass(AST.LogExpr)
    def printTree(self, indent=0):
        indented(indent)
        print(self.op)
        self.left.printTree(indent + 1)
        self.right.printTree(indent + 1)

    @addToClass(AST.UnaryExpr)
    def printTree(self, indent=0):
        indented(indent)
        print(self.op)
        self.expr.printTree(indent + 1)

    @addToClass(AST.WhileLoop)
    def printTree(self, indent=0):
        indented(indent)
        print("WHILE")
        self.condition.printTree(indent + 1)
        self.instructions.printTree(indent + 1)

    @addToClass(AST.IfExpr)
    def printTree(self, indent=0):
        indented(indent)
        print("IF")
        self.condition.printTree(indent + 1)
        indented(indent)
        print("THEN")
        self.instructions.printTree(indent + 1)
        if self.else_instructions:
            indented(indent)
            print("ELSE")
            self.else_instructions.printTree(indent + 1)

    @addToClass(AST.Error)
    def printTree(self, indent=0):
        pass
        # fill in the body


        # define printTree for other classes
        # ...
