#include "headers/header.h"

const char operators[] = {'-', '+', '*', '/', '(', ')'};

typedef enum {                  // return signals for read_token
    RT_UNEXPECTED_TOKEN = -4,   // -4 if unexpected token
    RT_INVALID_CHAR,            // -3 if invalid char
    RT_EOE,                     // -2 if end of expression
    RT_EOF,                     // -1 if end of file
    RT_SUCCESS,                 //  0 if success
} RT_SIGNAL;

RT_SIGNAL read_token(token *out, token_type previous){

    int c = getchar();
    while (c == ' ' || c == '\t'){
        c = getchar();
    }

    // RT_UNEXPECTED_TOKEN

    // RT_INVALID_CHAR

    // RT_EOE
    if (c == '\n'){
        return RT_EOE;
    }

    // RT_EOF
    if (c == EOF){
        return RT_EOF;
    }

    // RT_SUCCESS

}

bool read_expression(queue* q){

    token tk;
    RT_SIGNAL response = read_token(&tk, NONE);

    do {
        // push tk to q
    } while ((response = read_token(&tk, tk.type)) == RT_SUCCESS);

    if (response == RT_UNEXPECTED_TOKEN || response == RT_INVALID_CHAR){
        return false;
    }
    if (response == RT_EOF || response == RT_EOE) {
        return true;
    }

}

int main(){



}