#ifndef COMMON_H
#define COMMON_H

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Treat DataType as a void *, which can be cast into any type you want
 *
 */
typedef void *DataType;

typedef bool (*EqualType)(DataType lhs, DataType rhs);

/**
 * @brief Check if two DataType values are equal.
 * 
 */
extern EqualType equal;

/**
 * @brief Get the value where the DataType value (void *) points to
 *
 */
#define DATAVALUE(type, data) *(type *)(data)

/**
 * @brief Check if two ints are equal
 * 
 * @param lhs left int
 * @param rhs right int
 * @return true equal
 * @return false not equal
 */
bool equal_ints(DataType lhs, DataType rhs);

#endif // COMMON_H