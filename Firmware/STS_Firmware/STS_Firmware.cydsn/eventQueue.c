/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

//#include "eventQueue.h"

#define RUN_TEST_HARNESS

struct Node{
    event_t event;
    struct Node * next;
};

struct EventQueue_t{
    int size;
    struct Node * head;
    struct Node * tail;
};

EventQueuePtr_t EventQueue_New(void){
    EventQueuePtr_t eq = malloc(sizeof(struct EventQueue_t));

    // Check for malloc success
    if(eq == NULL){
        return false;
    }

    // Initialize struct members
    eq->size = 0;
    eq->head = NULL;
    eq->tail = NULL;

    return eq;
}

bool EventQueue_Enqueue(EventQueuePtr_t eq, event_t e){
    // Check for NULL pointer
    if(eq == NULL){
        return false;
    }

    // Check queue size limit
    if(eq->size >= MAX_QUEUE_SIZE){
        return false;
    }

    // Create new Node and store event
    struct Node * temp = malloc(sizeof(struct Node));
    temp->event = e;
    temp->next = NULL;

    // If queue is empty, add to head
    if(eq->tail == NULL){
        eq->head = eq->tail = temp;
    }

    // Insert node at tail
    eq->tail->next = temp;
    eq->tail = temp;

    // Increment Queue Size
    eq->size++;

    return true;
}

event_t EventQueue_Dequeue(EventQueuePtr_t eq){
    // Check for NULL pointer
    if(eq == NULL){
        return NO_EVENT;
    }

    // Check for empty list
    if(eq->head == NULL){
        return NO_EVENT;
    }

    // Create temp node
    struct Node * temp = eq->head;
    event_t retVal = eq->head->event;

    // Move head to next event in queue
    eq->head = eq->head->next;

    // If list is empty set tail to NULL
    if(eq->head == NULL){
        eq->tail = NULL;
    }

    // Free node and decrement list size
    free(temp);
    eq->size--;

    return retVal;
}

bool EventQueue_IsEmpty(EventQueuePtr_t eq){
    // Check for NULL pointer
    if(eq == NULL){
        return true;
    }
    return (eq->size == 0);
}

int EventQueue_Size(EventQueuePtr_t eq){
    // Check for NULL pointer
    if(eq == NULL){
        return -1;
    }
    return eq->size;
}

bool EventQueue_Clear(EventQueuePtr_t eq){
    // Check for NULL pointer
    if(eq == NULL){
        return false;
    }

    // Dequeue until no events in queue
    while(!EventQueue_IsEmpty(eq)){
        EventQueue_Dequeue(eq);
    }

    return true;
}

bool EventQueue_Free(EventQueuePtr_t eq){
    // Check for NULL pointer
    if(eq == NULL){
        return false;
    }

    // Empty queue
    EventQueue_Clear(eq);

    // Free memory
    free(eq);
    return true;
}

// --- Test Harness ---
#ifdef RUN_TEST_HARNESS
#include <stdio.h>

int main(){

    printf("eventQueue.c Test Harness\n");

    printf("Creating new event queue...\n");
    EventQueuePtr_t eventQueue = EventQueue_New();
    printf("%s\n", (eventQueue != NULL) ? "Success" : "Failure");


    EventQueue_Enqueue(eventQueue, UP_CLICK);
    printf("Enqueued Event: UP_CLICK\n");
    EventQueue_Enqueue(eventQueue, DOWN_CLICK);
    printf("Enqueued Event: DOWN_CLICK\n");
    EventQueue_Enqueue(eventQueue, SELECT_CLICK);
    printf("Enqueued Event: SELECT_CLICK\n");
    printf("Checking size...\n");
    printf("Expected: 3 Returned: %i\n",EventQueue_Size(eventQueue));
    printf("Dequeuing UP_CLICK event...\n");
    printf("%s\n", (EventQueue_Dequeue(eventQueue) == UP_CLICK) ? "Success" : "Failure");
    printf("Dequeuing DOWN_CLICK event...\n");
    printf("%s\n", (EventQueue_Dequeue(eventQueue) == DOWN_CLICK) ? "Success" : "Failure");
    printf("Dequeuing SELECT_CLICK event...\n");
    printf("%s\n", (EventQueue_Dequeue(eventQueue) == SELECT_CLICK) ? "Success" : "Failure");
    printf("Checking for empty queue...\n");
    printf("Expected: Empty Returned: %s\n",EventQueue_IsEmpty(eventQueue) ? "Empty" : "Not Empty");
    printf("Enqueuing 4 Events: SELECT_CLICK\n");
    EventQueue_Enqueue(eventQueue, SELECT_CLICK);
    EventQueue_Enqueue(eventQueue, SELECT_CLICK);
    EventQueue_Enqueue(eventQueue, SELECT_CLICK);
    EventQueue_Enqueue(eventQueue, SELECT_CLICK);
    printf("Clearing queue...\n");
     printf("%s\n", EventQueue_Clear(eventQueue) ? "Success" : "Failure");
    printf("Checking for empty queue...\n");
    printf("Expected: Empty Returned: %s\n",EventQueue_IsEmpty(eventQueue) ? "Empty" : "Not Empty");
    printf("Freeing event queue...\n");
    printf("%s\n", EventQueue_Free(eventQueue) ? "Success" : "Failure");

    return EXIT_SUCCESS;
}
#endif

/* [] END OF FILE */
