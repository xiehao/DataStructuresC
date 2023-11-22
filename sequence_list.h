#ifndef SEQUENCE_LIST_H
#define SEQUENCE_LIST_H

#include "common.h"

#define SEQUENCE_LIST_CAPACITY 256
// static const int SEQUENCE_LIST_CAPACITY = 256;

/**
 * @brief The sequence list structure
 * The sequence list is composed of a static array and an index of the last
 * element
 */
typedef struct {
    DataType data[SEQUENCE_LIST_CAPACITY];
    int last;
} SequenceList;

/**
 * @brief Create a sequence list
 *
 * @return SequenceList* the sequence list
 */
extern SequenceList *create_sequence_list();

/**
 * @brief Destroy a sequence list
 *
 * @param s the sequence list
 */
extern void destroy_sequence_list(SequenceList *s);

/**
 * @brief Insert an element into a certain indexed location of a sequence list
 * The elements after the inserted index (included) are then moved backward
 * accordingly one after another
 * @param s the sequence list
 * @param k the index of element to be inserted
 * @param d the value of the inserted element
 * @return true successfully inserted
 * @return false failed (full sequence list or wrong index)
 */
extern bool insert_sequence_list(SequenceList *s, int k, DataType d);

/**
 * @brief Remove an indexed element from a sequence list
 * The elements after the removed index are then moved forward accordingly one
 * after another
 * @param s the sequence list
 * @param k the index of element to be removed
 * @param p the value of the removed element, as a record
 * @return true successfully removed
 * @return false failed (empty sequence list or wrong index)
 */
extern bool remove_sequence_list(SequenceList *s, int k, DataType *p);

/**
 * @brief Search an element in a sequence list by value
 *
 * @param s the sequence list
 * @param d the value to be searched
 * @param e the function to check if two elements are equal
 * @return int the index of element matching the value, -1 if not found
 */
extern int search_sequence_list(SequenceList *s, DataType d, EqualType e);

/**
 * @brief Search an element in a sequence list by value
 * The elements are traversed reversely, easier to implement
 * @param s the sequence list
 * @param d the value to be searched
 * @param e the function to check if two elements are equal
 * @return int the index of element matching the value, -1 if not found
 */
extern int search_sequence_list_reversely(SequenceList *s, DataType d,
                                          EqualType e);

/**
 * @brief Insert an element at the end of a sequence list
 *
 * @param s the sequence list
 * @param d the value to be inserted
 * @return true successfully inserted
 * @return false failed (full sequence list)
 */
extern bool append_sequence_list(SequenceList *s, DataType d);

/**
 * @brief Check if a sequence list is empty
 *
 * @param s the sequence list
 * @return true is empty
 * @return false is not empty
 */
extern bool empty_sequence_list(SequenceList *s);

/**
 * @brief Check if a sequence list is full
 *
 * @param s the sequence list
 * @return true is full
 * @return false is not full
 */
extern bool full_sequence_list(SequenceList *s);

/**
 * @brief Demo of the sequence list
 *
 */
extern void demo_sequence_list();

extern SequenceList *merge_sequence_lists(SequenceList *sa, SequenceList *sb);
extern SequenceList *merge_sequence_lists_descendingly(SequenceList *sa,
                                                       SequenceList *sb);

#endif // SEQUENCE_LIST_H