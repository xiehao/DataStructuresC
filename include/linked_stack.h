#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include "linked_list.h"

/**
 * @brief The linked stack structure
 * The linked stack is actually an operation-limited linked list.
 */
typedef struct {
    LinkedList *_;
} LinkedStack;

/**
 * @brief Create a linked stack
 *
 * @return LinkedStack* the created linked stack
 */
extern LinkedStack *create_linked_stack();

/**
 * @brief Destroy the linked stack
 *
 * @param s the linked stack
 */
extern void destroy_linked_stack(LinkedStack *s);

/**
 * @brief Check if the linked stack is empty
 *
 * @param s the linked stack
 * @return true the stack is empty
 * @return false the stack is not empty
 */
extern bool empty_linked_stack(LinkedStack *s);

/**
 * @brief Peek the top of a linked stack
 *
 * @param s the linked stack
 * @param p the value of the top element, as a record
 * @return true successfully peeked
 * @return false failed (null pointer or stack underflow)
 */
extern bool top_linked_stack(LinkedStack *s, DataType *p);

/**
 * @brief Push an element into a linked stack
 *
 * @param s the linked stack
 * @param d the element to be pushed
 * @return true successfully pushed
 * @return false failed (null pointer or stack overflow)
 */
extern bool push_linked_stack(LinkedStack *s, DataType d);

/**
 * @brief Pop an element from the top of a linked stack
 *
 * @param s the linked stack
 * @param d the element to be popped
 * @return true successfully popped
 * @return false failed (null pointer or stack underflow)
 */
extern bool pop_linked_stack(LinkedStack *s, DataType *p);

/**
 * @brief Demo of the linked stack
 *
 */
extern void demo_linked_stack();

#endif // LINKED_STACK_H