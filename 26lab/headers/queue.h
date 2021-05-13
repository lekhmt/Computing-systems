#include <stdbool.h>

typedef struct item item;

struct item {
    double value;
    item* next;
};

typedef struct {
    item* first;
    item* last;
    int size;
} queue;

void    create(queue* q);
bool    empty(queue* q);
int     size(queue* q);
bool    push(queue* q, const double value);
double  pop(queue* q);
void    destroy(queue* q);