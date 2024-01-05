#include <stdlib.h>
#include <stdio.h>
#include "priority_queue.h"

struct node {
    int data;
    int priority;
};
typedef struct node Node;

struct queue {
    int size;
    int capacity;
    Node* heap;  // an array of nodes
};
typedef struct queue Queue;

void swap_nodes(Node* node1, Node* node2) {
    Node temp;
    
    temp = *node1;
    *node1 = *node2;
    *node2 = temp;
}

void fix_up(Queue* hQueue, int index_of_node) {
    Queue* pQueue = (Queue*)hQueue;
    int index_of_parent;
    
    if (index_of_node > 0) {   // if we have a parent else we are at the root and there is nothing to fix up
        index_of_parent = (index_of_node - 1) / 2;
        if (pQueue->heap[index_of_node].priority > pQueue->heap[index_of_parent].priority) {
            swap_nodes(pQueue->heap + index_of_node, pQueue->heap + index_of_parent);
            fix_up(pQueue, index_of_parent);
        }
    }
}

void fix_down(Queue* hQueue, int index_of_node) {
    Queue* pQueue = (Queue*)hQueue;
    int index_of_left = index_of_node * 2 + 1;
    int index_of_right = index_of_node * 2 + 2;
    int index_of_highest_priority;
    
    if (index_of_left < pQueue->size) {
        if (index_of_right < pQueue->size) {  // if we have 2 children
            index_of_highest_priority = (pQueue->heap[index_of_left].priority > pQueue->heap[index_of_right].priority) ?
            index_of_left : index_of_right;
        } else {  // we only have one child   
            index_of_highest_priority = index_of_left;
        }
        if (pQueue->heap[index_of_node].priority < pQueue->heap[index_of_highest_priority].priority) {
            swap_nodes(pQueue->heap + index_of_node, pQueue->heap + index_of_highest_priority);
            fix_down(pQueue, index_of_highest_priority);
        }
    }
}

PRIORITY_QUEUE priority_queue_init_default(void) {
    Queue* pQueue = (Queue*)malloc(sizeof(Queue));
    if (pQueue == NULL) {
        return NULL;
    }
    pQueue->size = 0;
    pQueue->capacity = 1;
    pQueue->heap = (Node*)malloc(sizeof(Node) * pQueue->capacity);
    if (pQueue->heap == NULL) {
        free(pQueue);
        return NULL;
    }
    return pQueue;
}

Status priority_queue_insert(PRIORITY_QUEUE hQueue, int priority_level, int data_item) {
    Queue* pQueue = (Queue*)hQueue;
    Node node;
    Node* temp;
    int i;
    
    if (pQueue->size >= pQueue->capacity) {
        temp = (Node*)malloc(sizeof(Node) * pQueue->capacity * 2);
        if (temp == NULL) {
            return FAILURE;
        }
        for (i = 0; i < pQueue->size; ++i) {
            temp[i] = pQueue->heap[i];
        }
        free(pQueue->heap);
        pQueue->heap = temp;
        pQueue->capacity *= 2;
    }
    node.data = data_item;
    node.priority = priority_level;
    
    if (pQueue->size == 0) {
        pQueue->heap[pQueue->size] = node;
        pQueue->size++;
    } else {
        pQueue->heap[pQueue->size] = node;
        pQueue->size++;
        fix_up(pQueue, pQueue->size - 1);
    }
    
    return SUCCESS;
}

int priority_queue_front(PRIORITY_QUEUE hQueue, Status* pStatus) {
    Queue* pQueue = (Queue*)hQueue;
    
    if (priority_queue_is_empty(hQueue)) {
        if (pStatus != NULL) {
            *pStatus = FAILURE;
        }
        return -1337;
    }
    
    if (pStatus != NULL) {
        *pStatus = SUCCESS;
    }
       
    return pQueue->heap[0].data;
}
 
Status priority_queue_service(PRIORITY_QUEUE hQueue) {
    Queue* pQueue = (Queue*)hQueue;
    Node* root = pQueue->heap + 0;
    Node* last_node = pQueue->heap + (pQueue->size - 1);
    
    if (priority_queue_is_empty(hQueue)) {
        return FAILURE;
    } else {
        swap_nodes(root, last_node);
        pQueue->size--;
        fix_down(pQueue, 0);
    }
    
    return SUCCESS;
}

Boolean priority_queue_is_empty(PRIORITY_QUEUE hQueue) {
    Queue* pQueue = (Queue*)hQueue;
    
    return pQueue->size == 0 ? TRUE : FALSE;
}

void priority_queue_destroy(PRIORITY_QUEUE* phQueue) {
    Queue* pQueue = (Queue*)*phQueue;
    
    free(pQueue->heap);
    free(pQueue);
    
    *phQueue = NULL;
}
