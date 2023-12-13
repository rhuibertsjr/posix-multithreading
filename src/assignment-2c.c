#include "main.h"

#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <pthread.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define N 50

internal void *
task_one (void *parameters)
{
  printf("task_one()\n");

  i64 *memory = (i64*) parameters;  
  i64 data[N];

  for (u8 i = 0; i < N; i++)
    data[i] = i + 1;

  // rhjr: test
  data[20] = 99;

  memcpy(memory, data, sizeof(i64) * N);

  return NULL;
}

internal void *
task_two (void *parameters)
{
  printf("task_two()\n");

  i64 *memory = (i64*) parameters;  

  while(1)
  {
    if (*memory != 1)
      continue;

    printf("Values send -> ");
    for (u8 i = 0; i < N; i++)
      printf("%d ", *memory++);

    printf("\n");
    break;
  }

  return NULL;
}

#define N_TASKS 2

int main(void) 
{
  pthread_t tasks[N_TASKS];

  // rhjr: create shared memory
  u64 shm_descr = shm_open("/memory", O_CREAT | O_RDWR, (mode_t) 0666);
  ftruncate(shm_descr, sizeof(i64) * N);

  i64 *shm = // rhjr: map into current address space.
    (i64*) mmap(
      NULL, sizeof(i64) * N, PROT_READ | PROT_WRITE, MAP_SHARED, shm_descr, 0);

  memset(shm, 0, sizeof(i64) * N);

  pthread_create(
    &tasks[0], NULL, (void*) task_one, (void*) shm);
  pthread_create(
    &tasks[1], NULL, (void*) task_two, (void*) shm);

  for (u8 n = 0; n < N_TASKS; n++)
  {
    pthread_join(tasks[n], 0);
  }

  // rhjr: free shared memory
  munmap(shm, sizeof(i64) * N);
  close(shm_descr);

  return 0;
}



