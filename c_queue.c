#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "customer.h"
#include "struct.h"

/*TAKES THE QUEUE, THE ELEMENT AND THE QUEUE COUNT AS ARGUMENTS*/
void enqueue(customer_t* c_queue, customer_t customer, int* queue_count) {

	/*ASSIGNS THE ELEMENT VALUES TO THE QUEUE*/
	c_queue[*queue_count].customer_number = customer.customer_number;
	c_queue[*queue_count].service_type = customer.service_type;
	
	/*CONTROL ZONE*/
	/*SAVING THE ARRIVAL TIME INTO MEMORY*/
	time_t t;
	t = time(NULL);
	struct tm* date = localtime(&t);
	
	memcpy(&(c_queue[*queue_count].arrival_time), date, sizeof(struct tm));
	/*CONTROL ZONE*/

	/*INCREMENTING THE QUEUE COUNT*/
	(*queue_count)++;
}

/*TAKES THE QUEUE AND THE QUEUE COUNT AS AN ARGUMENT AND RETURNS THE ELEMENT WITH TYPE CUSTOMER_T*/
customer_t dequeue(customer_t* c_queue, int* queue_count) {

	/*DOES NOT TRY TO REMOVE AN ELEMENT FROM THE QUEUE IF IT IS ALREADY EMPTY*/
	if (*queue_count == 0) {
        	fprintf(stderr, "Queue is Empty\n");
        	return (customer_t) {0, 0};
    	}

	/*SAVES THE FIRST ELEMENT IN THE QUEUE IN A VARIABLE*/
    	customer_t res = c_queue[0];

    	/*LOOP VARIABLE*/
	int i;

	/*SHIFTS EVERYTHING ONE SPACE TO THE LEFT, GETTING RID OF THE FIRST ELEMENT IN THE QUEUE*/
    	for (i = 0; i < *queue_count - 1; i++) {
        	c_queue[i] = c_queue[i + 1];
    	}

	/*DECREMENTING THE QUEUE*/
    	(*queue_count)--;

	/*RETURNS THE REMOVED ELEMENT*/
    	return res;
}

/*TAKES IN QUEUE COUNT AS AN ARGUMENT*/
int is_empty(int* queue_count) {

	/*CHECKS IF QUEUE COUNT IS EMPTY*/
	return *queue_count == 0;
}

/*FREE THE DYNAMICALLY ALLOCATED MEMORY*/
void free_queue(customer_t* c_queue) {
	
	/*FREES THE QUEUE*/
	free(c_queue);
}
