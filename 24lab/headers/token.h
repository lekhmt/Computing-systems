#ifndef _TOKEN_H
#define _TOKEN_H

typedef enum {      //  types of token
    NONE = -1,      // -1 if beginning of expression
    VARIABLE,       //  0 if variable
    CONST,          //  1 if constant
    OPERATOR,       //  2 if operator
    LEFT_BRACKET,   //  3 if '('
    RIGHT_BRACKET,  //  4 if ')'
} token_type;

typedef struct {
    token_type type;
    union {
        char name[64];      // if VARIABLE
        char operator;      // if OPERATOR
        double value;       // if CONST
    } data;
} token;

#endif
