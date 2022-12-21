#ifndef KURSACH_TOKEN_H
#define KURSACH_TOKEN_H

#include <string>
#include <set>
#include "../include/definitions.h"

class Token {
private:
    lexem_t _lexem;
    priority_t _priority;
    std::string _value;
public:

    Token() = default;

    Token(lexem_t lexem, priority_t priority, std::string string) : _lexem(lexem), _priority(priority), _value(string) {};

    lexem_t getLexem();

    priority_t getPriority();

    std::string getValue();

    void setLexem(lexem_t lexem);

    void setPriority(priority_t priority);

    void setValue(std::string value);

};

#endif //KURSACH_TOKEN_H
