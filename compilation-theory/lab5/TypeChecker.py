#!/usr/bin/python
from collections import namedtuple

import AST
from SymbolTable import *


class NodeVisitor(object):
    def visit(self, node, table=None):
        method = 'visit_' + node.__class__.__name__
        visitor = getattr(self, method, self.generic_visit)
        return visitor(node, table)

    def generic_visit(self, node, table):  # Called if no explicit visitor function exists for a node.
        if isinstance(node, list):
            for elem in node:
                self.visit(elem, table)
        else:
            for child in node.children:
                if isinstance(child, list):
                    for item in child:
                        if isinstance(item, AST.Node):
                            self.visit(item, table)
                elif isinstance(child, AST.Node):
                    self.visit(child, table)


class TypeChecker(NodeVisitor):
    def __init__(self):
        self.ttype = {}
        self.ttype['+'] = {
            'int': {
                'int': 'int',
                'float': 'int'
            },
            'float': {
                'int': 'float',
                'float': 'float'
            },
            'string': {
                'string': 'string',
            },
            'matrix': {
                'matrix': 'matrix'
            }
        }
        self.ttype['-'] = {
            'int': {
                'int': 'int',
                'float': 'int'
            },
            'float': {
                'int': 'float',
                'float': 'float'
            }
        }
        self.ttype['*'] = {
            'int': {
                'int': 'int',
                'float': 'int'
            },
            'float': {
                'int': 'float',
                'float': 'float'
            }
        }
        self.ttype['/'] = {
            'int': {
                'int': 'int',
                'float': 'int'
            },
            'float': {
                'int': 'float',
                'float': 'float'
            }
        }
        self.ttype['.+'] = {
            'matrix': {
                'matrix': 'matrix'
            },
        }
        self.ttype['.-'] = {
            'matrix': {
                'matrix': 'matrix'
            },
        }
        self.ttype['.*'] = {
            'matrix': {
                'matrix': 'matrix'
            },
        }
        self.ttype['./'] = {
            'matrix': {
                'matrix': 'matrix'
            },
        }
        self.ttype['=='] = {
            'int': {
                'int': 'int',
                'float': 'int'
            },
            'float': {
                'int': 'int',
                'float': 'int'
            },
            'string': {
                'string': 'int',
            }
        }
        self.ttype['!='] = {
            'int': {
                'int': 'int',
                'float': 'int'
            },
            'float': {
                'int': 'int',
                'float': 'int'
            },
            'string': {
                'string': 'int',
            }
        }
        self.ttype['>'] = {
            'int': {
                'int': 'int',
                'float': 'int'
            },
            'float': {
                'int': 'int',
                'float': 'int'
            },
        }
        self.ttype['<'] = {
            'int': {
                'int': 'int',
                'float': 'int'
            },
            'float': {
                'int': 'int',
                'float': 'int'
            },
        }
        self.ttype['<='] = {
            'int': {
                'int': 'int',
                'float': 'int'
            },
            'float': {
                'int': 'int',
                'float': 'int'
            },
        }
        self.ttype['>='] = {
            'int': {
                'int': 'int',
                'float': 'int'
            },
            'float': {
                'int': 'int',
                'float': 'int'
            },
        }
        self.ttype['&&'] = {
            'int': {
                'int': 'int',
            }
        }
        self.ttype['||'] = {
            'int': {
                'int': 'int',
            }
        }


    def visit_Program(self, node, table):
        Type = namedtuple('Type', ['type'])
        symbolTable = SymbolTable(None, 'global')
        symbolTable.put(FunctionSymbol("zeros", "matrix", [
            Type(type="int")
        ]))
        symbolTable.put(FunctionSymbol("ones", "matrix", [
            Type(type="int")
        ]))
        symbolTable.put(FunctionSymbol("eye", "matrix", [
            Type(type="int")
        ]))
        self.visit(node.instruction_list, symbolTable)

    def visit_InstructionList(self, node, table):
        self.visit(node.instructions, table)

    def visit_FCall(self, node, table):
        symbol = table.get(node.fn_name)
        if isinstance(symbol, FunctionSymbol):
            expressions = []
            tmp = node.arg
            if tmp:
                if (tmp.arg):
                    expressions.append(tmp.arg)
                while (tmp.argList):
                    tmp = tmp.argList
                    if (tmp):
                        expressions.append(tmp.arg)
            expressions.reverse()

            expressionsTypes = [self.visit(expression, table) for expression in expressions]
            expectedExpressionsTypes = [arg.type for arg in symbol.arguments]

            if 'undefined' in expressionsTypes:
                return 'undefined'

            if len(expressionsTypes) != len(expectedExpressionsTypes):
                print('Line ' + str(node.line) + ': Wrong number of parameters, expected ' + str(
                    len(expectedExpressionsTypes)) + ', found ' + str(len(expressionsTypes)))

            for exprType, expectedType, i in zip(expressionsTypes, expectedExpressionsTypes,
                                                 range(1, len(expressionsTypes) + 1)):
                if exprType != expectedType and not (exprType == 'int' and expectedType == 'float'):
                    print('Line ' + str(
                        node.line) + ': Incorrect type of parameter, expected ' + expectedType + ", found " + exprType)
                    return 'undefined'
            return symbol.type
        else:
            print('Line ' + str(node.line) + ': ' + node.fn_name + ' is not a function or undefined')
            return 'undefined'

    def visit_BreakInst(self, node, tablet):
        scope = tablet
        while scope:
            if scope == 'global' or scope == 'function':
                break
            if scope == 'while' or scope == 'for':
                return 'break'
            scope = tablet.getParentScope()
        print('Line ' + str(node.line) + ': Invalid break. There is no iteration.')

    def visit_ContinueInst(self, node, tablet):
        scope = tablet
        while scope:
            if scope == 'global' or scope == 'function':
                break
            if scope == 'while' or scope == 'for':
                return 'continue'
            scope = tablet.getParentScope()
        print('Line ' + str(node.line) + ': Invalid continue. There is no iteration.')

    def visit_Assignment(self, node, table):
        leftType = None
        leftSymbol = table.get(node.var_name.name)
        if leftSymbol:
            leftType = leftSymbol.type
        rightType = self.visit(node.expr, table)

        if node.op == "=":
            if leftType == None:
                table.put(VariableSymbol(node.var_name.name, rightType))
            elif rightType == 'undefined':
                return
            elif not (leftType == rightType or (leftType == 'float' and rightType == 'int')):
                print('Line ' + str(node.expr.line) + ': Incorrect assignment - ' + rightType + ' to ' + leftType)
        else:
            if leftType == None:
                print('Line ' + str(node.expr.line) + ': Variable ' + node.var_name.name + ' is not declared')
            else:
                result_type = self.check_new_type(leftType, node.op[0], rightType)
                if result_type == 'undefined':
                    print('Line ' + str(
                        node.line) + ': Operator ' + node.op + ' is not allowed between ' + leftType + ' and ' + rightType)
                    return 'undefined'

    def check_new_type(self, expr1, op, expr2):
        try:
            return self.ttype[op][expr1][expr2]
        except:
            return 'undefined'

    def visit_RelExpr(self, node, table):
        return self.visit_BinExpr(node, table)

    def visit_LogExpr(self, node, table):
        return self.visit_BinExpr(node, table)

    def visit_BinExpr(self, node, table):
        type1 = self.visit(node.left, table)
        type2 = self.visit(node.right, table)

        if type1 == 'undefined' or type2 == 'undefined':
            return 'undefined'

        operator = node.op

        result_type = self.check_new_type(type1, operator, type2)
        if result_type == 'undefined':
            print('Line ' + str(
                node.line) + ': Operator ' + operator + ' is not allowed here between ' + type1 + ' and ' + type2)
            return 'undefined'

        return result_type

    def visit_IfExpr(self, node, table):
        self.visit(node.condition, table)
        if (node.instructions):
            self.visit(node.instructions, SymbolTable(table, 'if_instr1'))
        if (node.else_instructions):
            self.visit(node.else_instructions, SymbolTable(table, 'if_instr2'))

    def visit_WhileLoop(self, node, table):
        self.visit(node.condition, table)
        if (node.instructions):
            self.visit(node.instructions, SymbolTable(table, 'while'))

    def visit_ForLoop(self, node, table):
        ltype = self.visit(node.left, table)
        self.visit(node.right, table)

        if (node.instructions):
            table = SymbolTable(table, 'for')
            table.put(VariableSymbol(node.var_name.name, ltype))
            self.visit(node.instructions, table)

    def visit_UnaryExpr(self, node, table):
        type = self.visit(node.expr, table)
        if node.op == 'UMINUS' and type in ["int", "float"]:
            return type
        if node.op == 'TRANSPOSE' and type.split("_")[0] == "matrix":
            return type
        print('Line ' + str(node.line) + ': ' + node.op + ' is not valid for ' + type)

    def visit_FloatNum(self, node, table):
        return 'float'

    def visit_Matris(self, node, table):
        if (node.values.__len__() == 0):
            return 'matrix_0x0'
        c = self.visit(node.values[0], table)
        for n in node.values[1:]:
            t = self.visit(n, table)
            if (c != t):
                print('Line ' + str(n.line) + ': ' + t + ' is not valid!')
                return 'undefined'
        return 'matrix_' + node.values.__len__().__str__() + "x" + c.split("_")[1]

    def visit_Vector(self, node, table):
        return 'vector_' + node.values.__len__().__str__()

    def visit_IntNum(self, node, table):
        return 'int'

    def visit_String(self, node, table):
        return 'string'

    def visit_Variable(self, node, table):
        symbol = table.get(node.name)
        if isinstance(symbol, VariableSymbol):
            return symbol.type
        elif isinstance(symbol, FunctionSymbol):
            print('Line ' + str(node.line) + ': ' + node.name + ' is a function expected a variable ')
            return 'undefined'
        else:
            print('Line ' + str(node.line) + ': ' + node.name + ' is not declared ')
            return 'undefined'
