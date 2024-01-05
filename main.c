#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"


int main(int argc, char* arv[]) {
    PRIORITY_QUEUE hQueue = priority_queue_init_default();
    int i;
    if (hQueue == NULL) {
        printf("Failed to create priority queue object.\n");
        exit(1);
    }
    
    if (priority_queue_is_empty(hQueue)) {
        printf("The queue is empty.\n");
    }
    
    priority_queue_insert(hQueue, 10, 1);
	
    priority_queue_insert(hQueue, 20, 2);
   
    priority_queue_insert(hQueue, 80, 3);
    
    priority_queue_insert(hQueue, 50, 4);
    
    priority_queue_insert(hQåueue, 500, 9);
    
    priority_queue_insert(hQueue, 43, 8);
    // testing
    for (i = 0; i < 6; ++i) {
        printf("%d ", priority_queue_front(hQueue, NULL));
        priority_queue_service(hQueue);
    }
    printf("\n");

    priority_queue_destroy(&hQueue);
    
    return 0;
}
