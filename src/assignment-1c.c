#define _GNU_SOURCE

#include "main.h" 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sched.h>
#include <time.h>

typedef void* (*tasks_func)(void);

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

  tasks_func tasks_functions[N_TASKS] = {
    task_one, task_two, task_three, task_four };

  for (u8 n = 4; n != 0; n--)
  {
    struct sched_param param;

    pthread_attr_init(&task_attribute[n]);

    pthread_attr_setschedpolicy(&task_attribute[n], SCHED_RR);
    pthread_attr_getschedparam(&task_attribute[n], &param);

    if (n > 2)
      param.sched_priority = 150;
    else
      param.sched_priority = 10;

    printf("Task %u priority -> %u\n", n, param.sched_priority);

    pthread_attr_setinheritsched(&task_attribute[n], PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedparam(&task_attribute[n], &param);

    u32 result = 
      pthread_create(&tasks[n], &task_attribute[n], (void*) tasks_functions[n], NULL);

    if (result)
    {
      printf("ERROR: pthread_create() -> %s\n", strerror(result));
    }
  }

  for (u8 n = 0; n < N_TASKS; n++)
  {
    pthread_join(tasks[n], 0);
  }

  return 0;
}
