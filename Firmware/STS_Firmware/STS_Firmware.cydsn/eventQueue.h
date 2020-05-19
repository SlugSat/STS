#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include <stdlib.h>
#include <stdbool.h>

#define MAX_QUEUE_SIZE 12
    
// Event Type List
typedef enum event_t{
    NO_EVENT,
    UP_CLICK,
    DOWN_CLICK,
    SELECT_CLICK,
    HAMMER_LIFTED,
    HAMMER_DROPPED,
}event_t;

// Pointer to Event Queue Structure
typedef struct EventQueue_t * EventQueuePtr_t;

// Public Function Prototypes
bool EventQueue_New(EventQueuePtr_t eq);
bool EventQueue_Enqueue(EventQueuePtr_t eq, event_t e);
event_t EventQueue_Dequeue(EventQueuePtr_t eq);
bool EventQueue_IsEmpty(EventQueuePtr_t eq);
int EventQueue_Size(EventQueuePtr_t eq);
bool EventQueue_Clear(EventQueuePtr_t eq);
bool EventQueue_Free(EventQueuePtr_t eq);


#endif /* EVENT_QUEUE_H */