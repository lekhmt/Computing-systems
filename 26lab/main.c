#include "headers/header.h"

void print_result(queue* q){
    double elem = pop(q);
    bool is_sorted = true;
    while (!empty(q)){
        double next_elem = pop(q);
        if (elem > next_elem){
            is_sorted = false;
        }
        elem = next_elem;
    }
    if (is_sorted){
        printf("Yes\n");
    } else {
        printf("No\n");
    }
}

int main(){

    queue q;
    create(&q);

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; ++i){
        double n;
        scanf("%lf", &n);
        push(&q, n);
    }

    if (size(&q) > 0){
        sort(&q);
        print_result(&q);
    } else {
        printf("Empty queue\n");
    }

}