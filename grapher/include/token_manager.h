#ifndef KURSACH_TOKEN_MANAGER_H
#define KURSACH_TOKEN_MANAGER_H

#include <string>
#include <vector>
#include "definitions.h"
#include "token.h"


class Token_manager {
public:
    class Token_checker {
    public:
        Token_checker() = default;

        bool isStaff(const std::string &str);

        bool isFunction(const std::string &str);

        bool isVariable(const std::string &str);
    };
private:

    std::string _input_string;
    std::vector<Token> _tokens;

    void eraseSpaces();

    void correctLexems();

    void correctVariable(Token &token);

    void correctUnary();

    Token *getToken(size_t from);


public:
    Token_manager() = default;

    explicit Token_manager(std::string input);

    void Tokenize();

    std::vector<Token> getTokens();

    std::string getString();
};


#endif //KURSACH_TOKEN_MANAGER_H
