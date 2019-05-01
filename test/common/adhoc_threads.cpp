#include "adhoc_threads.h"

pthread_t threads[MAX_THREADS_NO];
THREAD_DATA threads_data[MAX_THREADS_NO];

void set_thread_data(long tid, const char* name)
{
    check(tid < MAX_THREADS_NO, "tid = %ld exceeds the maximum allowed number of threads.", tid)
    threads_data[tid].thread_info.tid = tid;
    strncpy(threads_data[tid].thread_info.name,name, sizeof (threads_data[tid].thread_info.name));
    threads_data[tid].thread_info.name[sizeof (threads_data[tid].thread_info.name) - 1] = '\0';
    pthread_attr_init(&threads_data[tid].thread_info.attr); // initialize attribute object

    // set detach state to joinable
    pthread_attr_setdetachstate(&threads_data[tid].thread_info.attr, PTHREAD_CREATE_JOINABLE);
}

void create_default_thread(THREAD_DATA* thread_data, void* (*thread_task)(void*), PRIORITY priority)
{
    int rc;
    int fifo_max_prio, fifo_min_prio;
    struct sched_param fifo_param{};

  std::cout << "Creating thread (" << thread_data->thread_info.name << ")" << std::endl;

    fifo_max_prio = sched_get_priority_max(SCHED_FIFO);
    fifo_min_prio = sched_get_priority_min(SCHED_FIFO);

    pthread_attr_setinheritsched(&thread_data->thread_info.attr, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedparam(&thread_data->thread_info.attr, &fifo_param);

    if (priority == HIGH) {
        fifo_param.sched_priority = fifo_max_prio;
    } else {
        fifo_param.sched_priority = fifo_min_prio;
    }

    rc = pthread_create(&threads[thread_data->thread_info.tid], &thread_data->thread_info.attr, thread_task, (void *) thread_data);
    check(rc == 0, "Could not create thread %s.", thread_data->thread_info.name)
}


void free_thread_stuff()
{
    std::cout << "Freeing thread attr thingy" << std::endl;
    for(int i=0; i < MAX_THREADS_NO; ++i){
        pthread_attr_destroy(&threads_data[i].thread_info.attr); // free pthread library resources reserved for attribute object
    }
}
