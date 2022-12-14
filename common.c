#include "common.h"

bool equal_ints(DataType lhs, DataType rhs) {
    return DATAVALUE(int, lhs) == DATAVALUE(int, rhs);
}

int compare_ints(DataType lhs, DataType rhs) {
    int left = DATAVALUE(int, lhs);
    int right = DATAVALUE(int, rhs);
    return left < right ? -1 : (left > right ? 1 : 0);
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