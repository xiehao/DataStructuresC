#ifndef SEQUENCE_STACK
#define SEQUENCE_STACK

#include "sequence_list.h"

/**
 * @brief Sequence stack structure
 * Dependng on the existing structure SequenceList.
 */
typedef struct {
    SequenceList *_; // data
} SequenceStack;

/**
 * @brief Create a sequence stack object
 * 
 * @return pointer to dynamically allocated sequence stack
 */
extern SequenceStack *create_sequence_stack();

/**
 * @brief Destroy the sequence stack
 * 
 * @param s the sequence stack to be destroyed
 */
extern void destroy_sequence_stack(SequenceStack *s);

/**
 * @brief Check if the sequence stack is empty
 * 
 * @param s the sequence stack
 * @return true empty
 * @return false not empty
 */
extern bool empty_sequence_stack(SequenceStack *s);

/**
 * @brief Push an element to top of the sequence stack
 * 
 * @param s the sequence stack
 * @param d the element to be pushed
 * @return true successfully pushed
 * @return false failed (null pointer or stack overflow)
 */
extern bool push_sequence_stack(SequenceStack *s, DataType d);

/**
 * @brief Pop an element from top of the sequence stack
 * 
 * @param s the sequence stack
 * @param p pointer to the popped element
 * @return true successfully popped
 * @return false failed (null pointer or stack underflow)
 */
extern bool pop_sequence_stack(SequenceStack *s, DataType *p);

/**
 * @brief Peek the top of the sequence stack
 * 
 * @param s the sequence stack
 * @param p the value of the top element, as a record
 * @return true successfully peeked
 * @return false failed (null pointer or stack underflow)
 */
extern bool top_sequence_stack(SequenceStack *s, DataType *p);

/**
 * @brief Demo of the sequence stack
 * 
 */
extern void demo_sequence_stack();

#endif // SEQUENCE_STACK