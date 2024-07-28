#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

#define LIST_ALLOCATION_ERROR "Error in memory alocation for list\n"

#define LIST_NODE_ALLOCATION_ERROR "Error in memory allocation for list node\n"

#define NO_EMPTY_LIST_REMOVAL "No remotion on a empty list\n"

#define NULL_LIST_POINTER "List pointer is null\n"

#define PREVIOUS_PARAM_NULL "Param previous is null\n"

#define TAIL_NEXT_ERROR "Tail next is a null pointer\n"

#define NULL_COMPARE_POINTER "Param comapare is null"

List *list_init(void (*destroy)(void *data)) {
    List *list = malloc(sizeof(List));

    if (list == NULL) {
      fputs(LIST_ALLOCATION_ERROR, stderr);
      exit(1); 
    }

    ListNode *head = malloc(sizeof(ListNode));

    if (head == NULL) {
        fputs(LIST_NODE_ALLOCATION_ERROR, stderr); 
        exit(1);
    }

    head->next = NULL;

    list->head = list->tail = head;
    list->num_elem = 0;
    list->destroy = destroy;

    return list;
}

void list_insert_next(List *list, ListNode *previous, void *data) {
    ListNode *new_elem = malloc(sizeof(ListNode));

    if (new_elem == NULL) {
        fputs(LIST_NODE_ALLOCATION_ERROR, stderr); 
        exit(1);
    }

    new_elem->data = data;
    new_elem->next = previous->next;

    if (new_elem->next == NULL)
        list->tail = new_elem;

    previous->next = new_elem;

    list_num_elem(list)++;
}

void list_remove_next(List *list, ListNode *previous) {
    if (!list) {
        fputs(NULL_LIST_POINTER, stderr);
        return;
    } else if (!previous) {
        fputs(PREVIOUS_PARAM_NULL, stderr);
        return;
    } else if (!previous->next) {
        fputs(TAIL_NEXT_ERROR, stderr);
        return;
    }

    ListNode * old = previous->next;

    void * data = old->data;

    if (list->destroy)
        list->destroy(data);

    previous->next = old->next;
    
    if (previous->next == NULL)
        list->tail = previous;

    list->num_elem--;
}

void list_terminate(List *list) {
    if (!list) {
        fputs(NULL_LIST_POINTER, stderr);
        return;
    }

    while (list->head->next != NULL) {
        list_remove_next(list, list->head);
    }

    free(list_head(list));
    free(list);
}

void list_append(List *list, void *data) {
    list_insert_next(list, list_tail(list), data);
}

ListNode *list_search(List *list, int (*compare)(void *a, void *b), void *x) {
    if (!list) {
        fputs(NULL_LIST_POINTER, stderr);
        return NULL;
    } else if (!compare) {
        fputs(NULL_COMPARE_POINTER, stderr); 
        return NULL;
    }

    ListNode *tracer = list_head(list);

    while (tracer->next != NULL) {
        if (!compare(tracer->next->data, x)) 
            return tracer;
        tracer = tracer->next;
    } 

    return NULL;
}

List *list_merge(List *list1, List *list2, void (*destroy)(void *data)) {
    if (!list1 || !list2) {
        fputs(NULL_LIST_POINTER, stderr);
        return NULL;
    }

    list1->tail->next = list2->head->next;
    
    list1->num_elem += list2->num_elem;

    list1->destroy = destroy;

    free(list2->head);
    free(list2);

    return list1;
}