#include "main.h"

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define EXECUTION_CYCLE 5 
#define TASK_FREQ SEC(1)

//= rhjr: binary semaphore =====================================================

global sem_t binairy_semaphore;

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
      sem_wait(&binairy_semaphore);

    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &deadline, NULL);

    printf("thread_one()::%u -> section 1.\n", execution_counter);

    if (execution_counter == EXECUTION_CYCLE)
    {
      execution_counter = 0;
      sem_post(&binairy_semaphore);
    }

    // rhjr: calculate next deadline
    deadline.tv_nsec += TASK_FREQ;
    deadline.tv_sec += deadline.tv_nsec / NSEC_PER_SEC;
    deadline.tv_nsec %= NSEC_PER_SEC;
    execution_counter += 1;
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
      sem_wait(&binairy_semaphore);

    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &deadline, NULL);

    printf("thread_two()::%u -> section 2.\n", execution_counter);

    if (execution_counter == EXECUTION_CYCLE)
    {
      execution_counter = 0;
      sem_post(&binairy_semaphore);
    }

    // rhjr: calculate next deadline
    deadline.tv_nsec += TASK_FREQ;
    deadline.tv_sec += deadline.tv_nsec / NSEC_PER_SEC;
    deadline.tv_nsec %= NSEC_PER_SEC;
    execution_counter += 1;
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

  sem_init(&binairy_semaphore, 0, 1);

  pthread_create(&tasks[0], &task_attribute, (void*) task_one, NULL);
  pthread_create(&tasks[1], &task_attribute, (void*) task_two, NULL);

  for (u8 n = 0; n < N_TASKS; n++)
  {
    pthread_join(tasks[n], 0);
  }

  sem_destroy(&binairy_semaphore);

  return 0;
}
