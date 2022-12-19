#ifndef COMMON_H
#define COMMON_H

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Treat DataType as a void *, which can be cast into any type you want
 *
 */
typedef void *DataType;

/**
 * @brief The valid data type structure 
 *
 * The data is encapsulated and is valid only if it is not NULL
 */
typedef struct {
    DataType data;
    const bool valid;
} ValidDataType;

typedef bool (*EqualType)(DataType lhs, DataType rhs);

/**
 * @brief Type of function to compare two DataType values and returns:
 * -1 if lhs < rhs
 * 0 if lhs == rhs
 * 1 otherwise
 */
typedef int (*CompareType)(DataType lhs, DataType rhs);

/**
 * @brief Type of function to visit a node or vertex in a read-only way
 * 
 */
typedef void (*VisitType)(DataType);

/**
 * @brief Get the value where the DataType value (void *) points to
 *
 */
#define DATAVALUE(type, data) (*(type *)(data))

/**
 * @brief Check if two ints are equal
 *
 * @param lhs left int
 * @param rhs right int
 * @return true equal
 * @return false not equal
 */
bool equal_ints(DataType lhs, DataType rhs);

/**
 * @brief Compare two ints
 *
 * @param lhs left int
 * @param rhs right int
 * @return int -1 if lhs < rhs; 1 if lhs > rhs; 0 if lhs == rhs
 */
int compare_ints(DataType lhs, DataType rhs);

/**
 * @brief Swap two data
 *
 * @param lhs the address of the left hand side
 * @param rhs the address of the right hand side
 */
extern void swap_data(DataType *lhs, DataType *rhs);

/**
 * @brief Return the address of the larger one of two data
 *
 * @param lhs the address of the left one
 * @param rhs the address of the right one
 * @param c the comparison function
 * @return DataType* the address of the larger one
 */
extern DataType *larger_of(DataType *lhs, DataType *rhs, CompareType c);

/**
 * @brief Return the address of the smaller one of two data
 *
 * @param lhs the address of the left one
 * @param rhs the address of the right one
 * @param c the comparison function
 * @return DataType* the address of the smaller one
 */
extern DataType *smaller_of(DataType *lhs, DataType *rhs, CompareType c);

#endif // COMMON_H