#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/**
 * @file linked_list.h
 * @brief Header file for linked list initialization and management.
 */

/**
 * @brief Structure representing a node in the linked list.
 */
typedef struct _ListNode {
    void *data;               /**< Pointer to the data stored in the node. */
    struct _ListNode *next;   /**< Pointer to the next node in the list. */
} ListNode;

/**
 * @brief Structure representing a linked list.
 */
typedef struct _List {
    ListNode *head;           /**< Pointer to the head node of the list. */
    ListNode *tail;           /**< Pointer to the tail node of the list. */
    int num_elem;             /**< Number of elements in the list. */
    void (*destroy)(void *data); /**< Function pointer to the element destructor. */
} List;

/**
 * @brief Initializes a new list.
 *
 * This function creates and initializes a new list structure. It also sets
 * a callback function for destroying list elements, which will be called
 * whenever an element is removed from the list or when the list is destroyed.
 *
 * @param destroy A pointer to a function. This function will be used to free memory 
 *                or perform cleanup on data elements stored in the list. 
 *                If no cleanup is required, pass NULL.
 *
 * @return A pointer to the newly created list structure, or NULL if memory allocation fails.
 *
 * @note The caller is responsible for managing the memory of the list structure returned by this function.
 *       The list should be properly destroyed using the appropriate function to avoid memory leaks.
 */
List *list_init(void (*destroy)(void *data));

/**
 * @brief Inserts a new element into the list after the specified node.
 *
 * This function inserts a new element containing the provided data into the list 
 * immediately after the specified node. If the specified node is NULL, the element 
 * is inserted at the head of the list.
 *
 * @param list A pointer to the list structure.
 * @param previous A pointer to the node after which the new element should be inserted.
 *                 If NULL, the element is inserted at the head of the list.
 * @param data A pointer to the data to be inserted into the list.
 */
void list_insert_next(List *list, ListNode *previous, void *data);

/**
 * @brief Removes the element from the list immediately after the specified node.
 *
 * This function removes the element immediately after the specified node from the list.
 * If the specified node is NULL, the element at the head of the list is removed.
 *
 * @param list A pointer to the list structure.
 * @param previous A pointer to the node before the element to be removed.
 *                 If NULL, the element at the head of the list is removed.
 */
void list_remove_next(List *list, ListNode *previous);

/**
 * @brief Destroys the list and frees associated memory.
 *
 * This function destroys the list, freeing all memory associated with it,
 * including the memory for the data elements if a destroy function was specified
 * when the list was initialized.
 *
 * @param list A pointer to the list structure to be destroyed.
 */
void list_terminate(List *list);

/**
 * @brief Appends a new element at list end.
 * 
 * This function appends a new node at the end of list.
 * 
 * @param list A pointer to the list structure where the new node will be inserted
 * @param data A pointer to data to be inserted into list.
 */
void list_append(List *list, void *data);


/**
 * @brief Searches for an element in the list.
 *
 * This function searches for an element in the list that matches the provided data,
 * using the specified comparison function, and returns a pointer to the previous element 
 * to the searched one.
 *
 * @param list A pointer to the list structure.
 * @param compare A pointer to a function that compares two elements.
 * @param x A pointer to the data to be searched for in the list.
 *
 * @return A pointer to the previous element to the searched one, or NULL if no matching element is found.
 */
ListNode *list_search(const List *list, int (*compare)(void *a, void *b), void *x);

/**
 * @brief Merges two lists into a single list.
 *
 * This function merges two lists into a single list. The elements of the second list
 * are appended to the end of the first list. If a destroy function is specified,
 * it will be used to manage the memory of the elements.
 *
 * @param list1 A pointer to the first list structure.
 * @param list2 A pointer to the second list structure.
 * @param destroy A pointer to a function to destroy the elements. If no cleanup is required, pass NULL.
 *
 * @return A pointer to the newly merged list structure, or NULL if memory allocation fails.
 * 
 * @note list1 and list2 pointers shall be no longer used once the memory space allocated for them
 *       will be liberated in to order to prevent data conflict among their usage and the new merged list
 *       stucture. Besides, the user is responsible for giving the appropriate destroy function to liberate
 *       the list nodes in case of list1 and list2 nodes have been allocated with different routines.
 */
List *list_merge(List *list1, List *list2, void (*destroy)(void *data));

/**
 * @brief Merges two sorted lists into a single sorted list.
 *
 * This function merges two sorted lists into a single sorted list. The elements of the
 * second list are merged into the first list in sorted order. If a destroy function is
 * specified, it will be used to manage the memory of the elements. The compare function
 * is used to maintain the sorted order.
 *
 * @param list1 A pointer to the first sorted list structure.
 * @param list2 A pointer to the second sorted list structure.
 * @param destroy A pointer to a function to destroy the elements. If no cleanup is required, pass NULL.
 * @param compare A pointer to a function that compares two elements to determine their order.
 *
 * @return A pointer to the newly merged sorted list structure, or NULL if memory allocation fails.
 */
List *list_merge_sorted(List *list1, List *list2, void (*destroy)(void *data), int (*compare)(void *a, void *b));

/**
 * @brief Reverses the order of elements in the list.
 *
 * This function reverses the order of elements in the specified list.
 *
 * @param list A pointer to the list structure to be reversed.
 *
 * @return A pointer to the reversed list structure, or NULL if memory allocation fails.
 */
void list_reverse(List *list);

/**
 * @brief Prints all the elements of List
 * 
 * This functions prints all nodes from a list in a specified stream by using a user defined
 * node_print function which protype must be
 * 
 *        void node_print(ListNode * node);
 * 
 * @param list a List pointer
 * @param node_print user defined function for printing a node
 */
void list_print(List * list, void (*node_print)(ListNode * node));

/**
 * @brief Retrieves the head node of the list.
 *
 * @param list A pointer to the list structure.
 *
 * @return A pointer to the head node of the list.
 */
#define list_head(list) ((list)->head)

/**
 * @brief Retrieves the tail node of the list.
 *
 * @param list A pointer to the list structure.
 *
 * @return A pointer to the tail node of the list.
 */
#define list_tail(list) ((list)->tail)

/**
 * @brief Retrieves the number of elements in the list.
 *
 * @param list A pointer to the list structure.
 *
 * @return The number of elements in the list.
 */
#define list_num_elem(list) ((list)->num_elem)


#endif /* LINKED_LIST_H */
