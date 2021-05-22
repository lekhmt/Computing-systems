#include "../headers/header.h"

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
    if (t == NULL){
        return;
    }
    tree left  = get_left(t);
    tree right = get_right(t);
    token tk = get_value(t);

    if (tk.type == OPERATOR && tk.data.operator == '~'){
        printf("(-");
        print_token(get_value(left));
        printf(")");
    } else if (tk.type == OPERATOR && tk.data.operator == '/'){
        print_expression(left);
        print_token(tk);
        printf("(");
        print_expression(right);
        printf(")");
    } else {
        if (!is_empty(left)) {
            token left_tk  = get_value(left);
            if (tk.type == OPERATOR && left_tk.type == OPERATOR && priority(tk) > priority(left_tk)) {
                printf("(");
                print_expression(left);
                printf(")");
            } else {
                print_expression(left);
            }
        }
        print_token(tk);
        if (!is_empty(right)){
            token right_tk = get_value(right);
            if (tk.type == OPERATOR && right_tk.type == OPERATOR && priority(tk) > priority(right_tk)){
                printf("(");
                print_expression(right);
                printf(")");
            } else {
                print_expression(right);
            }
        }
    }

};

bool is_integer(double a){
    return (double)(int) a == a;
}

tree get_power(tree t, double power){
    tree tmp = get_left(t);
    if (power == 0){
        token tk;
        tk.type = CONST;
        tk.data.value = 1;
        tmp = build(tree_create(), tk, tree_create());
    }
    for (int i = 1; i < fabs(power); ++i){
        token tk;
        tk.type = OPERATOR;
        tk.data.operator = '*';
        tmp = build(tmp, tk, copy(get_left(t)));
    }
    if (power > 0){
        return tmp;
    } else if (power < 0){
        token tk1;
        tk1.type = OPERATOR;
        tk1.data.operator = '/';
        token tk2;
        tk2.type = CONST;
        tk2.data.value = 1;
        return build(build(tree_create(), tk2, tree_create()), tk1, tmp);
    }
}

tree change_tree(tree t){

    tree left = get_left(t);
    tree right = get_right(t);

    if (!is_empty(left)){
        left = change_tree(left);
    }

    if (get_value(t).type == OPERATOR && get_value(t).data.operator == '^'){
        if (get_value(right).type == CONST && is_integer(get_value(right).data.value)){
            double power = get_value(right).data.value;
            tree tmp = get_power(t, power);
            return tmp;
        } else if (get_value(right).type == OPERATOR && get_value(right).data.operator == '~'
                   && is_integer(get_value(get_left(right)).data.value)){
            double power = - get_value(get_left(right)).data.value;
            tree tmp = get_power(t, power);
            return tmp;
        }
    }

    if (!is_empty(right)){
        right = change_tree(right);
    }

    return build(left, get_value(t), right);

}

int main(){

    int expression_counter = 1;
    queue expression; create(&expression);
    queue result;     create(&result);
    token_stack sort; create(&sort);
    tree_stack treeStack; create(&treeStack);

    READ_SIGNAL response;

    do {

        clear(&result);
        clear(&sort);
        clear(&treeStack);

        do {
            response = read_expression(&expression);
            if (!is_empty(&expression)){
                printf("Expression №%d\n", expression_counter);
                ++expression_counter;
            }
            if (response != READ_SUCCESS && response != READ_EOE && response != READ_EOF){
                print_error("unexpected error");
                continue;
            }
        } while (response != READ_SUCCESS && response != READ_EOE && response != READ_EOF);


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
                    while (tmp.type != LEFT_BRACKET && !is_empty(&sort)){
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

        if (error){
            print_error("unexpected error");
            continue;
        }

        while (!is_empty(&sort)){
            push(&result, pop(&sort));
        }

        if (is_empty(&result)){
            continue;
        }

        // построение дерева
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
        print_expression(treeExpression); printf("\n");
        printf("--------------------------------------------------------\n");
        print(treeExpression, 0);
        printf("--------------------------------------------------------\n");
        treeExpression = change_tree(treeExpression);
        print_expression(treeExpression); printf("\n");
        printf("========================================================\n");

    } while (response != READ_EOF);

    destroy(&result);
    destroy(&sort);
    destroy(&treeStack);
    destroy(&expression);

}