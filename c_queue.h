#ifndef C_QUEUE_H
#define C_QUEUE_H

#include "struct.h"

void enqueue(customer_t* c_queue, customer_t customer, int* queue_count);
customer_t dequeue(customer_t* c_queue, int* queue_count);
int is_empty(int* queue_count);
void free_queue(customer_t* c_queue);

#endif

