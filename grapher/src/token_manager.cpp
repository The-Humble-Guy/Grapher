// Token manager implements container logic under stream of _tokens
// this tok
#include <utility>
#include "../include/token_manager.h"

Token_manager::Token_manager(std::string input) : _input_string(std::move(input)), _tokens({}) {}

std::string Token_manager::getString() {
    return this->_input_string;
}

void Token_manager::Tokenize() {
    eraseSpaces();

    Token *token = nullptr;
    Token start(L_EXP_BEGIN, P_START_END, "");
    _tokens.push_back(start);

    size_t pos = 0;
    while (pos < _input_string.length()) {
        token = getToken(pos);
        _tokens.push_back(*token);
        pos += token->getValue().length();
        delete token;
    }

    Token end(L_EXP_END, P_START_END, "");
    _tokens.push_back(end);

    correctLexems();
    correctUnary();
}

void Token_manager::eraseSpaces() {
    std::string new_string = {};
    if (!this->_input_string.empty()) {
        for (char i: this->_input_string) {
            if (i != ' ') {
                new_string.push_back(i);
            }
        }
    }
    new_string.shrink_to_fit();
    this->_input_string = new_string;
}

Token *Token_manager::getToken(size_t from) {
    Token *token = new Token;
    Token_checker checker;
    std::string str = {};

    size_t pos = from;
    if (pos < _input_string.length()) {
        str.push_back(_input_string.at(pos));
        if (!checker.isStaff(_input_string.substr(pos, 1))) {
            while (pos + 1 < _input_string.length() && !checker.isStaff(_input_string.substr(pos + 1, 1))) {
                str.push_back(_input_string.at(pos + 1));
                ++pos;
            }
        }

        switch (str.at(0)) {
            case '+':
                token->setLexem(L_ADD);
                token->setPriority(P_ADD_SUB);
                break;
            case '-':
                token->setLexem(L_SUB);
                token->setPriority(P_ADD_SUB);
                break;
            case '*':
                token->setLexem(L_MUL);
                token->setPriority(P_MUL_DIV_POW);
                break;
            case '/':
                token->setLexem(L_DIV);
                token->setPriority(P_MUL_DIV_POW);
                break;
            case '^':
                token->setLexem(L_POW);
                token->setPriority(P_MUL_DIV_POW);
                break;
            case '(':
                token->setLexem(L_BRACKET_BEGIN);
                token->setPriority(P_BRACKET);
                break;
            case ')':
                token->setLexem(L_BRACKET_END);
                token->setPriority(P_BRACKET);
                break;
            default:
                token->setLexem(L_VARIABLE);
                token->setPriority(P_VARIABLE);
                break;
        }

    }
    token->setValue(str);

    return token;
}

void Token_manager::correctVariable(Token &token) {
    Token_checker checker;
    if (checker.isFunction(token.getValue())) {
        token.setLexem(L_FUNCTION);
        token.setPriority(P_FUNCTION_UNARY);
    }
}

void Token_manager::correctLexems() {
    for (int i = 0; i < _tokens.capacity(); ++i) {
        if (_tokens[i].getLexem() == L_VARIABLE)
            correctVariable(_tokens[i]);
    }
}

void Token_manager::correctUnary() {
    for (int i = 1; i < _tokens.capacity(); ++i) {
        if (_tokens[i].getLexem() == L_SUB || _tokens[i].getLexem() == L_ADD) {
            if (_tokens[i - 1].getLexem() == L_BRACKET_BEGIN || _tokens[i - 1].getLexem() == L_EXP_BEGIN) {
                _tokens[i].setPriority(P_FUNCTION_UNARY);
            }
        }
    }
}

std::vector<Token> Token_manager::getTokens() {
    if (_tokens.empty()) Tokenize();
    return this->_tokens;
}

bool Token_manager::Token_checker::isStaff(const std::string &str) {
    bool result = true;
    std::set<std::string> staff_characters = {"+", "^", "-", "*", "/", "(", ")"};
    if (staff_characters.find(str) == staff_characters.end()) result = false;
    return result;
}

bool Token_manager::Token_checker::isFunction(const std::string &str) {
    bool result = true;
    std::set<std::string> functions = {"sin", "cos", "tan", "cot", "atan", "acot", "asin", "acos", "ln", "lg", "log",
                                       "sqrt", "pow"};
    if (functions.find(str) == functions.end()) result = false;
    return result;
}

bool Token_manager::Token_checker::isVariable(const std::string &str) {
    return !(isFunction(str) || isStaff(str));
}
