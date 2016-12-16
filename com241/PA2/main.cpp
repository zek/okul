#include <iostream>
#include <stack>
#include <fstream>
#include <ios>
#include <sstream>

using namespace std;

enum Token {
    eof, id, add, mul, lp, rp, E, T, F
};

unsigned int pos = 0, ppos = 0;

struct TokenState {
    Token token;
    int state;

    TokenState(Token token, int state) {
        this->token = token;
        this->state = state;
    }
};


stack<TokenState> ts_stack;
Token token;
std::string line;

stringstream ss;


// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

Token getToken() {
    char c;
    if (!(ss >> c)) return eof;

    if (c == 'i') {
        ss >> c;
        if (c != 'd') {
            cout << "d bekleniyordu" << endl;
            exit(0);
        }
        ppos = pos;
        pos += 2;
        return (id);
    } else if (c == '(') {
        ppos = pos;
        pos++;
        return (lp);
    } else if (c == ')') {
        ppos = pos;
        pos++;
        return (rp);
    } else if (c == '+') {
        ppos = pos;
        pos++;
        return (add);
    } else if (c == '*') {
        ppos = pos;
        pos++;
        return mul;
    } else if (isspace(c)) {
        ppos = pos;
        pos++;
        return getToken();
    } else {
        cout << "Beklenmeyen: " << c << endl;
        exit(0);
    }
}

string getTokenName(Token token) {
    switch (token) {
        case eof:
            return "$";
        case id:
            return "id";
        case add:
            return "+";
        case mul:
            return "*";
        case lp:
            return "(";
        case rp:
            return ")";
        case E:
            return "E";
        case F:
            return "F";
        case T:
            return "T";
        default:
            return "";
    }
}

int error() {
    cout << "Hata: Token(" << getTokenName(token) << ")" << endl;
    size_t i = ts_stack.size() - 1;
    for (; !ts_stack.empty(); ts_stack.pop(), i--) {
        cout << i << ": (" << ts_stack.top().state << "," << getTokenName(ts_stack.top().token) << ")" << endl;
    }
    exit(0);
}

void print_status() {
    std::stack<TokenState> st = ts_stack;
    stack<TokenState> dump;
    while (!st.empty()) {
        TokenState token = st.top();
        dump.push(token);
        st.pop();
    }
    for (; !dump.empty(); dump.pop())
        std::cout << getTokenName(dump.top().token) << dump.top().state << " ";
    cout << endl;
}

void show_input() {
    if (token == eof) {
        cout << "$";
        cout << std::string(pos - 1, ' ');
    } else {
        string _line = line.substr(ppos);
        trim(_line);
        cout << _line;
        cout << std::string(line.length() - _line.length(), ' ');
        return;
    }
}

int reduce(int rule) {
    cout << "Reduce " << rule << "\t";
    show_input();
    cout << " \t";

    int state;
    switch (rule) {
        case 1:
            if (ts_stack.top().token != T) error();
            ts_stack.pop();
            if (ts_stack.top().token != add) error();
            ts_stack.pop();
            if (ts_stack.top().token != E) error();
            ts_stack.pop();
            state = ts_stack.top().state;
            if (state == 0 || state == 1) {
                ts_stack.push(TokenState(E, 1));
            } else if (state == 4) {
                ts_stack.push(TokenState(E, 8));
            }
            break;
        case 2:
            if (ts_stack.top().token != T) error();
            ts_stack.pop();
            state = ts_stack.top().state;
            if (state == 0 || state == 1) {
                ts_stack.push(TokenState(E, 1));
            } else if (state == 4) {
                ts_stack.push(TokenState(E, 8));
            }
            break;
        case 3:
            if (ts_stack.top().token != F) error();
            ts_stack.pop();
            if (ts_stack.top().token != mul) error();
            ts_stack.pop();
            if (ts_stack.top().token != T) error();
            ts_stack.pop();
            state = ts_stack.top().state;
            if (state == 0 || state == 4) {
                ts_stack.push(TokenState(T, 2));
            } else if (state == 6) {
                ts_stack.push(TokenState(T, 9));
            }
            break;
        case 4:
            if (ts_stack.top().token != F) error();
            ts_stack.pop();
            state = ts_stack.top().state;
            if (state == 0 || state == 4) {
                ts_stack.push(TokenState(T, 2));
            } else if (state == 6) {
                ts_stack.push(TokenState(T, 9));
            }
            break;
        case 5:
            if (ts_stack.top().token != rp) error();
            ts_stack.pop();
            if (ts_stack.top().token != E) error();
            ts_stack.pop();
            if (ts_stack.top().token != lp) error();
            ts_stack.pop();
            state = ts_stack.top().state;
            if (state == 0 || state == 4 || state == 6) {
                ts_stack.push(TokenState(F, 3));
            } else if (state == 7) {
                ts_stack.push(TokenState(F, 10));
            }
            break;
        case 6:
            if (ts_stack.top().token != id) error();
            ts_stack.pop();
            state = ts_stack.top().state;
            if (state == 0 || state == 4 || state == 6) {
                ts_stack.push(TokenState(F, 3));
            } else if (state == 7) {
                ts_stack.push(TokenState(F, 10));
            }
            break;
        default:
            break;
    }
    print_status();
    return 1;
}

int shift(int state) {
    cout << "Shift " << state << " \t";
    show_input();
    cout << " \t";


    ts_stack.push(TokenState(token, state));
    token = getToken();

    print_status();

    return 1;
}


int main() {

    ss << std::cin.rdbuf();
    line = ss.str();
    ss.unsetf(ios_base::skipws);

    string line2 = line;
    trim(line2);
    cout << "\t\t" << line2 << "\t\t$0" << endl;

    ts_stack.push(TokenState(eof, 0));

    token = getToken();

    while (true) {

        switch (ts_stack.top().state) {
            case 0:
                if (token == id) {
                    shift(5);
                    continue;
                } else if (token == lp) {
                    shift(4);
                    continue;
                }
                break;
            case 1:
                if (token == add) {
                    shift(6);
                    continue;
                } else if (token == eof) {
                    cout << ("accept\t\t");
                    show_input();
                    cout << ("\t");
                    print_status();
                    exit(0);
                }
                break;
            case 2:
                if (token == add || token == lp || token == rp || token == eof) {
                    reduce(2);
                    continue;
                } else if (token == mul) {
                    shift(7);
                    continue;
                }
                break;
            case 3:
                if (token == add || token == mul || token == rp || token == eof) {
                    reduce(4);
                    continue;
                }
                break;
            case 4:
            case 6:
            case 7:
                if (token == id) {
                    shift(5);
                    continue;
                } else if (token == lp) {
                    shift(4);
                    continue;
                }
                break;
            case 5:
                if (token == add || token == mul || token == rp || token == eof) {
                    reduce(6);
                    continue;
                }
                break;
            case 8:
                if (token == add) {
                    shift(6);
                    continue;
                } else if (token == rp) {
                    shift(11);
                    continue;
                }
                break;
            case 9:
                if (token == add || token == rp || token == eof) {
                    reduce(1);
                    continue;
                } else if (token == mul) {
                    shift(7);
                    continue;
                }
                break;
            case 10:
                if (token == add || token == mul || token == rp || token == eof) {
                    reduce(3);
                    continue;
                }
                break;
            case 11:
                if (token == add || token == mul || token == rp || token == eof) {
                    reduce(5);
                    continue;
                }
                break;

            default:
                break;
        }
        error();
    }
}