#include <iostream>
#include <cmath>

using namespace std;

enum Type{
    nope,
    number,
    ADD, SUB, MUL, DIV, REM,
    lparen, rparen,
    semicolon,
    quit,
};

class Token{
    Type type;
    double value;

public:

    Token(){
        value = 0;
        type = nope;
    }

    Token(double v){
        type = number;
        value = v;
    }
    Token(Type t){
        type = t;
        value = 0;
    }

    Type getType(){
        return type;
    }

    double getValue(){
        return value;
    }
};
class Parser{
    Token token;
    bool _nextToken;

public:

    Parser(){
        _nextToken = true;
    }

    void nextToken(){
        _nextToken = true;
    }
    Token getToken(){
        if(!_nextToken)
            return token;
        _nextToken = false;
        char ch;
        while(cin >> ch){
            switch (ch){
                case ' ':
                    break;
                case 'q':
                    token = Token(quit);
                    return token;
                case '\t':
                    break;
                case ';':
                    token = Token(semicolon);
                    return token;
                case '/':
                    token = Token(DIV);
                    return token;
                case '*':
                    token = Token(MUL);
                    return token;
                case '%':
                    token = Token(REM);
                    return token;
                case '+':
                    token = Token(ADD);
                    return token;
                case '-':
                    token = Token(SUB);
                    return token;
                case '(':
                    token = Token(lparen);
                    return token;
                case ')':
                    token = Token(rparen);
                    return token;
                case '0': case '1': case '2': case '3':
                case '4': case '5': case '6': case '7':
                case '8': case '9':
                    double d;
                    cin.putback(ch);
                    cin >> d;
                    token = Token(d);
                    return token;
                default:
                    throw string("Unexpected token");
            }
        }
        throw string("Unexpected token");
    }

    double primary(){
        double v;
        getToken();

        switch (token.getType()){
            case number:
                nextToken();
                return token.getValue();
            case lparen:
                nextToken();
                v = expression();
                getToken();
                nextToken();
                if(token.getType() != rparen){
                    throw string(") expected");
                }
                return v;
            case quit:
                throw string("exit");
            default:
                throw string("Grammer error");
        }
    }

    double term(){
        double left = primary();

        double right;
        while(1) {
            getToken();
            switch (token.getType()){
                case MUL:
                    nextToken();
                    left *= term();
                    break;
                case DIV:
                    nextToken();
                    right = term();
                    if(right == 0){
                        throw string("Division error");
                    }
                    left /= right;
                    break;
                case REM:
                    nextToken();
                    right = term();
                    if(floor(left) != abs(left)){
                        throw string("Remainder floating error");
                    }else if(right == 0){
                        throw string("Remainder error");
                    }else if(floor(right) != abs(right)){
                        throw string("Remainder floating error");
                    }
                    left = (int) left % (int) right;
                    break;
                default:
                    return left;
            }
        }
    }

    double expression(){
        double left = term();
        while(1) {
            getToken();
            switch (token.getType()){
                case ADD:
                    nextToken();
                    left += term();
                    break;
                case SUB:
                    nextToken();
                    left -= term();
                    break;
                default:
                    return left;
            }
        }
    };


};

int main() {
    Parser p;
    double val;
    while(cin){
        try {
            p.nextToken();
            val = p.expression();
            cout << "=" << val << endl;
            if(p.getToken().getType() == semicolon){
                p.nextToken();
            }
        }catch(string s){
            if(s == "exit")
                return 0;
            cout << s << endl;
            Token t;
            do{
                t = p.getToken();
                p.nextToken();
            } while (t.getType() != semicolon);
        }
    }

    return 0;
}