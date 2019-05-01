#ifndef SERVICE_ADHOC_THREADS_H
#define SERVICE_ADHOC_THREADS_H

#include <iostream>
#include <pthread.h>
#include <cstdbool>
#include <cstdint>
#include "dbg.h"

#define MAX_THREADS_NO 2
#define MAX_CHAR 32

typedef enum {
    HIGH,
    LOW
} PRIORITY;

typedef struct {
    pthread_attr_t attr;
    char name[MAX_CHAR];
    uint8_t tid;
} THREAD_INFO;

typedef struct {
    THREAD_INFO thread_info;
    bool status;
} THREAD_DATA;

extern pthread_t threads[MAX_THREADS_NO];
extern THREAD_DATA threads_data[MAX_THREADS_NO];


void set_thread_data(long tid, const char* name);
void create_default_thread(THREAD_DATA* thread_data, void* (*thread_task)(void*), PRIORITY priority);
void free_thread_stuff();

#endif //SERVICE_ADHOC_THREADS_H
