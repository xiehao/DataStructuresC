#include "common.h"

EqualType equal = equal_ints;

bool equal_ints(DataType lhs, DataType rhs) {
    return DATAVALUE(int, lhs) == DATAVALUE(int, rhs);
}

void swap_data(DataType *lhs, DataType *rhs) {
    DataType data = *lhs;
    *lhs = *rhs;
    *rhs = data;
}

DataType *larger_of(DataType *lhs, DataType *rhs, CompareType c) {
    if (!lhs) return rhs;
    if (!rhs) return lhs;
    return c(lhs, rhs) < 0 ? rhs : lhs;
}

DataType *smaller_of(DataType *lhs, DataType *rhs, CompareType c) {
    if (!lhs) return rhs;
    if (!rhs) return lhs;
    return c(lhs, rhs) < 0 ? lhs : rhs;
}