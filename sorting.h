#ifndef SORTING_H
#define SORTING_H

#include "common.h"

extern void insertion_sort(DataType *s, int f, int t, CompareType c);

extern void selection_sort(DataType *s, int f, int t, CompareType c);

extern void bubble_sort(DataType *s, int f, int t, CompareType c);

extern void quick_sort(DataType *s, int f, int t, CompareType c);

extern void demo_sorting();

#endif // SORTING_H