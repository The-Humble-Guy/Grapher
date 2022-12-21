#include "../include/syntax_checker.h"

void Syntax_checker::setRules() {
    _rules = {
            //            +        -       *      ^        /      FUN      (        )      end
            /* start*/ {B_NEXT, B_NEXT, B_NEXT, B_NEXT, B_NEXT, B_NEXT, B_NEXT, B_ERROR, B_EXIT},
            /* + */
                       {B_PREV, B_PREV, B_NEXT, B_NEXT, B_NEXT, B_NEXT, B_NEXT, B_PREV,  B_PREV},
            /* - */
                       {B_PREV, B_PREV, B_NEXT, B_NEXT, B_NEXT, B_NEXT, B_NEXT, B_PREV,  B_PREV},
            /* * */
                       {B_PREV, B_PREV, B_PREV, B_PREV, B_PREV, B_NEXT, B_NEXT, B_PREV,  B_PREV},
            /* ^ */
                       {B_PREV, B_PREV, B_PREV, B_PREV, B_PREV, B_NEXT, B_NEXT, B_PREV,  B_PREV},
            /* / */
                       {B_PREV, B_PREV, B_PREV, B_PREV, B_PREV, B_NEXT, B_NEXT, B_PREV,  B_PREV},
            /* Fun */
                       {B_PREV, B_PREV, B_PREV, B_PREV, B_PREV, B_NEXT, B_NEXT, B_PREV, B_PREV},
            /* ( */
                       {B_NEXT, B_NEXT, B_NEXT, B_NEXT, B_NEXT, B_NEXT, B_NEXT, B_EQUAL, B_ERROR},
            /* ) */
                       {B_NEXT, B_NEXT, B_NEXT, B_NEXT, B_NEXT, B_NEXT, B_NEXT, B_ERROR, B_PREV}
    };
}

action_t Syntax_checker::getCurrentAction(int state, int signal) {
    return _rules[state][signal];
}

bool Syntax_checker::isSyntaxCorrect() {
    bool flag = true;
    std::stack<Token> stack_stored = {};
    std::vector<Token> analyzed_tokens = {};
    std::vector<Token> old_tokens = _tokens.getTokens();
    std::vector<Token> tokens = {};
    for (int i = 0; i < old_tokens.capacity(); ++i) {
        if (old_tokens[i].getPriority() == P_FUNCTION_UNARY && (old_tokens[i].getLexem() == L_ADD || old_tokens[i].getLexem() == L_SUB)) {
            tokens.push_back(Token(L_VARIABLE, P_VARIABLE, "0"));
        } else {
            tokens.push_back(old_tokens[i]);
        }
    }
    std::vector<Token> temp = {};

    stack_stored.push(tokens[0]);

    action_t action = B_NEXT;

    auto token = tokens.begin() + 1;
    while ((token-1)->getLexem() != L_EXP_END) {
        while (!isKeyLexem(token->getLexem())) {
            analyzed_tokens.push_back(*token);
            ++token;
        }
        analyzed_tokens.push_back(*token);
        action =
                getCurrentAction(getStatePos(stack_stored.top().getLexem()),
                                           getActionPos((analyzed_tokens.back()).getLexem()));

        if (action == B_NEXT) {
            for (const auto& item: analyzed_tokens) {
                stack_stored.push(item);
            }
            analyzed_tokens.clear();
        }

        if (action == B_EQUAL) {
            if (analyzed_tokens.size() == 1 || stack_stored.size() == 1 ) {
                action = B_ERROR;
                break;
            }
            temp.push_back(analyzed_tokens.back());
            temp.push_back(*(analyzed_tokens.end() - 2));
            temp.push_back(stack_stored.top());

            stack_stored.pop();
            Token new_token;
            new_token.setLexem(L_VARIABLE);
            new_token.setPriority(P_VARIABLE);

            for (int i = temp.size() - 1; i >= 0; --i) {
                new_token.setValue(new_token.getValue() + temp[i].getValue());
            }
            temp.clear();
            analyzed_tokens.clear();
            analyzed_tokens.push_back(new_token);
        }

        if (action == B_PREV) {
            if (analyzed_tokens.size() == 1) {
                action = B_ERROR;
                break;
            }
            if (stack_stored.top().getLexem() == L_FUNCTION) {
                temp.push_back(stack_stored.top());
                stack_stored.pop();
            } else {
                temp.push_back(stack_stored.top());
                stack_stored.pop();
                if (stack_stored.top().getLexem() != L_VARIABLE) {
                    action = B_ERROR;
                    break;
                } else {
                    temp.push_back(stack_stored.top());
                    stack_stored.pop();
                }
            }
            temp.push_back(analyzed_tokens.front());

            Token reserved = analyzed_tokens.back();
            analyzed_tokens.clear();

            Token new_token;
            std::string str = temp[1].getValue() + temp[0].getValue() + temp[2].getValue();
            new_token.setValue(str);
            new_token.setLexem(L_VARIABLE);
            new_token.setPriority(P_VARIABLE);

            analyzed_tokens.push_back(new_token);
            temp.clear();
            --token;
        }
        if (action == B_EXIT || action == B_ERROR) break;
        ++token;
    }
    return (action == B_EXIT);
}

int Syntax_checker::getStatePos(lexem_t lexem) {
    int pos = 0;
    switch (lexem) {
        case L_EXP_BEGIN:
            pos = 0;
            break;
        case L_ADD:
            pos = 1;
            break;
        case L_SUB:
            pos = 2;
            break;
        case L_MUL:
            pos = 3;
            break;
        case L_POW:
            pos = 4;
            break;
        case L_DIV:
            pos = 5;
            break;
        case L_FUNCTION:
            pos = 6;
            break;
        case L_BRACKET_BEGIN:
            pos = 7;
            break;
        case L_BRACKET_END:
            pos = 8;
            break;
    }
    return pos;
}

int Syntax_checker::getActionPos(lexem_t lexem) {
    int pos = 0;
    switch (lexem) {
        case L_EXP_END:
            pos = 8;
            break;
        case L_ADD:
            pos = 0;
            break;
        case L_SUB:
            pos = 1;
            break;
        case L_MUL:
            pos = 2;
            break;
        case L_POW:
            pos = 3;
            break;
        case L_DIV:
            pos = 4;
            break;
        case L_FUNCTION:
            pos = 5;
            break;
        case L_BRACKET_BEGIN:
            pos = 6;
            break;
        case L_BRACKET_END:
            pos = 7;
            break;
    }
    return pos;
}

bool Syntax_checker::isKeyLexem(lexem_t lexem) {
    return (lexem != L_VARIABLE);
}
