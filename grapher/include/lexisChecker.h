#ifndef KURSACH_LEXISCHECKER_H
#define KURSACH_LEXISCHECKER_H

#include <utility>
#include <stdexcept>

#include "expression.h"

class Lexis_checker : public Token_manager {
private:
    std::vector<Token> _tokens;
    std::string _argument;

//    bool isDouble(std::string input);
    bool isDigit(char sym);

public:
    Lexis_checker() = delete;

    Lexis_checker(Expression expression) : _tokens(expression.getTokens()), _argument(expression.getArgument()) {};

    bool isLexisCorrect();

    bool isDouble(std::string input);

};


#endif //KURSACH_LEXISCHECKER_H
