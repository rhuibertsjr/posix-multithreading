#include "main.h"

#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define TASK_ONE_FREQ 1300000000
#define TASK_TWO_FREQ 500000000
#define NSEC_PER_SEC 1000000000

internal void *
task_one (void)
{
  struct timespec deadline; 
  clock_gettime(CLOCK_MONOTONIC, &deadline);

  while(1)
  {
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &deadline, NULL);

    printf("thread_one() -> %u\n", TASK_ONE_FREQ);

    // rhjr: calculate next deadline
    deadline.tv_nsec += TASK_ONE_FREQ;
    deadline.tv_sec += deadline.tv_nsec / NSEC_PER_SEC;
    deadline.tv_nsec %= NSEC_PER_SEC;
  }
}

internal void *
task_two (void)
{
  struct timespec deadline; 
  clock_gettime(CLOCK_MONOTONIC, &deadline);

  while(1)
  {
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &deadline, NULL);

    printf("thread_two() -> %u\n", TASK_TWO_FREQ);

    // rhjr: calculate next deadline
    deadline.tv_nsec += TASK_TWO_FREQ;
    deadline.tv_sec += deadline.tv_nsec / NSEC_PER_SEC;
    deadline.tv_nsec %= NSEC_PER_SEC;
  }
}

#define N_TASKS 2

int main(void)
{
  pthread_t tasks[N_TASKS];
  pthread_attr_t task_attribute;

  pthread_attr_init(&task_attribute);
  pthread_attr_setschedpolicy(&task_attribute, SCHED_RR);

  pthread_create(&tasks[0], &task_attribute, (void*) task_one, NULL);
  pthread_create(&tasks[1], &task_attribute, (void*) task_two, NULL);

  for (u8 n = 0; n < N_TASKS; n++)
  {
    pthread_join(tasks[n], 0);
  }

  return 0;
}
