#ifndef SEARCHING_H
#define SEARCHING_H

#include "vector.h"

/**
 * @brief Search an element in a vector linearly
 * 
 * @param v the vector
 * @param d the query data
 * @param e the function to check if two elements are equal
 * @return int the index of the objective element, -1 if not found
 */
extern int linear_search(Vector *v, DataType d, EqualType e);

/**
 * @brief Search an element in an ORDERED vector using binary partition 
 * 
 * @param v he vector
 * @param d the query data
 * @param c the function to cpmpare two elements
 * @return int 
 */
extern int binary_search(Vector *v, DataType d, CompareType c);

extern void demo_searching();

#endif // SEARCHING_H