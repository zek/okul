
class Node(object):
    pass


class IntNum(Node):
    def __init__(self, value):
        self.value = value

class SingInstruct(Node):
    def __init__(self, value):
        self.value = value

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

class Assignment(Node):
    def __init__(self, var_name, op, expr):
        self.var_name = var_name
        self.op = op
        self.expr = expr

class Vector(Node):
    def __init__(self, values):
        self.values = values

class ForLoop(Node):
    def __init__(self, var_name, left, right, instructions):
        self.var_name = var_name
        self.left = left
        self.right = right
        self.instructions = instructions

class Matris(Node):
    def __init__(self, values):
        self.values = values

class Variable(Node):
    def __init__(self, name):
        self.name = name

class IdRef(Node):
    def __init__(self, varname, left, right = None):
        self.varname = varname
        self.left = left
        self.right = right


class BinExpr(Node):
    def __init__(self, op, left, right):
        self.op = op
        self.left = left
        self.right = right


class UnaryExpr(Node):
    def __init__(self, op, expr):
        self.op = op
        self.expr = expr

class InstructionList(Node):
    def __init__(self, instructions):
        self.instructions = instructions

class PrintExpr(Node):
    def __init__(self, arguments):
        self.arguments = arguments


class WhileLoop(Node):
    def __init__(self, condition, instructions):
        self.condition = condition
        self.instructions = instructions

class IfExpr(Node):
    def __init__(self, condition, instructions, else_instructions = None):
        self.condition = condition
        self.instructions = instructions
        self.else_instructions = else_instructions


# ...
# fill out missing classes
# ...

class Error(Node):
    def __init__(self):
        pass
