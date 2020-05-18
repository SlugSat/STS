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

#include "eventQueue.h"

struct Node{
    event_t event;
    struct Node * next;
};

struct EventQueue_t{
    int size;
    struct Node * head;
    struct Node * tail;
};

bool EventQueue_New(EventQueuePtr_t eq){
    eq = malloc(sizeof(struct EventQueue_t));
    
    if(eq == NULL){
        return false;
    }
    
    eq->size = 0;
    eq->head = NULL;
    eq->tail = NULL;
    
    return true;
}

bool EventQueue_Enqueue(EventQueuePtr_t eq, event_t e);
//TO-DO

event_t EventQueue_Dequeue(EventQueuePtr_t eq);
//TO-DO

bool EventQueue_IsEmpty(EventQueuePtr_t eq){
    if(eq == NULL){
        return true;
    }
    return (eq->size == 0);
}

bool EventQueue_Free(EventQueuePtr_t * eq){
    if(eq == NULL){
        return false;
    }
    
    //TO-DO
    
    return true;
}

/* [] END OF FILE */
