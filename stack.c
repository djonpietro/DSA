#include <stdlib.h>
#include "stack.h"

void push(Stack * stack, void * x) {
    list_insert_next(stack, NULL, x);
}

void pop(Stack * stack) {
    list_remove_next(stack, NULL);
}

