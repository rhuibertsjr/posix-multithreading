#include "main.h"

#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h>

#define N_TASKS 2

internal void *
task_one (void *parameters)
{
  printf("task_one()\n");

  u32 *pipe_descr = (u32*) parameters;
  u32 result;

  result = write(*pipe_descr, "Hello world", 12);

  if (result == -1)
  {
    perror("write");
    return NULL;
  }

  close(*pipe_descr);

  return NULL;
}

internal void *
task_two (void *parameters)
{
  printf("task_two()\n");

  u32 *pipe_descr = (u32*) parameters;
  char buffer[256];
  u32 result;

  result = read(*pipe_descr, buffer, sizeof(buffer));

  if (result == -1)
  {
    perror("read");
    return NULL;
  }

  close(*pipe_descr);

  printf("%s\n", buffer);

  return NULL;
}

int main(void) 
{
  pthread_t tasks[N_TASKS];

  u32 pipe_descr[2];
  u32 result;

  result = pipe(pipe_descr);

  if (result == -1)
  {
    perror("pipe");
    return 0;
  }

  pthread_create(
    &tasks[0], NULL, (void*) task_one, (void*) &pipe_descr[0]);
  pthread_create(
    &tasks[1], NULL, (void*) task_two, (void*) &pipe_descr[1]);

  for (u8 n = 0; n < N_TASKS; n++)
  {
    pthread_join(tasks[n], 0);
  }

  return 0;
}



