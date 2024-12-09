#include "queue.h"
#include <stdlib.h>

void enqueue(Queue *queue, void *data) {
    list_insert_next(queue, NULL, data);
}

void dequeue(Queue *queue) {
    list_remove_next(queue, list_tail(queue));
}
