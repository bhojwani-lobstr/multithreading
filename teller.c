#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"
#include "c_queue.h"
#include "teller.h"
#include "mutex.h"

#define WAIT_BF_TERM 5

void* teller(void* arg) {

	/*Assigns the Received Paramters to the Struct named thread_args*/
	thread_args_t* thread_args = (thread_args_t*) arg;

	/*creates a variable t_no with datatype teller_t and assigns it the value of t_no in the thread args*/
	teller_t t_no = thread_args->t_no;

	/*creates a c_queue with datatype customer_t pointers and assigns it the value of c_queue in the thread args*/
	customer_t* c_queue = thread_args->c_queue;

	/*creates a pointer to queue_count with datatype and assigns it the value of pointer to queue_count in the thread args*/
	int* queue_count = thread_args->queue_count;

	/*EXPORTS THE COMMAND LINE ARGUMENTS FROM THE MAIN FUNCTION AND ASSIGNS THEM TO LOCAL VARIABLES*/
        comm_args_t comm_args = thread_args->comm_args;
	
	/* File Intialzer*/
	FILE *fp;

	/*GETTING THE START TIME FOR TELLER*/
	time_t t1 = time(NULL);
	struct tm start_time = *localtime(&t1);
	
	/*INITIALIZING VARIABLE TO STORE THE DEQUEUED CUSTOMERS*/
	customer_t serve_customer;
	
	/*LOCKING THE QUEUE*/
	pthread_mutex_lock(&enqueue_mutex);

	/*CHECKS IF QUEUE IS EMPTY*/
	while (is_empty(queue_count)) {

		/*PRINTS TELLER# AND WAITING FOR CUSTOMER FOR TESTING PURPOSES*/
		printf("Teller# %d is waiting for customer\n", t_no.teller_id);

		/*WAITS FOR SIGNAL TO WAKE AND UNLOCKS THE ENQUEUE_MUTEX*/
		pthread_cond_wait(&teller_cond, &enqueue_mutex);
	}
	
	/*CHECKS IF THERE IS ATLEAST ONE CUSTOMER IN THE QUEUE*/
	while (!is_empty(queue_count)) {

		/*TAKES A CUSTOMER FROM THE QUEUE*/
		serve_customer = dequeue(c_queue, queue_count);

		/*PRINTS THE TELLER3 AND CUSTOMER3 ON SCREEN FOR TESTING PURPOSES*/
		printf("Teller# %d is serving customer# %d\n", t_no.teller_id, serve_customer.customer_number);

		/*UNLOCKS THE QUEUE*/
		pthread_mutex_unlock(&enqueue_mutex);

		/*GETS THE RESPONSE TIME*/
		time_t t = time(NULL);
		struct tm response_time = *localtime(&t);

		/*LOCKS THE R_LOG.TXT FOR APPENDING*/
		pthread_mutex_lock(&enqueue_mutex);

		/*OPENS THE FILE APPENDING*/
		fp = fopen("r_log.txt", "a+");

		/*WRITES TO THE FILE AS SPECIFED IN THE ASSIGNMENT SPECIFICATION*/
                fprintf(fp, "Teller: %d\n", t_no.teller_id);
		fprintf(fp, "Customer: %d\n", serve_customer.customer_number);
		fprintf(fp, "Arrival Time: %02d:%02d:%02d\n", serve_customer.arrival_time.tm_hour, serve_customer.arrival_time.tm_min, serve_customer.arrival_time.tm_sec); 
		fprintf(fp, "Response Time: %02d:%02d:%02d\n\n", response_time.tm_hour, response_time.tm_min, response_time.tm_sec);

		/*CLOSES THE FILE, SO OTHER THREADS CAN WRITE TO THE FILE*/
		fclose(fp);

		/*UNLOCKS THE R_LOG.TXT FILE*/
		pthread_mutex_unlock(&enqueue_mutex);

		/*CHECKS WHICH SERVICE TYPE THE CUSTOMER HAS*/
		if (serve_customer.service_type == 'D'){

			/*SLEEPS FOR A CERTAIN PEROID OF TIME ACCORDING TO THE COMMAND LINE ARGUMENT GIVEN*/
			sleep(comm_args.td);

			/*GETS THE COMPLETITION TIME*/
			time_t t = time(NULL);
			struct tm completion_time = *localtime(&t);

			/*LOCKS THE FILE FOR APPENDING*/
			pthread_mutex_lock(&enqueue_mutex);

			/*OPENS THE FILE FOR APPENDING*/
			fp = fopen("r_log.txt", "a+");

			
			/*WRITES TO THE FILE AS SPECIFED IN THE ASSIGNMENT SPECIFICATION*/
                	fprintf(fp, "Teller: %d\n", t_no.teller_id);
			fprintf(fp, "Customer: %d\n", serve_customer.customer_number);
			fprintf(fp, "Arrival Time: %02d:%02d:%02d\n", serve_customer.arrival_time.tm_hour, serve_customer.arrival_time.tm_min, serve_customer.arrival_time.tm_sec); 
			fprintf(fp, "Completeion Time: %02d:%02d:%02d\n\n", completion_time.tm_hour, completion_time.tm_min, completion_time.tm_sec);


			/*CLOSES THE FILE, SO OTHER THREADS CAN WRITE TO THE FILE*/
			fclose(fp);


			/*UNLOCKS THE R_LOG.TXT FILE*/
			pthread_mutex_unlock(&enqueue_mutex);

		}

		/*CHECKS WHICH SERVICE TYPE THE CUSTOMER HAS*/
		else if (serve_customer.service_type == 'W'){

			/*SLEEPS FOR A CERTAIN PEROID OF TIME ACCORDING TO THE COMMAND LINE ARGUMENT GIVEN*/
			sleep(comm_args.tw);

			/*GETS THE COMPLETITION TIME*/
			time_t t = time(NULL);
			struct tm completion_time = *localtime(&t);

			/*LOCKS THE FILE FOR APPENDING*/
			pthread_mutex_lock(&enqueue_mutex);

			/*OPENS THE FILE FOR APPENDING*/
			fp = fopen("r_log.txt", "a+");

			/*WRITES TO THE FILE AS SPECIFED IN THE ASSIGNMENT SPECIFICATION*/
                	fprintf(fp, "Teller: %d\n", t_no.teller_id);
			fprintf(fp, "Customer: %d\n", serve_customer.customer_number);
			fprintf(fp, "Arrival Time: %02d:%02d:%02d\n", serve_customer.arrival_time.tm_hour, serve_customer.arrival_time.tm_min, serve_customer.arrival_time.tm_sec); 
			fprintf(fp, "Completeion Time: %02d:%02d:%02d\n\n", completion_time.tm_hour, completion_time.tm_min, completion_time.tm_sec);

			/*CLOSES THE FILE, SO OTHER THREADS CAN WRITE TO THE FILE*/
			fclose(fp);

			/*UNLOCKS THE R_LOG.TXT FILE*/
			pthread_mutex_unlock(&enqueue_mutex);

		}

		/*CHECKS WHICH SERVICE TYPE THE CUSTOMER HAS*/
		else if (serve_customer.service_type == 'I'){

			/*SLEEPS FOR A CERTAIN PEROID OF TIME ACCORDING TO THE COMMAND LINE ARGUMENT GIVEN*/
			sleep(comm_args.ti);

			/*GETS THE COMPLETITION TIME*/
			time_t t = time(NULL);
			struct tm completion_time = *localtime(&t);

			/*LOCKS THE FILE FOR APPENDING*/
			pthread_mutex_lock(&enqueue_mutex);

			/*OPENS THE FILE FOR APPENDING*/
			fp = fopen("r_log.txt", "a+");

			/*WRITES TO THE FILE AS SPECIFED IN THE ASSIGNMENT SPECIFICATION*/
                	fprintf(fp, "Teller: %d\n", t_no.teller_id);
			fprintf(fp, "Customer: %d\n", serve_customer.customer_number);
			fprintf(fp, "Arrival Time: %02d:%02d:%02d\n", serve_customer.arrival_time.tm_hour, serve_customer.arrival_time.tm_min, serve_customer.arrival_time.tm_sec); 
			fprintf(fp, "Completeion Time: %02d:%02d:%02d\n\n", completion_time.tm_hour, completion_time.tm_min, completion_time.tm_sec);

			/*CLOSES THE FILE, SO OTHER THREADS CAN WRITE TO THE FILE*/
			fclose(fp);

			/*UNLOCKS THE R_LOG.TXT FILE*/
			pthread_mutex_unlock(&enqueue_mutex);

		}

		/*INCREMENTS THE NUMBER OF CUSTOMER SERVED*/
		t_no.customer_count ++;

		/*SLEEPS FOR WAIT_BF_TERM TIME DEFINED AT THE TOP OF THIS FILE TO MAKE SURE NO CUSTOMER ENTERS THE QUEUE BEFORE IT TERMINATES*/
		/*NOTE THAT IF tc IS GREATER THAN THE VALUE OF WAIT_BF_TERM, INCREASE THE VALUE OF WAIT_BF_TERM*/
		sleep(WAIT_BF_TERM);
	}
	
	/*PRINTS THE TELLER# AND TERMINATION TIME FOR TESTING PURPOSES*/
	printf("Teller# %d Has Terminated\n", t_no.teller_id);

	/*GETS THE TERMINATION TIME*/
	time_t t = time(NULL);
	struct tm termination_time = *localtime(&t);

	/*LOCKS THE FILE FOR APPENDING*/
	pthread_mutex_lock(&enqueue_mutex);

	/*OPENS THE FILE FOR APPENDING*/
	fp = fopen("r_log.txt", "a+");

	/*WRITES TO THE FILE AS SPECIFED IN THE ASSIGNMENT SPECIFICATION*/
	fprintf(fp, "Termination Teller-%d\n",t_no.teller_id);
	fprintf(fp, "#Served Customers: %d\n", t_no.customer_count);
	fprintf(fp, "Start Time: %02d:%02d:%02d\n", start_time.tm_hour, start_time.tm_min, start_time.tm_sec); 
	fprintf(fp, "Termination Time: %02d:%02d:%02d\n\n", termination_time.tm_hour, termination_time.tm_min, termination_time.tm_sec);

	/*CUSTOMER SERVED COUNT*/
	fprintf(fp, "Teller Statistic\nTeller-%d serves %d customers.",t_no.teller_id, t_no.customer_count);


	/*CLOSES THE FILE, SO OTHER THREADS CAN WRITE TO THE FILE*/
	fclose(fp);

	/*UNLOCKS THE R_LOG.TXT FILE*/
	pthread_mutex_unlock(&enqueue_mutex);

}
