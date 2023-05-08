#ifndef CUSTOMER_H
#define CUSTOMER_H

#define LENGTH_OF_QUEUE 4 
#define TC_SECONDS 5

#include <time.h>

typedef struct{
        char* cq;
        int m;
        int tc;
        int tw;
        int td;
        int ti;
} comm_args_t;

typedef struct {
        int teller_id;
        int customer_count;
} teller_t;


typedef struct {
    int customer_number;
    char service_type;
    struct tm arrival_time;
} customer_t;

typedef struct {
    customer_t* c_queue;
    int* queue_count;
    comm_args_t comm_args;
} thread_cus_t;

typedef struct {
        teller_t t_no;
        customer_t* c_queue;
        int* queue_count;
    	comm_args_t comm_args;
} thread_args_t;

#endif
