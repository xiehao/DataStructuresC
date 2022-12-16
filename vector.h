#if !defined(VECTOR_H)
#define VECTOR_H

#include "common.h"

/**
 * @brief The vector structure
 * A sequence list which can dynamically grow and shrink according to the number
 * of elements
 */
typedef struct _vector Vector;

/**
 * @brief Create a vector
 *
 * @param int the initial capacity
 * @return Vector* the created vector
 */
extern Vector *create_vector(int c);

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
 * @brief Get the address of an element of an vector
 * 
 * @param v the vector
 * @param k the index of the element
 * @return DataType* the address of the element
 */
extern DataType *vector_at(Vector *v, int k);

/**
 * @brief The number of elements of a vector
 * 
 * @param v the vector
 * @return int the number of elements
 */
extern int size_of_vector(Vector *v);

/**
 * @brief Check if a vector is empty
 * 
 * @param v the vector
 * @return true is empty
 * @return false is not empty
 */
extern bool is_vector_empty(Vector *v);

/**
 * @brief Make a vector empty by erase all elements in it
 * 
 * @param v the vector
 * @return Vector* the empty vector
 */
extern Vector *make_vector_empty(Vector *v);

/**
 * @brief Demo for the vector
 * 
 */
extern void demo_vector();

#endif // VECTOR_H
