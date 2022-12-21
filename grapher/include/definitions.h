#ifndef KURSACH_DEFINITIONS_H
#define KURSACH_DEFINITIONS_H

typedef enum {
    L_EXP_BEGIN,
    L_EXP_END,
    L_BRACKET_BEGIN,
    L_BRACKET_END,
    L_VARIABLE,
    L_ADD,
    L_SUB,
    L_MUL,
    L_DIV,
    L_POW,
    L_FUNCTION
} lexem_t;

typedef enum {
    P_START_END,
    P_VARIABLE,
    P_ADD_SUB,
    P_MUL_DIV_POW,
    P_FUNCTION_UNARY,
    P_BRACKET,
} priority_t;

typedef enum {
    S_CORRECT,
    S_UNCORRECT,
} status_t;

typedef enum {
    B_NEXT,
    B_PREV,
    B_EQUAL,
    B_ERROR,
    B_EXIT,
} action_t;

#endif //KURSACH_DEFINITIONS_H
