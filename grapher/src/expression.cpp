#include <utility>

#include "../include/expression.h"

Expression::Expression(std::string input, std::string variable) {
    this->setParams(std::move(input), std::move(variable));
}

void Expression::setParams(std::string input, std::string argument) {
    this->_token_manager = Token_manager(std::move(input));
    this->_operation_order = {};
    this->_argument = std::move(argument);
}

void Expression::toPolish() {
    if (_token_manager.getTokens().empty()) _token_manager.Tokenize();
    std::vector<Token> tokens = _token_manager.getTokens();
    std::stack<Token> operations = {};

    for (int i = 1; i < tokens.capacity() - 1; ++i) {
        Token cur_tok = tokens[i];

        if (cur_tok.getLexem() == L_VARIABLE) _operation_order.push_back(cur_tok);

        if (cur_tok.getLexem() == L_FUNCTION || cur_tok.getLexem() == L_BRACKET_BEGIN) operations.push(cur_tok);

        if (cur_tok.getLexem() == L_BRACKET_END) {
            while (!operations.empty() && operations.top().getLexem() != L_BRACKET_BEGIN) {
                _operation_order.push_back(operations.top());
                operations.pop();
            }
            if (!operations.empty()) operations.pop();
        }

        if (cur_tok.getLexem() == L_ADD || cur_tok.getLexem() == L_SUB || cur_tok.getLexem() == L_DIV ||
            cur_tok.getLexem() == L_MUL || cur_tok.getLexem() == L_POW) {

            while (!operations.empty() && operations.top().getPriority() >= cur_tok.getPriority() &&
                   operations.top().getLexem() != L_BRACKET_BEGIN) {
                _operation_order.push_back(operations.top());
                operations.pop();
            }
            operations.push(cur_tok);
        }
    }

    while (!operations.empty()) {
        _operation_order.push_back(operations.top());
        operations.pop();
    }

}

Value Expression::evaluate(double x) {
    if (_operation_order.empty()) toPolish();
    Value res(0, S_CORRECT);
    std::stack<Token> stack_variables = {};
    std::stack<Token> stack_operations = {};
    bool flag = true;
    for (auto item = _operation_order.begin(); item != _operation_order.end() && flag; ++item) {
        if (item->getLexem() == L_VARIABLE) stack_variables.push(*item);
        else {
            stack_operations.push(*item);
            res = performOperation(stack_variables, stack_operations, x);
            if (res.getStatus() == S_UNCORRECT) flag = false;
            stack_variables.push(Token(L_VARIABLE, P_VARIABLE, std::to_string(res.getY())));
        }
    }
    return {getValueFromStack(stack_variables, x), res.getStatus()};
}

Value Expression::performOperation(std::stack<Token> &stack_variables, std::stack<Token> &stack_operations, double x) {
    double var1 = 0;
    double var2 = 0;
    Value res(0, S_CORRECT);
    Token operation = stack_operations.top();
    stack_operations.pop();
    switch (operation.getLexem()) {
        case L_ADD:
            if (operation.getPriority() == P_FUNCTION_UNARY) {
                res.setY(getValueFromStack(stack_variables, x));
            } else {
                var2 = getValueFromStack(stack_variables, x);
                var1 = getValueFromStack(stack_variables, x);
                res.setY(var1 + var2);
            }
            break;
        case L_SUB:
            if (operation.getPriority() == P_FUNCTION_UNARY) {
                res.setY(-1 * getValueFromStack(stack_variables, x));
            } else {
                var2 = getValueFromStack(stack_variables, x);
                var1 = getValueFromStack(stack_variables, x);
                res.setY(var1 - var2);
            }
            break;
        case L_MUL:
            var2 = getValueFromStack(stack_variables, x);
            var1 = getValueFromStack(stack_variables, x);
            res.setY(var1 * var2);
            break;
        case L_DIV:
            var2 = getValueFromStack(stack_variables, x);
            if (var2 == 0) res.setStatus(S_UNCORRECT);
            else {
                var1 = getValueFromStack(stack_variables, x);
                res.setY(var1 / var2);
            }
            break;
        case L_POW:
            var2 = getValueFromStack(stack_variables, x);
            var1 = getValueFromStack(stack_variables, x);
            res.setY(pow(var1, var2));
            break;
        case L_FUNCTION:
            var2 = getValueFromStack(stack_variables, x);

            if (operation.getValue() == "sin") res.setY(sin(var2));
            if (operation.getValue() == "cos") res.setY(cos(var2));

            if (operation.getValue() == "tan") {
                if (fabs(cos(var2) - 1e6) > 0) {
                    res.setY(tan(var2));
                } else res.setStatus(S_UNCORRECT);
            }

            if (operation.getValue() == "cot") {
                if (fabs(sin(var2) - 1e6) > 0) res.setY(cos(var2) / sin(var2)); else res.setStatus(S_UNCORRECT);
            }

            if (operation.getValue() == "sqrt") {
                if (var2 >= 0) res.setY(var2); else res.setStatus(S_UNCORRECT);
            }

            if (operation.getValue() == "ln") {
                if (var2 > 0) res.setY(log(var2)); else res.setStatus(S_UNCORRECT);
            }
            break;
        default:
            break;
    }
    return res;
}

double Expression::getValueFromStack(std::stack<Token> &stack_variables, double x) {
    double val = 0;
    if (stack_variables.top().getValue() == _argument) val = x; else val = std::stod(stack_variables.top().getValue());
    stack_variables.pop();
    return val;
}

std::vector<Token> Expression::getTokens() {
    if (_token_manager.getTokens().empty()) _token_manager.Tokenize();
    return _token_manager.getTokens();
}

std::string Expression::getArgument() {
    return _argument;
}

std::string Expression::getFunName()
{
    return this->_token_manager.getString();
}

Token_manager Expression::getTokenManager() {
    return _token_manager;
}
