#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include "linked_list.h"

/**
 * @brief The linked queue structure
 *
 * The queue consists at least a front node and a rear node by default, making
 * it easy to do some operations, e.g. push and pop
 */
typedef struct {
    LinkedList *_;
    LinkedNode *front;
    LinkedNode *rear;
} LinkedQueue;

/**
 * @brief Create a linked queue
 * 
 * @return LinkedQueue* the created linked queue
 */
extern LinkedQueue *create_linked_queue();

/**
 * @brief Destroy a linked queue
 * 
 * @param s the linked queue to be destroyed
 */
extern void destroy_linked_queue(LinkedQueue *s);

/**
 * @brief Push an element into the rear of a linked queue
 * 
 * @param s the linked queue
 * @param d the data to pushed into
 * @return true successfully pushed
 * @return false failed (almost impossible)
 */
extern bool push_linked_queue(LinkedQueue *s, DataType d);

/**
 * @brief Pop the first element out of a linked queue
 * 
 * @param s the linked queue
 * @param d the data popped out
 * @return true successfully popped
 * @return false failed
 */
extern bool pop_linked_queue(LinkedQueue *s, DataType *d);

/**
 * @brief The demo of linked queue
 * 
 */
extern void demo_linked_queue();

#endif // LINKED_QUEUE_H