#include "lexisChecker.h"

bool Lexis_checker::isLexisCorrect() {
    bool correct = true;
    for (size_t i = 0; (i < _tokens.capacity() - 1) && correct; ++i) {
        if (_tokens.at(i).getLexem() == L_VARIABLE) {
            if (!(_tokens.at(i).getValue() == _argument || isDouble(_tokens.at(i).getValue()))) correct = false;
        }
        if (_tokens.at(i).getLexem() == L_FUNCTION && _tokens.at(i + 1).getLexem() != L_BRACKET_BEGIN) correct = false;
    }
    return correct;
}

bool Lexis_checker::isDouble(std::string input) {
    bool flag = true;
    int count_commas = 0;
    int count_pos_neg = 0;
        for (size_t i = 0; i < input.length() && flag; ++i) {
            if (!isDigit(input[i])) {
                if (input[i] == ',') ++count_commas;
                else if (input[i] == '+' || input[i] == '-') ++count_pos_neg;
                else flag = false;
            }
    }
    return flag && (count_commas <= 1) && (count_pos_neg <= 1);
}

bool Lexis_checker::isDigit(char sym)
{
    bool flag = true;
    switch (sym) {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '0':
    case '\0':
        break;
    default:
        flag = false;
        break;
    }
    return flag;
}
