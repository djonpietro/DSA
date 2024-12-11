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

ListNode *list_search(const List *list, int (*compare)(void *a, void *b), void *x) {
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

List *list_merge_sorted(List *list1, List *list2, void (*destroy)(void *data), int (*compare)(void *a, void *b)) {
    ListNode *walker1 = list1->head->next,
             *walker2 = list2->head->next,
             dummy,
             *tail = &dummy;
    
    dummy.next = NULL;

    while (walker1 != NULL && walker2 != NULL) {
        if (compare(walker1->data, walker2->data) <= 0) {
            tail->next = walker1;
            walker1 = walker1->next;
        } else {
            tail->next = walker2;
            walker2 = walker2->next;
        }

        tail = tail->next;
    }    

    if (walker1 == NULL)
        tail->next = walker2;
    else
        tail->next = walker1;
    
    list1->num_elem += list2->num_elem;

    list1->head->next = dummy.next;

    list1->destroy = destroy;

    free(list2->head); free(list2);

    return list1;
}

ListNode *reverse(ListNode *head) {
    if (!head->next)
        return head;
    else {
        ListNode *newHead = reverse(head->next);
        (head->next)->next = head;
        head->next = NULL;
        return newHead;
    }
}

void list_reverse(List *list) {
    if (list == NULL) {
        fputs(NULL_LIST_POINTER, stderr);
        return;
    }

    list->head->next = reverse(list->head->next);
}

void  list_print(List * list, void (*node_print)(ListNode * node)) {
    int total_char = 0;

    ListNode * walker = list_head(list)->next;

    while (walker != NULL) {
        node_print(walker);
        walker = walker->next;
    }
}
