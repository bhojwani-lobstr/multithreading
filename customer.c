#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "customer.h"
#include "c_queue.h"
#include "mutex.h"
	
void* customer(void* arg) {

	/*Assigns the Received Paramters to the Struct named thread_args*/
        thread_cus_t* thread_args = (thread_cus_t*) arg;

        /*creates a variable t_no with datatype teller_t and assigns it the value of t_no in the thread args*/
        customer_t* c_queue = thread_args->c_queue;

        /*creates a pointer to queue_count with datatype and assigns it the value of pointer to queue_count in the thread args*/
        int* queue_count = thread_args->queue_count;

	/*Exporting the struct with command line arguments*/
	comm_args_t comm_args = thread_args->comm_args;

	/*Initialzing Variables*/
        FILE *fp;
        FILE *fp2;
        int temp_num;
        char temp_type;
        customer_t temp_cus;
	time_t t;

	/*Opening the file in reading mode*/
        fp = fopen(comm_args.cq, "r");

	/*Error checking for if file exists or not*/
        if (fp == NULL) {
                printf("Error opening file\n");
                return NULL;
        }

	sleep(1);
	
	/*CHECKING IF QUEUE IS FULL AND GETTING THE CUSTOMER# AND SERVICE TYPE FROM THE FILE*/
	while (*queue_count < comm_args.m && fscanf(fp, "%d %c", &temp_num, &temp_type) != EOF) {

        	/*ASSIGNING THE VALUES GOTTEN FROM THE FILE TO THE TEMPORARY CUSTOMER*/
		temp_cus.customer_number = temp_num;
	        temp_cus.service_type = temp_type;

		/*GETTING THE START TIME FOR THE TELLER*/
	        t = time(NULL);
	        struct tm date = *localtime(&t);
		temp_cus.arrival_time = date;

		/*LOCKING THE QUEUE*/
		pthread_mutex_lock(&enqueue_mutex);

		/*PUTTING THE CUSTOMER EXTRACTED FROM THE FILE INTO THE QUEUE*/
	       	enqueue(c_queue, temp_cus, queue_count);

		/*UNLOCKING THE QUEUE*/
		pthread_mutex_unlock(&enqueue_mutex);

		/*WAITS tc BEFORE GETTING THE NEXT CUSTOMER*/
	        sleep(comm_args.tc);

		/*PRINT STATEMENT FOR TESTING PURPOSES TO CHECK IF THE CUSTOMER HAS BEEN ENQUEUED*/
	        printf("Customer#: %d Has Entered The Queue\n", temp_num);

		/*LOCKING THE FILE FOR WRITING*/
		pthread_mutex_lock(&enqueue_mutex);

		/*OPENING THE FILE FOR APPENDING*/
        	fp2 = fopen("r_log.txt", "a+");

		/*WRITING TO THE FILE ACCORDING THE ASSIGNMENT SPECIFICATIONS*/
        	fprintf(fp2, "---------------------------------------\n");
	        fprintf(fp2, "Customer#: %d Service Type: %c\n", temp_num, temp_type);
	        fprintf(fp2, "Arrival Time: %02d:%02d:%02d\n", date.tm_hour, date.tm_min, date.tm_sec);
	        fprintf(fp2, "---------------------------------------\n\n");

		/*CLOSING THE FILE, SO OTHER THREADS CAN OPEN AND WRITE AGAIN SAFELY*/
        	fclose(fp2);

		/*UNLOCKING THE FILE*/
		pthread_mutex_unlock(&enqueue_mutex);

		/*SIGNALLING THE TELLERS TO WAKE-UP*/
		pthread_cond_signal(&teller_cond);
		
		
	    }

	/*CLOSES THE FILE WITH CUSTOMER INFORMATION*/
        fclose(fp);

	return NULL;
}
