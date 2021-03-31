#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node node;
typedef node* tree;

#define double int

struct node{
    double val;
    tree left;
    tree right;
};


//функциональная спецификация бинарного дерева
tree    create()           { return NULL; }
void    destroy(tree t)    { free(t); }
bool    is_empty(tree t)   { return t == NULL; }
double  get_root(tree t)   { return t->val; }
tree    get_left(tree t)   { return t->left; }
tree    get_right(tree t)  { return t->right; }

tree build(tree left, double val, tree right){
    tree tmp   = malloc(sizeof(node));
    tmp->left  = left;
    tmp->val   = val;
    tmp->right = right;
    return tmp;
}


//вставка в бинарное дерево поиска, используя функциональную спецификацию бинарного дерева
tree insert(tree t, double val){
    if (is_empty(t)){
        return build(create(), val, create());
    } else if (val < get_root(t)){
        tree tmp = build(insert(get_left(t), val), get_root(t), get_right(t));
        destroy(t);
        return tmp;
    } else if (val > get_root(t)){
        tree tmp = build(get_left(t), get_root(t), insert(get_right(t), val));
        destroy(t);
        return tmp;
    } else {
        return t;
    }
}


//печать бинарного дерева поиска
void print(tree t, int h){
    if (t != NULL){
        print(t->right, h + 2);
        for (int i = 0; i < h; ++i){ printf("-"); }
        printf("%d\n", t->val);
        print(t->left, h + 2);
    }
}


//удаление элемента с использованием функциональной спецификации
tree delete(tree t, double val){
    if (get_root(t) == val){
        if (get_left(t) == NULL && get_right(t) == NULL){
            destroy(t);
        } /*else if (get_left(t) == NULL || get_right(t) == NULL){
            tree tmp;
            if (get_left(t) == NULL){
                tmp = build(create(), get_root(get_right(t)), get_right(get_right(t)));
            } else {
                tmp = build(get_left(get_left(t)), get_root(get_left(t)), create());
            }
            destroy(t);
            return tmp;
        }*/
    } else if (val < get_root(t)){
        tree tmp = build(delete(get_left(t), val), get_root(t), get_right(t));
        destroy(t);
        return tmp;

    } else if (val > get_root(t)){
        tree tmp = build(get_left(t), get_root(t), delete(get_right(t), val));
        destroy(t);
        return tmp;
    }
}


int main(){

    tree t = create();

    t = insert(t, 1);
    t = insert(t, 2);
    t = insert(t, 3);
    t = insert(t, 4);
    print(t, 0);
    printf("#######################\n");
    t = delete(t, 2);
    print(t, 0);

}
