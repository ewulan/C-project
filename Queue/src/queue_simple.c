#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <queue_simple.h>

/*************************************
 * @brief Constructs a new queue.
 * 
 * This function creates a new queue and initializes its properties. 
 * The capacity of the queue is specified by the parameter.
 * 
 * @param i_size The capacity of the queue. Must be greater than 0 and less than or equal to QUEUE_MAX_SIZE.
 * @return Queue* If successful, returns a pointer to the new queue; otherwise, returns NULL.
 *************************************/
Queue* queue_construct(int i_size)
{
    Queue *p_queue = NULL;

    if (i_size<= 0 || i_size > QUEUE_MAX_SIZE)
    {
        printf("queue_construct : over size %d\n", i_size);
        return NULL;       
    }
    
    p_queue = (Queue *)malloc(sizeof(Queue));

    if (NULL == p_queue)
    {
        printf("queue_construct : malloc failed\n");
        return NULL;
    }

    p_queue->i_size = 0;
    p_queue->p_front = NULL;
    p_queue->p_rear = NULL;
    p_queue->i_capacity = i_size;

    return p_queue;   
}

/*************************************
 * @brief Destroys a queue and frees all associated memory.
 * 
 * This function releases all memory allocated for the queue, including its nodes.
 * 
 * @param p_queue A pointer to the queue to be destroyed.
 * @return SUCCESS if the queue is successfully destroyed; otherwise, returns FAILURE.
 *************************************/
int queue_destruct(Queue *p_queue)
{
    Node *p_curr = NULL;
    Node *p_next = NULL;

    if (NULL == p_queue)
    {
        printf("queue_destruct : input NULL ptr\n");
        return FAILURE;
    }   

    p_curr = p_queue->p_front;
    while (NULL != p_curr)
    {
        p_next = p_curr->p_next;
        free(p_curr);
        p_curr = p_next;

    }     

    free(p_queue);

    return SUCCESS;   
}

/*************************************
 * @brief Adds an element to the rear of the queue.
 * 
 * This function inserts a new element into the queue. If the queue is full, the operation fails.
 * 
 * @param p_queue A pointer to the queue.
 * @param i_item The element to be added to the queue.
 * @return SUCCESS if the element is successfully added; otherwise, returns FAILURE.
 *************************************/
int queue_push(Queue *p_queue, ElementType i_item)
{
    Node *p_item = NULL;

    if (NULL == p_queue)
    {
        printf("queue_push : input NULL ptr\n");
        return FAILURE;
    }

    if (1 == queue_is_full(p_queue))
    {
        printf("queue_push : queue is full\n");
        return FAILURE;
    }

    p_item = (Node *)malloc(sizeof(Node));
    if (NULL == p_item)
    {
        printf("queue_push : malloc failed\n");
        return FAILURE;
    }

    p_item->t_data = i_item;
    p_item->p_next = NULL;

    //Add first node into a empty queue
    if (NULL == p_queue->p_rear)
    {
        p_queue->p_front = p_queue->p_rear = p_item;

    }
    //Add node into a non empty queue
    else
    {
        p_queue->p_rear->p_next = p_item;
        p_queue->p_rear = p_item;

    }

    p_queue->i_size++;
            
    return SUCCESS;   
}

/*************************************
 * @brief Removes an element from the front of the queue.
 * 
 * This function removes the element at the front of the queue and stores it in the provided pointer.
 * 
 * @param p_queue A pointer to the queue.
 * @param p_item A pointer to store the removed element.
 * @return SUCCESS if the element is successfully removed; otherwise, returns FAILURE.
 *************************************/
int queue_pop(Queue *p_queue, ElementType *p_item)
{
    Node *p_drop = NULL;

    if (NULL == p_queue || NULL == p_item)
    {
        printf("queue_pop : input NULL ptr\n");
        return FAILURE;
    }

    if (1 == queue_is_empty(p_queue))
    {
        printf("queue_pop : queue is empty\n");
        return FAILURE;
    }

    *p_item = p_queue->p_front->t_data;
    p_drop = p_queue->p_front;

    
    //Pop first node from a 1 node queue
    if (p_queue->p_front == p_queue->p_rear)
    {
        p_queue->p_front = p_queue->p_rear = NULL;
        p_queue->i_size = 0;
    }
    else
    {
        p_queue->p_front = p_drop->p_next;
        p_queue->i_size--;
    }    

    free(p_drop);
    p_drop = NULL;

    return SUCCESS;   
}

/*************************************
 * @brief Checks if the queue is empty.
 * 
 * This function checks whether the queue contains any elements.
 * 
 * @param p_queue A pointer to the queue.
 * @return 1 if the queue is empty; otherwise, returns 0. If the input pointer is NULL, returns FAILURE.
 *************************************/
int queue_is_empty(Queue *p_queue)
{
    if (NULL == p_queue)
    {
        printf("queue_is_empty : input NULL ptr\n");
        return FAILURE;
    }

    return (0 == p_queue->i_size);   
}

/*************************************
 * @brief Checks if the queue is full.
 * 
 * This function checks whether the queue has reached its maximum capacity.
 * 
 * @param p_queue A pointer to the queue.
 * @return 1 if the queue is full; otherwise, returns 0. If the input pointer is NULL, returns FAILURE.
 *************************************/
int queue_is_full(Queue *p_queue)
{
    if (NULL == p_queue)
    {
        printf("queue_is_full : input NULL ptr\n");
        return FAILURE;
    }

    return (p_queue->i_capacity == p_queue->i_size);    
}

