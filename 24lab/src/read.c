#include "../headers/header.h"

const char OPERATORS[] = {'^', '*', '/', '+'};
const int OPERATORS_COUNTER = 4;

void print_error(char* s);
void print_note(char* s);

RT_SIGNAL read_token(token *out, token_type previous){

    int c = getchar();
    while (c == ' ' || c == '\t'){
        c = getchar();
    }

    // RT_EOE
    if (c == '\n'){
        c = getchar();
        if (c == EOF) {
            return RT_EOF;
        } else {
            ungetc(c, stdin);
            return RT_EOE;
        }
    }

    // RT_EOF
    if (c == EOF){
        return RT_EOF;
    }

    // RT_INVALID_CHAR
    bool is_operator = false;
    for (int i = 0; i < OPERATORS_COUNTER; ++i){
        if (OPERATORS[i] == c){
            is_operator = true;
        }
    }
    if (!is_operator){
        if (!(c >= '0' && c <= '9') && !((c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z'))
            && !(c == '-' || c == '(' || c == ')')){
            return RT_INVALID_CHAR;
        }
    }

    // RT_SUCCESS
    if (c == '-'){
        out->type = OPERATOR;
        if (previous == OPERATOR || previous == LEFT_BRACKET || previous == NONE){
            out->data.operator = '~';
        } else {
            out->data.operator = '-';
        }
    } else if (is_operator){
        out->type = OPERATOR;
        out->data.operator = (char) c;
    }

    if (c == '('){
        out->type = LEFT_BRACKET;
    } else if (c == ')'){
        out->type = RIGHT_BRACKET;
    }

    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
        out->type = VARIABLE;
        out->data.name[0] = (char) c;
        int i = 1;
        while (i < 63){
            c = getchar();
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' ||
                (c >= '0' && c <= '9') ){
                out->data.name[i] = (char) c;
                ++i;
            } else if (c == EOF){
                out->data.name[i] = '\0';
                ungetc(c, stdin);
                break;
            } else if (c == '\n'){
                out->data.name[i] = '\0';
                ungetc(c, stdin);
                break;
            } else {
                out->data.name[i] = '\0';
                ungetc(c, stdin);
                break;
            }
        }
    } else if (c >= '0' && c <= '9'){
        ungetc(c, stdin);
        double result;
        scanf("%lf", &result);
        out->type = CONST;
        out->data.value = result;
    }

    // RT_UNEXPECTED_TOKEN
    if (previous == VARIABLE && out->type == VARIABLE){
        return RT_UNEXPECTED_TOKEN;
    }
    if (previous == OPERATOR && out->type == OPERATOR && out->data.operator != '~'){
        return RT_UNEXPECTED_TOKEN;
    }
    if (previous == CONST && out->type == CONST){
        return RT_UNEXPECTED_TOKEN;
    }

    return RT_SUCCESS;

}

READ_SIGNAL read_expression(queue* result){

    if (!is_empty(result)){
        clear(result);
    }

    token tk;
    RT_SIGNAL response = read_token(&tk, NONE);
    bool success = true;
    if (response == RT_UNEXPECTED_TOKEN || response == RT_INVALID_CHAR){
        success = false;
    }

    if (response == RT_EOE && success){
        return READ_EOE;
    }
    if (response == RT_EOF && success){
        return READ_EOF;
    }
    if (!success){
        return READ_ERROR;
    }

    do {
        push(result, tk);
    } while ((response = read_token(&tk, tk.type)) == RT_SUCCESS);

    if (response == RT_UNEXPECTED_TOKEN){
        return READ_ERROR;
    }

    if (response == RT_INVALID_CHAR){
        return READ_ERROR;
    }

    if (response == RT_EOE){
        return READ_EOE;
    }

    if (response == RT_EOF){
        return READ_EOF;
    }

    return READ_SUCCESS;

}

void print_token(token tk){
    if (tk.type == LEFT_BRACKET){
        printf("(");
    } else if (tk.type == RIGHT_BRACKET){
        printf(")");
    }
    if (tk.type == VARIABLE){
        printf("%s", tk.data.name);
    }
    if (tk.type == CONST){
        printf("%.0lf", tk.data.value);
    }
    if (tk.type == OPERATOR){
        printf("%c", tk.data.operator);
    }
}

