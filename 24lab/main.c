#include "headers/header.h"

void print_error(char* s){
    fprintf(stderr, "\033[31;3mError\033[0m: %s\n", s);
}

void print_note(char* s){
    printf("\033[33;3mNote\033[0m: %s\n", s);
}

int priority(token t){
    if (t.data.operator == '+' || t.data.operator == '-'){
        return 0;
    }
    if (t.data.operator == '*' || t.data.operator == '/'){
        return 1;
    }
    if (t.data.operator == '^'){
        return 2;
    }
    if (t.data.operator == '~'){
        return 3;
    }
    return -1;
}

bool left_associative(token t){
    return !(t.data.operator == '~' || t.data.operator == '^');
}

void print_expression(tree t){

};

int main(){

    queue expression; create(&expression);
    READ_SIGNAL response;
    do {
        response = read_expression(&expression);
        if (response != READ_SUCCESS && response != READ_EOE && response != READ_EOF){
            print_error("unexpected error");
            continue;
        }
    } while (response != READ_SUCCESS && response != READ_EOE && response != READ_EOF);

    if (is_empty(&expression)){
        print_note("empty expression");
    }

    queue result;     create(&result);
    token_stack sort; create(&sort);
    tree_stack treeStack; create(&treeStack);

    do {

        if (response == READ_UNEXPECTED_TOKEN){
            print_error("unexpected token");
            continue;
        } else if (response == READ_INVALID_CHAR){
            print_error("invalid char");
            continue;
        }

        bool error = false;

        while (!is_empty(&expression)){

            if (error){
                print_error("unexpected error");
                break;
            }

            token t = pop(&expression);
            if (t.type == VARIABLE || t.type == CONST){
                push(&result, t);
                continue;
            }
            if (t.type == LEFT_BRACKET){
                push(&sort, t);
                continue;
            }
            if (t.type == RIGHT_BRACKET){
                if (is_empty(&sort)){
                    error = true;
                } else {
                    token tmp = pop(&sort);
                    while (tmp.type != LEFT_BRACKET){
                        push(&result, tmp);
                        tmp = pop(&sort);
                        if (is_empty(&result) && tmp.type != LEFT_BRACKET){
                            error = true;
                        }
                    }
                }
                continue;
            }
            if (t.type == NONE){
                print_error("unexpected error");
                continue;
            }
            if (t.type == OPERATOR){
                if (is_empty(&sort)){
                    push(&sort, t);
                    continue;
                }
                token operator = pop(&sort);
                if (priority(t) > priority(operator) || operator.type == LEFT_BRACKET){
                    push(&sort, operator);
                } else if (priority(t) < priority(operator)){
                    push(&result, operator);
                } else {
                    if (left_associative(t)){
                        push(&result, operator);
                    } else {
                        push(&sort, operator);
                    }
                }
                push(&sort, t);
                continue;
            }
        }

        while (!is_empty(&sort)){
            push(&result, pop(&sort));
        }

        // построение дерева
        if (is_empty(&result)){
            continue;
        } else if (error){
            print_error("unexpected error");
            continue;
        }

        token tmp = pop(&result);
        push(&treeStack, build(tree_create(), tmp, tree_create()));
        while (!is_empty(&result)){
            tmp = pop(&result);
            if (tmp.type == CONST || tmp.type == VARIABLE){
                push(&treeStack, build(tree_create(), tmp, tree_create()));
            } else {
                if (tmp.data.operator == '~'){
                    if (is_empty(&treeStack)){
                        error = true;
                        continue;
                    }
                    tree left = pop(&treeStack);
                    push(&treeStack, build(left, tmp, tree_create()));
                } else {
                    if (size(&treeStack) < 2){
                        error = true;
                        continue;
                    }
                    tree right = pop(&treeStack);
                    tree left = pop(&treeStack);
                    push(&treeStack, build(left, tmp, right));
                }
            }
        }

        if (size(&treeStack) != 1 || error){
            print_error("unexpected error");
            continue;
        }

        tree treeExpression = pop(&treeStack);
        print(treeExpression, 0);
        print_expression(treeExpression);

        clear(&result);
        clear(&sort);
        clear(&treeStack);
        clear(treeExpression);

    } while ((response = read_expression(&expression)) != READ_EOF);

    destroy(&result);
    destroy(&sort);
    destroy(&treeStack);
    destroy(&expression);

}