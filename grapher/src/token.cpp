#include "../include/token.h"

lexem_t Token::getLexem() {
    return this->_lexem;
}

priority_t Token::getPriority() {
    return this->_priority;
}

std::string Token::getValue() {
    return this->_value;
}

void Token::setLexem(lexem_t lexem) {
    this->_lexem = lexem;
}

void Token::setPriority(priority_t priority) {
    this->_priority = priority;
}

void Token::setValue(std::string value) {
    this->_value = value;
}
