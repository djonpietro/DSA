#ifndef STACK_H
#define STACK_H

#include "linked_list.h"

/**
 * @file stck.h
 * @brief Simple implementation of a stack based on linked lists
 */

/**
 * @brief A item in the stack
 * 
 * Defines a item on the stack based on linked list nodes
 */
typedef ListNode StackNode;

/**
 * @brief The stack structure 
 * 
 * Defines a stack type based on the linked list structure
 */
typedef List Stack;

#define stack_init list_init
#define stack_terminate list_terminate

/**
 * @brief Stack top item
 * 
 * @return a pointer to stack top
 */
#define stack_top(stack) list_head(stack)

/**
 * @brief Stack bottom item
 * 
 * @return A pointer to  the stack top item
 */
#define stack_bottom(stack) list_tail(stack)

/**
 * @brief Pushes a new element o the stack
 * 
 * @param stack a pointer to the stack
 * @param x data to be pushed
 */
void push(Stack * stack, void * x);

/**
 * @brief Pops a element from the stack
 * 
 * @param stack a pointer to the stacks
 * 
 * @return the pointer to the popped data
 */
void pop(Stack * stack);
#endif 