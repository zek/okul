class Node(object):
    pass


class Program(Node):
    def __init__(self, instruction_list):
        self.instruction_list = instruction_list


class IntNum(Node):
    def __init__(self, value):
        self.value = value


class BreakInst(Node):
    def __init__(self):
        self.children = ()

class ContinueInst(Node):
    def __init__(self):
        self.children = ()

class ReturnInst(Node):
    def __init__(self, expr = None):
        self.expr = expr
        if(self.expr):
            self.children = (expr,)
        else:
            self.children = ()


class String(Node):
    def __init__(self, value):
        self.value = value


class FloatNum(Node):
    def __init__(self, value):
        self.value = value


class FCall(Node):
    def __init__(self, fn_name, arg):
        self.fn_name = fn_name
        self.arg = arg
        self.children = (arg,)


class ArgumentList(Node):
    def __init__(self, argList, arg):
        self.argList = argList
        self.arg = arg
        self.children = (argList, arg)

class Assignment(Node):
    def __init__(self, var_name, op, expr):
        self.var_name = var_name
        self.op = op
        self.expr = expr
        self.children = (expr,)


class Vector(Node):
    def __init__(self, values):
        self.values = values
        self.children = (values,)


class ForLoop(Node):
    def __init__(self, var_name, left, right, instructions):
        self.var_name = var_name
        self.left = left
        self.right = right
        self.instructions = instructions
        self.children = (left, right, instructions)


class Matris(Node):
    def __init__(self, values):
        self.values = values
        self.children = (values,)


class Variable(Node):
    def __init__(self, name):
        self.name = name
        self.children = ()


class IdRef(Node):
    def __init__(self, name, left, right=None):
        self.name = name
        self.left = left
        self.right = right
        self.children = (left, right)


class BinExpr(Node):
    def __init__(self, op, left, right):
        self.op = op
        self.left = left
        self.right = right
        self.children = (left, right)


class RelExpr(Node):
    def __init__(self, op, left, right):
        self.op = op
        self.left = left
        self.right = right
        self.children = (left, right)

class LogExpr(Node):
    def __init__(self, op, left, right):
        self.op = op
        self.left = left
        self.right = right
        self.children = (left, right)


class UnaryExpr(Node):
    def __init__(self, op, expr):
        self.op = op
        self.expr = expr
        self.children = (expr,)


class InstructionList(Node):
    def __init__(self, instructions):
        self.instructions = instructions
        self.children = (instructions)


class PrintExpr(Node):
    def __init__(self, arguments):
        self.arguments = arguments
        self.children = (arguments,)


class WhileLoop(Node):
    def __init__(self, condition, instructions):
        self.condition = condition
        self.instructions = instructions
        self.children = (condition, instructions)


class IfExpr(Node):
    def __init__(self, condition, instructions, else_instructions=None):
        self.condition = condition
        self.instructions = instructions
        self.else_instructions = else_instructions
        self.children = (condition, instructions, else_instructions)

class Empty(Node):
    def __init__(self):
        self.name = ""
        self.children = ( )


# ...
# fill out missing classes
# ...

class Error(Node):
    def __init__(self):
        pass
