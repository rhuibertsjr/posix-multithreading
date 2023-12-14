#include "main.h"

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define EXECUTION_CYCLE 5 
#define TASK_FREQ SEC(1)

//= rhjr: binary semaphore =====================================================

global pthread_mutex_t mutex;

internal void *
task_one ()
{
  printf("task_one()\n");

  u32 execution_counter = 0;
  struct timespec deadline; 

  clock_gettime(CLOCK_MONOTONIC, &deadline);

  while(1)
  {
    if (execution_counter == 0)
    {
      pthread_mutex_lock(&mutex);
      printf("\n");
    }

    printf("thread_one()::%u -> section 1.\n", execution_counter + 1);

    execution_counter += 1;

    if (execution_counter == EXECUTION_CYCLE)
    {
      execution_counter = 0;
      pthread_mutex_unlock(&mutex);
    }

    // rhjr: calculate next deadline
    deadline.tv_nsec += TASK_FREQ;
    deadline.tv_sec += deadline.tv_nsec / NSEC_PER_SEC;
    deadline.tv_nsec %= NSEC_PER_SEC;

    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &deadline, NULL);
  }

  return NULL;
}

internal void *
task_two ()
{
  printf("task_two()\n");

  u32 execution_counter = 0;
  struct timespec deadline; 

  clock_gettime(CLOCK_MONOTONIC, &deadline);

  while(1)
  {
    if (execution_counter == 0)
    {
      pthread_mutex_lock(&mutex);
      printf("\n");
    }

    printf("thread_two()::%u -> section 2.\n", execution_counter + 1);

    execution_counter += 1;

    if (execution_counter == EXECUTION_CYCLE)
    {
      execution_counter = 0;
      pthread_mutex_unlock(&mutex);
    }

    // rhjr: calculate next deadline
    deadline.tv_nsec += TASK_FREQ;
    deadline.tv_sec += deadline.tv_nsec / NSEC_PER_SEC;
    deadline.tv_nsec %= NSEC_PER_SEC;

    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &deadline, NULL);
  }

  return NULL;
}

#define N_TASKS 2

int main(void)
{
  pthread_t tasks[N_TASKS];
  pthread_attr_t task_attribute;

  pthread_attr_init(&task_attribute);
  
  pthread_attr_setschedpolicy(&task_attribute, SCHED_RR);

  pthread_mutex_init(&mutex, NULL);

  pthread_create(&tasks[0], &task_attribute, (void*) task_one, NULL);
  pthread_create(&tasks[1], &task_attribute, (void*) task_two, NULL);

  for (u8 n = 0; n < N_TASKS; n++)
  {
    pthread_join(tasks[n], 0);
  }

  sem_destroy(&binairy_semaphore);

  return 0;
}
