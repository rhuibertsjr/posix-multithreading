#include "main.h" 

#include <stdio.h>
#include <pthread.h>

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
  while(1)
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
  while(1)
  {
    printf("Task 4 \n");
    for (u64 m = 0, n = 0; m <= 1000; m++)
    {
      for (;n <= 10000; n++);
    }
  }
}

#define N_TASKS 4

int main(void) 
{
  pthread_t tasks[N_TASKS];
  pthread_attr_t task_attribute;

  pthread_attr_init(&task_attribute);
  
  pthread_attr_setschedpolicy(&task_attribute, SCHED_RR);

  pthread_create(&tasks[0], &task_attribute, (void*) task_one,   NULL);
  pthread_create(&tasks[1], &task_attribute, (void*) task_two,   NULL);
  pthread_create(&tasks[2], &task_attribute, (void*) task_three, NULL);
  pthread_create(&tasks[3], &task_attribute, (void*) task_four,  NULL);

  for (u8 n = 0; n < N_TASKS; n++)
  {
    pthread_join(tasks[n], 0);
  }

  return 0;
}
