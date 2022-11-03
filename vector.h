#if !defined(VECTOR_H)
#define VECTOR_H

#include "common.h"

/**
 * @brief The vector structure
 * A sequence list which can dynamically grow and shrink according to the number
 * of elements
 */
typedef struct {
    DataType *data;
    int size;
    int capacity;
} Vector;

/**
 * @brief Create a vector
 *
 * @return Vector* the created vector
 */
extern Vector *create_vector();

/**
 * @brief Destroy a vector
 *
 * @param v the vector to be destroyed
 */
extern void destroy_vector(Vector *v);

/**
 * @brief Insert a value into a certain indexed location of a vector
 * The elements after the inserted index (included) are then moved backward
 * accordingly one after another, the capacity is doubled when the vector is
 * full
 * @param v the vector
 * @param k the index of element to be inserted at
 * @param d the value to be inserted
 * @return true successfully inserted
 * @return false failed (wrong index or growing failed)
 */
extern bool insert_vector_by_index(Vector *v, int k, DataType d);

/**
 * @brief Remove a value from a certain indexed location of a vector
 * The elements after the removed index are then moved forward accordingly one
 * after another, the capacity is halved if the size is less than 1/4 capacity
 * @param v the vector
 * @param k the index of element to be removed
 * @param d copy of the element to be removed
 * @return true successfully removed
 * @return false failed (wrong index or shrinking failed)
 */
extern bool remove_vector_by_index(Vector *v, int k, DataType *d);

/**
 * @brief Insert a value at the end of a vector
 * 
 * @param v the vector
 * @param d the value to be inserted
 * @return true successfully inserted
 * @return false failed (growing failed)
 */
extern bool push_back_vector(Vector *v, DataType d);

/**
 * @brief Remove the last element of a vector
 * 
 * @param v the vector
 * @param d copy of the element popped back
 * @return true successfully removed
 * @return false failed (shrinking failed)
 */
extern bool pop_back_vector(Vector *v, DataType *d);

/**
 * @brief Search a value in a vector
 * 
 * @param v the vector
 * @param d the value to be searched
 * @return int the index of matched element, -1 if not found
 */
extern int search_vector(Vector *v, DataType d);

/**
 * @brief Demo for the vector
 * 
 */
extern void demo_vector();

#endif // VECTOR_H
