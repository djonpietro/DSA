#include "queue.h"
#include <stdlib.h>

void enqueue(Queue *queue, void *data) {
    list_insert_next(queue, list_tail(queue), data);
}

void dequeue(Queue *queue) {
    list_remove_next(queue, list_head(queue));
}
