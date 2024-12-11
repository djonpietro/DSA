#ifndef DLIST_H
#define DLIST_H

#include "linked_list.h" 

// Structure representing a node in a doubly linked list.
typedef struct DlistNode {
    void * data;              // Pointer to the data stored in the node (generic type).
    struct DlistNode * next;  // Pointer to the next node in the list.
    struct DlistNode * prev;  // Pointer to the previous node in the list.
} DlistNode;

// Structure representing a doubly linked list.
typedef struct Dlist {
    DlistNode * head;          // Pointer to the first node of the list.
    int num_elem;              // Number of elements currently in the list.
    void (*destroy)(void * data); // Optional function pointer to free the memory of the data stored in the nodes.
} Dlist;

/**
 * Initializes a new doubly linked list.
 * 
 * @param destroy A function pointer to handle freeing the memory of the data (optional).
 * @return A pointer to the newly initialized list.
 */
Dlist * dlist_init(void (*destroy)(void * data));

/**
 * Inserts a new node after a given node.
 * 
 * @param dlist Pointer to the doubly linked list.
 * @param prev The node after which the new node will be inserted. Can be NULL to insert at the head.
 * @param data Pointer to the data to store in the new node.
 * @return A pointer to the inserted data, or NULL if the operation fails.
 */
void dlist_insert_next(Dlist * dlist, DlistNode * prev, void * data);

/**
 * Inserts a new node before a given node.
 *
 * @param dlist Pointer to the doubly linked list.
 * @param next The node before which the new node will be inserted. Can be NULL to insert at the tail.
 * @param data Pointer to the data to store in the new node.
 * @return A pointer to the inserted data, or NULL if the operation fails.
 */
void dlist_insert_prev(Dlist * dlist, DlistNode * next, void * data);

/**
 * Removes the node immediately after a given node.
 * 
 * @param dlist Pointer to the doubly linked list.
 * @param prev The node before the one to be removed.
 * @return A pointer to the data of the removed node, or NULL if the operation fails.
 */
void delist_remove_next(Dlist * dlist, DlistNode * prev);

/**
 * Removes the node immediately before a given node.
 * 
 * @param dlist Pointer to the doubly linked list.
 * @param next The node after the one to be removed.
 * @return A pointer to the data of the removed node, or NULL if the operation fails.
 */
void dlist_remove_prev(Dlist * dlist, DlistNode * next);

/**
 * Destroys the doubly linked list, freeing all nodes and their associated data.
 * 
 * @param dlist Pointer to the doubly linked list.
 */
void dlist_terminate(Dlist * dlist);

/**
 * Searches for a node containing specific data using a comparison function.
 * 
 * @param dlist Pointer to the doubly linked list.
 * @param x Pointer to the data to search for.
 * @param compare Function pointer to compare two data elements.
 * @return A pointer to the found node, or NULL if no match is found.
 */
DlistNode * dlist_search(Dlist * dlist, void * x, int (*compare)(void * a, void * b));

/**
 * Rotates the list by moving the head pointer `i` steps forward or backward.
 * 
 * @param dlist Pointer to the doubly linked list.
 * @param i The number of positions to rotate the list. Negative values rotate backward.
 */
void dlist_rotate(Dlist * dlist, int i);

/**
 * Sets a new first node for the list, effectively rotating the list to start from a given node.
 * 
 * @param dlist Pointer to the doubly linked list.
 * @param new_first Pointer to the node to set as the new head of the list.
 */
void dlist_new_first(Dlist * dlist, DlistNode * new_first);

/**
 * Converts the doubly linked list into a singly linked list.
 * 
 * @param dlist Pointer to the doubly linked list.
 * @return A pointer to the newly created singly linked list.
 */
List * dlist_to_list(Dlist * dlist);

/**
 * Macro to access the head node of the list.
 * 
 * @param dlist Pointer to the doubly linked list.
 * @return Pointer to the head node.
 */
#define dlist_head(dlist) ((dlist)->head)

/**
 * Macro to access the number of elements in the list.
 * 
 * @param dlist Pointer to the doubly linked list.
 * @return The number of elements in the list.
 */
#define dlist_num_elem(dlist) ((dlist)->num_elem)

#endif
