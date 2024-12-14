#include <stdlib.h>
#include "stack.h"

void push(Stack * stack, void * x) {
    list_insert_next(stack, list_head(stack), x);
}

void pop(Stack * stack) {
    list_remove_next(stack, list_head(stack));
}

