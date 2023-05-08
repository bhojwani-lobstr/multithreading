#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "c_queue.h"
#include "customer.h"
#include "teller.h"
#include "struct.h"
#include "mutex.h"


/*INITIALZING THE MUTEX WITH THE DEFAULT INITIALIZER*/
pthread_mutex_t enqueue_mutex = PTHREAD_MUTEX_INITIALIZER;

/*INITIALZING THE CONDTITION WITH THE DEFAULT INITIALIZER*/
pthread_cond_t teller_cond = PTHREAD_COND_INITIALIZER;

int main(int argc, char* argv[]) {

	/*INITIALZING VARIABLES*/
	int i = 0, j = 0, k = 0;
	int queue_count = 0;
	FILE *ptr;	
	comm_args_t args;

	/*CHECKING IF ALL THE ARGUMENTS ARE PROVDIDED*/
	if (argc == 7) {
	
	/*ASSIGNING THE COMMAND-LINE ARGUMENTS TO THE A STRUCT*/
	args.cq = (argv[1]);
	args.m = atoi(argv[2]);
	args.tc = atoi(argv[3]);
	args.tw = atoi(argv[4]);
	args.td = atoi(argv[5]);
	args.ti = atoi(argv[6]);

	}

	/*IF THE C-L ARGUMENTS ARE NOT CORRECT IT RETURNS ONE*/
	else {

		/*PRINTS TO THE SCREEN TO PUT THE CORRECT NUMBER OF ARGUMENTS*/
 		printf("Incorrect Number of Arguments. Please Enter 7 Including ./executable\n");

		return 1;
	}

	/*DYNAMICALLY ALLOCATES THE QUEUE*/
	customer_t* c_queue = malloc(args.m * sizeof(customer_t));

	/*INITIALIZES THE THREADS*/
	pthread_t t1;
	pthread_t tell_t[4];

	/*INITIALIZES THE ARGUMENTS FOR TELLER AND CUSTOMER FUNCTIONS*/
	thread_cus_t cus_args;
	thread_args_t thread_args[4];

	/*INITIALIZES THE TELLERS*/
	teller_t teller_no[4] = {{1, 0}, {2, 0}, {3, 0}, {4, 0}};

	/*OPENS A FRESH R_LOG.TXT*/
	ptr = fopen("r_log.txt", "w+");

	/*ASSIGNS THE CUSTOMER FUNCTION ARGUMENTS*/
	cus_args.c_queue = c_queue;
	cus_args.queue_count = &queue_count;
	cus_args.comm_args = args;

	/*CREATES A THREAD TO RUN THE CUSTOMER FUNCTION*/
	pthread_create(&t1, NULL, customer, (void*)&cus_args);


	for (i; i < 4; i++) {


		/*ASSIGNS THE TELLER FUNCTION ARGUMENTS FOR ALL TELLERS*/
		thread_args[i].t_no = teller_no[i];
		thread_args[i].c_queue = c_queue;
		thread_args[i].queue_count = &queue_count;
		thread_args[i].comm_args = args;

		/*CREATES THREADS TO RUN ALL THE TELLER FUNCTION*/
		pthread_create(&tell_t[i], NULL, teller, (void*)&thread_args[i]);
	}

	/*JOINS THE CUSTOMER FUNCTION THREAD*/
	pthread_join(t1, NULL);
	
	for (j; j < 4; j++) {

		/*JOINS ALL THE TELLER THREADS*/
		pthread_join(tell_t[j], NULL);

	}

	/*DESTROYS THE MUTEX*/
	pthread_mutex_destroy(&enqueue_mutex);

	/*DESTORYS THE CONDITIONS*/
	pthread_cond_destroy(&teller_cond);

	/*FREES THE MEMORY FOR THE QUEUE*/
	free_queue(c_queue);

	/*CLOSES THE R_LOG.TXT FILE*/
	fclose(ptr);
	
    	return 0;
}
