#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

extern pthread_mutex_t enqueue_mutex;
extern pthread_cond_t teller_cond;

#endif

