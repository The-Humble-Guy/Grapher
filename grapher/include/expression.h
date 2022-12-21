#ifndef KURSACH_EXPRESSION_H
#define KURSACH_EXPRESSION_H

#include <stack>
#include <list>
#include <cmath>
#include <utility>
#include "value.h"
#include "token_manager.h"

class Expression {
private:
    std::string _argument;
    Token_manager _token_manager;
    std::list<Token> _operation_order;

    void toPolish();

    double getValueFromStack(std::stack<Token> &stack_variables, double x);

    Value performOperation(std::stack<Token> &stack_variables, std::stack<Token> &stack_operations, double x);

public:
    Expression() = delete;

    explicit Expression(Token_manager token_manager) : _token_manager(std::move(token_manager)) {};

    Expression(std::string input, std::string variable);

    void setParams(std::string input, std::string argument);

    std::vector<Token> getTokens();

    std::string getArgument();

    std::string getFunName();

    Token_manager getTokenManager();

    Value evaluate(double x);
};

#endif //KURSACH_EXPRESSION_H
