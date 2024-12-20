#include "array.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define ARRAY_ALLOCATION_ERROR "Memory allocation error for the array"

#define ARRAY_LIST_ALLOCATION_ERROR "Error in memory allocation for array data for specified length"

#define ARRAY_NULL_POINTER "Array pointer parameter is NULL"

Array * array_init(void (*destroy)(void * data), int init_size, size_t elem_size) {
    Array * array = malloc(sizeof(Array));
    if (!array) {
        fputs(ARRAY_ALLOCATION_ERROR, stderr);
        return NULL;
    }

    array->destroy = destroy;

    if (init_size > 0) {
        array->list = calloc(init_size, elem_size);
        if (!array->list) {
            fputs(ARRAY_LIST_ALLOCATION_ERROR, stderr);
            free(array);
            return NULL;
        }
        return array;
    }
    else {
        array->list = calloc(10, elem_size);
        if (!array->list) {
            fputs(ARRAY_LIST_ALLOCATION_ERROR, stderr);
            free(array);
            return NULL;
        }
        return array;
    }
}

void array_reallocate(Array * array, int new_size) {
    if (!array) {
        fputs(ARRAY_NULL_POINTER, stderr);
        return ;
    } else if (new_size <= array->total_size) 
        return ;
    
    void * new_list = calloc(new_size, array->elem_size);
    if (!new_list) {
        fputs(ARRAY_LIST_ALLOCATION_ERROR, stderr);
        return ;
    }

    memcpy(new_list, array->list, array->total_size * array->elem_size);
    
    free(array->list);

    array->list = new_list;
    array->total_size = new_size;
}
