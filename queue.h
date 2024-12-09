#ifndef QUEUE_H
#define QUEUE_H

#include "linked_list.h"

/**
 * @brief A queue node.
 * 
 * This defines a queue node by aliasing it to the ListNode type from the linked_list module.
 */
typedef ListNode QueueNode;

/**
 * @brief A queue implemented using a linked list.
 * 
 * This defines the Queue type by aliasing it to the List type from the linked_list module.
 * It allows the linked list's structure and functions to be reused for managing queues.
 */
typedef List Queue;

/**
 * @brief Initializes a queue.
 * 
 * Alias for the `list_init` function, which initializes an empty queue by reusing the 
 * linked list initialization function.
 */
#define queue_init list_init

/**
 * @brief Terminates a queue.
 * 
 * Alias for the `list_terminate` function, which cleans up all resources used by the queue
 * by reusing the linked list termination function.
 */
#define queue_terminate list_terminate

/**
 * @brief Retrieves the front element of the queue.
 * 
 * Alias for the `list_tail` function, which provides access to the first element of the queue 
 * without removing it.
 * 
 * @param queue Pointer to the queue.
 * @return Pointer to the data at the front of the queue.
 */
#define queue_front(queue) list_tail(queue)

/**
 * @brief Retrieves the back element of the queue.
 * 
 * Alias for the `list_head` function, which provides access to the last element of the queue 
 * without removing it.
 * 
 * @param queue Pointer to the queue.
 * @return Pointer to the data at the back of the queue.
 */
#define queue_back(queue) list_head(queue)

/**
 * @brief Enqueues (adds) an element to the back of the queue.
 * 
 * Adds a new element to the end of the queue by reusing the linked list structure.
 * 
 * @param queue Pointer to the queue where the element will be added.
 * @param data Pointer to the data to be added to the queue.
 */
void enqueue(Queue *queue, void *data);

/**
 * @brief Dequeues (removes) an element from the front of the queue.
 * 
 * Removes the first element from the queue, freeing its associated resources if needed.
 * 
 * @param queue Pointer to the queue from which the front element will be removed.
 */
void dequeue(Queue *queue);

#endif
