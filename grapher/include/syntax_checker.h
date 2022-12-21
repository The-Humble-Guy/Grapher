#ifndef KURSACH_SYNTAX_CHECKER_H
#define KURSACH_SYNTAX_CHECKER_H

#include "expression.h"

class Syntax_checker {
private:
    Token_manager _tokens;
    std::vector<std::vector<action_t>> _rules;

    void setRules();

    action_t getCurrentAction(int state, int signal);

    int getStatePos(lexem_t lexem);

    int getActionPos(lexem_t lexem);

    bool isKeyLexem(lexem_t lexem);

public:
    Syntax_checker() = delete;

    Syntax_checker(Expression expression) : _tokens(expression.getTokenManager()) { setRules(); };

    Syntax_checker(Token_manager manager) : _tokens(manager) { setRules(); };

    bool isSyntaxCorrect();
};

#endif //KURSACH_SYNTAX_CHECKER_H
