#ifndef _HEADER_H
#define _HEADER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "read.h"
#include "queue.h"
#include "token_stack.h"
#include "tree_stack.h"
#include "token.h"
#include "tree.h"

#define create(X)                           \
    _Generic((X),                           \
    queue*:         queue_create,           \
    token_stack*:   token_stack_create,     \
    tree_stack*:    tree_stack_create       \
)(X)

#define is_empty(X)                         \
    _Generic((X),                           \
    queue*:         queue_is_empty,         \
    tree:           tree_is_empty,          \
    token_stack*:   token_stack_is_empty,   \
    tree_stack*:    tree_stack_is_empty     \
)(X)

#define size(X)                             \
    _Generic((X),                           \
    queue*:         queue_size,             \
    token_stack*:   token_stack_size,       \
    tree_stack*:    tree_stack_size         \
)(X)

#define push(X, Y)                          \
    _Generic((X),                           \
    queue*:         queue_push,             \
    token_stack*:   token_stack_push,       \
    tree_stack*:    tree_stack_push         \
)(X, Y)

#define pop(X)                              \
    _Generic((X),                           \
    queue*:         queue_pop,              \
    token_stack*:   token_stack_pop,        \
    tree_stack*:    tree_stack_pop          \
)(X)

#define destroy(X)                          \
    _Generic((X),                           \
    queue*:         queue_destroy,          \
    tree:           tree_destroy,           \
    token_stack*:   token_stack_destroy,    \
    tree_stack*:    tree_stack_destroy      \
)(X)

#define clear(X)                            \
    _Generic((X),                           \
    queue*:         queue_clear,            \
    tree:           tree_clear,             \
    token_stack*:   token_stack_clear,      \
    tree_stack*:    tree_stack_clear        \
)(X)

#define get_value(X) tree_get_value(X)
#define get_left(X) tree_get_left(X)
#define get_right(X) tree_get_right(X)
#define build(X, Y, Z) tree_build(X, Y, Z)
#define print(X, Y) tree_print(X, Y)

#endif
