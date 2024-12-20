#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>


/**
 * @brief typedef for an Arry list type
 */
typedef struct Array {
    void * list;                    //defines the array itself as a list of elements 
    int num_elem;                   //number of elements in the array
    int total_size;                 //the total length of the array
    size_t elem_size;               //length in bytes of one single element        
    void (*destroy)(void * data);   //funtion pointer for elements cleaning up routine
} Array;

/**
 * @brief Initializes a new Array
 * 
 * It allocates a new array of a specified length given by init_tam parameter.
 * 
 * @param destroy A pointer to funtion that will be used to clean up
 *                array elements from memory. The prototype of this shloud
 *                be 
 *                      void destroy (void * data);
 *                For example, if you use malloc() from stdlib to allocate data
 *                free() can passed as the destroy funtion.
 * 
 * @param init_size Speciefies a initial length for the array.
 *                 Non positive values (<= 0) will create an
 *                 array of inital length 10
 * 
 * @return A pointer to a new Array type.
 */

Array * array_init(void (*destroy)(void * data), int init_size, size_t elem_size);

/**
 * @brief Reallocates an array in memory
 * 
 * @param array Pointer to the array to be reallocated
 * 
 * @param new_size The new length of the reallocated array. If new_len
 *                is lower than the previous len, than a NULL pointer
 *                shall be returned.
 * 
 * @param elem_size The size in bytes of a individual element of the array
 * 
 */
void array_reallocate(Array * array, int new_size);


/**
 * @brief Inserts a new element in the specified index
 * 
 * @param array Pointer to the array where the element will be inserted at
 * 
 * @param index The index number where the element will be inserted
 * 
 * @param data A pointer to the data to be inserted
 * 
 * @return 0 if the insertion is successful, 1 otherwise. Failed isertions might
 *         occur due to index being lower than the total length of the array, or
 *         some of the paremeters is NULL.
 */
int array_insert_at(Array * array, int index, void * data);

/**
 * @brief Appends a new element at the end of the array
 * 
 * @param array To array where the element will be appended
 * 
 * @param data a pointer the data to be appendeded 
 * 
 */
void array_append(Array * array, void * data);

/**
 * @brief Inserts a new element so that the array is kept sorted
 * 
 * Supposing a sorted array, this function makes an insertion so that the array continues sorted.
 * It will do a sequential search comparing each element until find some so that it has data key
 * greater than the to be inserted one, then inserts in before. If an element with the same data
 * key is found, then the function will return the index where this element is, so the user 
 * can decide if will insert this element or not. If so, then the user can use the array_inser_at
 * function. The comprison function used in search is user defined, and for more details of
 * how it should work, see the docstring of array_search_function. 
 * 
 * @param array Pointer to the array where the element will be inserted
 * 
 * @param data The memory address of data to be inserted
 * 
 * @param compare A function pointer used to compare elements. See array_search for 
 *                more details.
 * 
 * @return If the array contains a previous element with the same data key, then it
 *         will return the index of this element. If not, it shall return -1. 
 */
int array_sorted_insert(Array * array, void * data, int (*compare)(void*a, void*b));

/**
 * @brief Removes the element at the specified index
 * 
 * @param array The array where the element will be removed
 * 
 * @param index The index of the element to be removed
 * 
 * @return 0 for successful removal, 1 otherwise.
 */
int array_remove_at(Array * array, int index);

/**
 * @brief Removes the last element of the array
 * 
 * @param array Pointe rto the array where the element will be removed
 * 
 * @return 0 for successful removal, 1 otherwise
 */
int array_remove_last(Array * array);

/**
 * @brief Seaches for a x element in the array using a user or standard library  comparing function
 * 
 * It does a sequential search through the array, and stops at the first
 * occurence of the searched element. A comparison function will be used to do
 * it so. The prototype of this function shall be
 * 
 *      int compare(void *a, void *b);
 * 
 * The logic implemented by compare must be analogue to strcmp() from string.h. 
 * So if a is greater than b, then it shall return a positive value. 
 * On the other hand, if b is greater than a, then it should
 * return a negative value. If a and b are equal, than it must return 0.
 * 
 * @param array A pointer to the array where the search will be done
 * 
 * @param x A pointer to data to be seached
 * 
 * @param comapare A comparison function analogue to strcmp() from string.h
 * 
 * @return The pointer to the memory space where the searched data is allocated.
 *         Be careful bacause a void type pointer is returned, so a casting might
 *         be necessary in order to using it. 
 */
void * array_search(Array * array, void * x, int (*compare)(void*a, void*b));

void array_remove_duplicates(Array * array, int (*compare)(void*a, void*b ));

void * array_quickselect(Array * array, int n);

#define array_total_size(array) ((array)->total_size)

#define array_elem_size(array) ((array)->elem_size)

#define array_num_elem(array) ((array)->num_elem)

#endif