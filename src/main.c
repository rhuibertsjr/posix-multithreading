#include "main.h" 

#include <stdio.h>
#include <pthread.h>

void * 
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

void * 
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

void * 
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
void * 
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

int main(void) 
{


  return 0;
}
