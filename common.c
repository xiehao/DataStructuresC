#include "common.h"

EqualType equal = equal_ints;

bool equal_ints(DataType lhs, DataType rhs) {
    return DATAVALUE(int, lhs) == DATAVALUE(int, rhs);
}