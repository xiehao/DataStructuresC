#ifndef SEQUENCE_QUEUE_H
#define SEQUENCE_QUEUE_H

#include "common.h"

#define SEQUENCE_QUEUE_CAPACITY 1024

/**
 * @brief The sequence queue structure 
 * A sequence queue consists of a static array, a front index and a rear index
 */
typedef struct {
    DataType data[SEQUENCE_QUEUE_CAPACITY];
    int front;
    int rear;
    int size;
} SequenceQueue;

/**
 * @brief Create a sequence queue
 * 
 * @return SequenceQueue* the created queue
 */
extern SequenceQueue *create_sequence_queue();

/**
 * @brief Destroy the sequence queue
 * 
 * @param s the queue to be destroyed
 */
extern void destroy_sequence_queue(SequenceQueue *s);

/**
 * @brief Check if a sequence queue is empty
 * 
 * @param s the sequence queue
 * @return true is empty
 * @return false is not empty
 */
extern bool empty_sequence_queue(SequenceQueue *s);

/**
 * @brief Check if a sequence queue is full
 * 
 * @param s the sequence queue
 * @return true is full
 * @return false is not full
 */
extern bool full_sequence_queue(SequenceQueue *s);

/**
 * @brief Push an element into a sequence queue
 * 
 * @param s the sequence queue
 * @param d the pushed data
 * @return true successfully pushed
 * @return false failed (full queue)
 */
extern bool push_sequence_queue(SequenceQueue *s, DataType d);

/**
 * @brief Pop an element out of a sequence queue
 * 
 * @param s the sequence queue
 * @param d the popped data
 * @return true successfully popped
 * @return false failed (empty queue)
 */
extern bool pop_sequence_queue(SequenceQueue *s, DataType *d);

/**
 * @brief Demo of sequence queue
 * 
 */
extern void demo_sequence_queue();

#endif // SEQUENCE_QUEUE_H