#ifndef HEAP_H
#define HEAP_H

#include "common.h"

/**
 * @brief The heap/priority queue structure
 * 
 */
typedef struct _heap Heap;

/**
 * @brief Create a heap object
 * 
 * @param c the comparison function
 * @return Heap* the created heap
 */
extern Heap *create_heap(CompareType c);

/**
 * @brief Create a heap from an array object
 * 
 * @param d the array of raw data
 * @param n the length of the arrary
 * @param c the comparison function
 * @return Heap* the created heap
 */
extern Heap *create_heap_from_array(DataType d[], int n, CompareType c);

/**
 * @brief Destroy a heap
 * 
 * @param h the heap
 */
extern void destroy_heap(Heap *h);

/**
 * @brief Get the size of a heap
 * 
 * @param h the heap
 * @return int the size of the heap
 */
extern int size_of_heap(Heap *h);

/**
 * @brief Push an element into a heap, then the element is percolated up to a
 * proper location.
 *
 * @param h the heap
 * @param d the data to be pushed
 * @return true success to push
 * @return false failed to push
 */
extern bool push_heap(Heap *h, DataType d);

/**
 * @brief Pop an element (the top) out of a heap, then the last element is moved
 * to the top and percolated down to a proper location.
 *
 * @param h the heap
 * @return ValidDataType the popped encapsulated element
 */
extern ValidDataType pop_heap(Heap *h);

/**
 * @brief Peek the top of a heap
 * 
 * @param h the heap
 * @return ValidDataType the encapsulated top element
 */
extern ValidDataType top_heap(Heap *h);

/**
 * @brief The demo of heap
 * 
 */
extern void demo_heap();

#endif // HEAP_H