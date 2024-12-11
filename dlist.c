#include "dlist.h"
#include <stdlib.h>
#include <stdio.h>

#define DLIST_ALLOCATION_ERROR "Error in memory alocation for list\n"

#define DLIST_NODE_ALLOCATION_ERROR "Error in memory allocation for list node\n"

#define NO_EMPTY_DLIST_REMOVAL "No remotion on a empty list\n"

#define NULL_DLIST_POINTER "List pointer is null\n"

#define PREVIOUS_PARAM_NULL "Param previous is null\n"

#define NULL_COMPARE_POINTER "Param comapare is null"

#define DLIST_HEAD_REMOVAL_TRY "Prev fiel next is dlist head"

#define NULL_POINTER_FOR_X "searched data is null"

Dlist * dlist_init(void (*destroy)(void * data)) {

    Dlist * dlist = malloc(sizeof(Dlist));
    if (!dlist) {
        fputs(DLIST_ALLOCATION_ERROR, stderr);
        exit(1);        
    }

    DlistNode * head = malloc(sizeof(DlistNode));
    if (!head) {
        fputs(DLIST_ALLOCATION_ERROR, stderr);
        exit(1);
    }

    head->prev = head->next = head;

    dlist->head = head;

    dlist->num_elem = 0;

    dlist->destroy = destroy;

    return dlist;
}

void dlist_insert_next(Dlist * dlist, DlistNode * prev, void * data){
    DlistNode * newNode = malloc(sizeof(DlistNode));

    if (!newNode) {
        fputs(DLIST_ALLOCATION_ERROR, stderr);
        exit(1);
    }

    newNode->data = data;

    newNode->prev = prev; newNode->next = prev->next;
    prev->next = newNode;

    ++dlist_num_elem(dlist);
}

void dlist_insert_prev(Dlist * dlist, DlistNode * next, void * data){
    DlistNode * newNode = malloc(sizeof(DlistNode));

    if (!newNode) {
        fputs(DLIST_ALLOCATION_ERROR, stderr);
        exit(1);
    }

    newNode->data = data;

    newNode->prev = next->prev; newNode->next = next;
    next->prev = newNode;

    ++dlist_num_elem(dlist);
}

void  delist_remove_next(Dlist * dlist, DlistNode * prev) {
    if (!prev) {
        fputs(PREVIOUS_PARAM_NULL, stderr);
        return;
    } else if (!dlist) {
        fputs(NULL_DLIST_POINTER, stderr);
        return;
    } else if (dlist->num_elem == 0) {
        fputs(NO_EMPTY_DLIST_REMOVAL, stderr);
        return;
    } else if (prev->next == dlist_head(dlist)){
        fputs(DLIST_HEAD_REMOVAL_TRY, stderr);
        return;
    }

    DlistNode * old = prev->next;

    void * data = old->data;

    if (dlist->destroy)
        dlist->destroy(data);

    prev->next = old->next;
    old->next->prev = old->prev;
    free(old); 
    dlist_num_elem(dlist)--;
}

void dlist_remove_prev(Dlist * dlist, DlistNode * next) {
    if (!next) {
        fputs(PREVIOUS_PARAM_NULL, stderr);
        return;
    } else if (!dlist) {
        fputs(NULL_DLIST_POINTER, stderr);
        return;
    } else if (dlist->num_elem == 0) {
        fputs(NO_EMPTY_DLIST_REMOVAL, stderr);
        return;
    } else if (next->prev == dlist_head(dlist)){
        fputs(DLIST_HEAD_REMOVAL_TRY, stderr);
        return;
    }

    DlistNode * old = next->prev;
    void * data = old->data;

    if (dlist->destroy)
        dlist->destroy(data);

    next->prev = old->prev;
    old->prev->next = next;
    free(old);
    dlist_num_elem(dlist)--;
}

void dlist_terminate(Dlist * dlist) {
    if (!dlist) {
        fputs(NULL_DLIST_POINTER, stderr);
        return;
    }

    while (dlist_num_elem(dlist) != 0) {
        delist_remove_next(dlist, dlist_head(dlist));
    }
    free(dlist_head(dlist));
    free(dlist);
}


DlistNode * dlist_search(Dlist * dlist, void * x, int (*compare)(void * a, void * b)) {
    if (!dlist) {
        fputs(NULL_DLIST_POINTER, stderr);
        return NULL;
    } else if (!x) {
        fputs(NULL_POINTER_FOR_X, stderr);
        return NULL;
    } else if (!compare) {
        fputs(NULL_COMPARE_POINTER, stderr);
        return NULL;
    }
    
    DlistNode * walker  = dlist_head(dlist)->next;

    while (walker != dlist_head(dlist)) {
        if (!compare(walker->data, x))
            return walker;
        walker = walker->next;
    }
    return NULL;
}

void dlist_rotate(Dlist * dlist, int i) {
    if (!dlist) {
        fputs(NULL_DLIST_POINTER, stderr);
        return;
    } 

    switch (dlist_num_elem(dlist)) {
        case 0: fputs("Dlist is empty\n", stderr); return;
        case 1: fputs("Dlist has just one node", stderr); return;
    }

    int num_jumps = i % dlist_num_elem(dlist);

    if (num_jumps == 0)
        return;

    DlistNode * pt = dlist_head(dlist)->next;
    DlistNode * head = dlist_head(dlist);
    
    for (int j = 0; j < num_jumps; j++)
        pt = pt->next;
    

    /*Lets call the head previous node of tail, and next node of front.
    In order to rotate the list, we shall do:
    
    Tail new next is front*/
    head->prev->next = head->next;
    
    /*Front new previous is tail*/
    head->next->prev = head->prev;
    
    /*Head new next is pt. Head new previous is pt previous node*/
    head->next = pt; head->prev = pt->prev;
    
    /*Pt old previous node now points to head*/
    pt->prev->next = head;
    
    /*Pt new previous is head*/
    pt->prev = head;
}