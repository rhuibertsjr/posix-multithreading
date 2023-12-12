#define _GNU_SOURCE

#include "main.h" 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <time.h>

internal void * 
task_one(void)
{
  while(1)
  {
    printf("Task 1 \n");
    for (u64 m = 0, n = 0; m <= 1000; m++)
    {
      for (;n <= 10000; n++);
    }
  }
}

internal void * 
task_two(void)
{
  while(1)
  {
    printf("Task 2 \n");
    for (u64 m = 0, n = 0; m <= 1000; m++)
    {
      for (;n <= 10000; n++);
    }
  }
}

internal void * 
task_three(void)
{
  for (u64 i = 0; i <= 40; i++)
  {
    printf("Task 3 \n");
    for (u64 m = 0, n = 0; m <= 1000; m++)
    {
      for (;n <= 10000; n++);
    }
  }
}

internal void * 
task_four(void)
{
  for (u64 i = 0; i <= 40; i++)
  {
    printf("Task 4 \n");
    fflush(stdout);
    for (u64 m = 0, n = 0; m <= 1000; m++)
    {
      for (;n <= 10000; n++);
    }
  }
}

#define N_TASKS 4

int main(void) 
{
  // rhjr: run tasks on core n. 0
  cpu_set_t mask;
  CPU_ZERO(&mask);
  CPU_SET(0, &mask);

  sched_setaffinity(0, sizeof(mask), &mask);

  pthread_t tasks[N_TASKS];
  pthread_attr_t task_attribute[N_TASKS]; 

  for (u8 n = 0; n < N_TASKS; n++)
  {
    struct sched_param param;

    pthread_attr_init(&task_attribute[n]);
    pthread_attr_setschedpolicy(&task_attribute[n], SCHED_RR);
    pthread_attr_getschedparam(&task_attribute[n], &param);

    if (n > 1)
      param.sched_priority = 20;
    else
      param.sched_priority = 10;

    pthread_attr_setinheritsched(&task_attribute[n], PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedparam(&task_attribute[n], &param);
  }

  pthread_create(&tasks[0], &task_attribute[0], (void*) task_one,   NULL);
  pthread_create(&tasks[1], &task_attribute[1], (void*) task_two,   NULL);
  pthread_create(&tasks[2], &task_attribute[2], (void*) task_three, NULL);
  pthread_create(&tasks[3], &task_attribute[3], (void*) task_four,  NULL);

  for (u8 n = 0; n < N_TASKS; n++)
  {
    pthread_join(tasks[n], 0);
  }

  return 0;
}
