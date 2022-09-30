#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "common.h"

/**
 * @brief The node of a linked list
 * 
 */
typedef struct LinkedNode {
    DataType data;
    struct LinkedNode *next;
} LinkedNode;

/**
 * @brief The linked list structure
 * The list contains at list a head node by default, making it easy to do some
 * operations, e.g. removal, consistently.
 */
typedef struct {
    LinkedNode *head;
} LinkedList;

/**
 * @brief Create a linked list
 *
 * @return LinkedList* the created linked list
 */
extern LinkedList *create_linked_list();

/**
 * @brief Clean up all nodes in a linked list, without destroying it
 *
 * @param s the linked list
 * @return true successfull cleaned up
 * @return false failed (null pointer)
 */
extern bool cleanup_linked_list(LinkedList *s);

/**
 * @brief Destroy linked list and free its memory
 *
 * @param s the linked list
 */
extern void destroy_linked_list(LinkedList *s);

/**
 * @brief Search an element in a linked list by its index
 *
 * @param s the linked list
 * @param k the index to be searched
 * @return LinkedNode* the result linked node, NULL if not found
 */
extern LinkedNode *search_linked_by_index(LinkedList *s, int k);

/**
 * @brief Search an element in a linked list by its value
 *
 * @param s the linked list
 * @param d the value to match
 * @return LinkedNode* the result linked node, NULL if not found
 */
extern LinkedNode *search_linked_by_data(LinkedList *s, DataType d);

/**
 * @brief Insert a value into a linked list BEFORE an indexed node
 *
 * @param s the linked list
 * @param k the index of node
 * @param d the value to be inserted
 * @return true successfully inserted
 * @return false failed (wrong index)
 */
extern bool insert_before_linked_by_index(LinkedList *s, int k, DataType d);

/**
 * @brief Insert a value into a linked list AFTER an indexed node
 *
 * @param s the linked list
 * @param k the index of node
 * @param d the value to be inserted
 * @return true successfully inserted
 * @return false failed (wrong index)
 */
extern bool insert_after_linked_by_index(LinkedList *s, int k, DataType d);

/**
 * @brief Remove and destroy an indexed node from a linked list
 *
 * @param s the linked list
 * @param k the index of node to be removed
 * @param p the value of the removed node, unchanged if failed to remove
 * @return true successfully removed
 * @return false failed (wrong index)
 */
extern bool remove_linked_by_index(LinkedList *s, int k, DataType *p);

/**
 * @brief Insert a node at the beginning (right after the head) of a linked list
 *
 * @param s the linked list
 * @param d the value to be inserted
 * @return true successfully inserted
 * @return false failed (cannot occur)
 */
extern bool add_front_linked_list(LinkedList *s, DataType d);

/**
 * @brief Remove the node right after the head (if it exists) from a linked list
 *
 * @param s the linked list
 * @param p the value from the removed node, unchanged if failed to remove
 * @return true successfully removed
 * @return false failed (wrong index)
 */
extern bool remove_front_linked_list(LinkedList *s, DataType *p);

/**
 * @brief Get the length of a linked list
 *
 * @param s the linked list
 * @return int the length of it
 */
extern int get_linked_list_length(LinkedList *s);

/**
 * @brief Demo of the linked list
 *
 */
extern void demo_linked_list();

#endif // LINKED_LIST_H