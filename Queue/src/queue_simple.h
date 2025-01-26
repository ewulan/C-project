// queue_simple.h
#ifndef QUEUE_SIMPLE_H
#define QUEUE_SIMPLE_H

#define SUCCESS 0
#define FAILURE -1

#define QUEUE_MAX_SIZE 20

typedef int ElementType;

// typedef struct Node {
//     ElementType t_data;             // Data stored in the node
//     struct Node *p_next;    // Pointer to the next node
// } Node;

// typedef struct {
//     Node *p_head;           // Pointer to the head node of the linked list
// } Queue;


typedef struct Node {
    ElementType t_data;             // Data stored in the node
    struct Node *p_next;    // Pointer to the next node
} Node;

typedef struct {
    Node *p_front;           // 
    Node *p_rear;
    int i_size;
    int i_capacity;
} Queue;

Queue* queue_construct(int i_size);
int queue_destruct(Queue *p_queue);

int queue_push(Queue *p_queue, ElementType i_item);
int queue_pop(Queue *p_queue, ElementType *p_item);
int queue_is_empty(Queue *p_queue);
int queue_is_full(Queue *p_queue);

#endif // QUEUE_SIMPLE_H