#ifndef _READ_H
#define _READ_H

#include "token.h"
#include "queue.h"

typedef enum {                  // return signals for read_token
    RT_UNEXPECTED_TOKEN = -4,   // -4 if unexpected token
    RT_INVALID_CHAR,            // -3 if invalid char
    RT_EOE,                     // -2 if end of expression
    RT_EOF,                     // -1 if end of file
    RT_SUCCESS,                 //  0 if success
} RT_SIGNAL;

typedef enum {                  // return signals for read_expression (same as RT_SIGNAL)
    READ_UNEXPECTED_TOKEN = -4,
    READ_INVALID_CHAR,
    READ_EOE,
    READ_EOF,
    READ_SUCCESS,
} READ_SIGNAL;

RT_SIGNAL read_token(token* out, token_type previous);
READ_SIGNAL read_expression(queue* result);
void print_token(token tk);

#endif
