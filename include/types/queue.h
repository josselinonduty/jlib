#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdbool.h>
#include "base/generic.h"
#include "base/linked_list.h"

/**
 * @brief Queue flags
 * @typedef queue_flag
 */
typedef enum queue_flag
{
    QUEUE_SORTED,
    QUEUE_UNSORTED
} queue_flag;

/**
 * @private
 * @brief Queue
 * @typedef queue
 */
typedef struct queue queue;

/**
 * @brief Queue structure
 * @struct queue
 */
struct queue
{
    linked_list head;
    linked_list tail;

    generic_copy copy;
    generic_free free;
    generic_compare order;
};

/**
 * @brief Create a new queue
 * @param flag Queue flag
 * @param copy_fn Generic copy function
 * @param free_fn Generic free function
 * @param order_fn Generic compare function
 */
queue queue_create(generic_copy copy_fn, generic_free free_fn, generic_compare order_fn);

/**
 * @brief Destroy the queue
 * @param q queue
 */
void queue_destroy(queue *q);

/**
 * @brief Check if the queue is empty
 * @param q queue
 * @return True if the queue is empty, false otherwise
 */
bool queue_is_empty(queue q);

/**
 * @brief Get the length of the queue
 * @param q queue
 * @return long int
 */
long int queue_length(queue q);

/**
 * @brief Get the head of the queue
 * @param q queue
 * @return linked_list
 */
linked_list queue_get_head(queue q);

/**
 * @brief Get the tail of the queue
 * @param q queue
 * @return linked_list
 */
linked_list queue_get_tail(queue q);

/**
 * @brief Add an element at the end of the queue
 * @param q queue
 * @param data any
 */
void queue_enqueue(queue *q, any data);

/**
 * @brief Remove the first element of the queue
 * @param q queue
 * @return any
 */
any queue_dequeue(queue *q);

/**
 * @brief Print the queue
 * @param q queue
 * @param print_fn Generic print function
 */
void queue_print(queue q, generic_print print_fn);

#endif // __QUEUE_H__