#include "main.h"

#include <stdio.h>
#include <math.h>

#include <pthread.h>
#include <mqueue.h>

#define N 50

typedef struct ThreadParams ThreadParams;
struct ThreadParams
{
  mqd_t mailbox_descriptor;
};

internal void *
task_one(void* parameters)
{
  printf("Thread 1"); 

  ThreadParams *params = (ThreadParams*) parameters;
  r32 sine_approx[N];

  for (u8 i = 0; i < N; i++)
  {
    sine_approx[i] = sinf(i * M_PI / 180.0);
  }

  u32 result = mq_send(params->mailbox_descriptor, (const char*) sine_approx, N, 0);

  if (result == -1)
  {
    printf("Failed sending sine approximation.\n");
  }

  return NULL;
}

internal void *
task_two(void *parameters)
{
  printf("Thread 2"); 

  ThreadParams *params = (ThreadParams*) parameters;
  r32 mailbox[N];

  while (1)
  {
    // rhjr: block until it receives mail.
    uint32_t result = mq_receive(params->mailbox_descriptor, (char*) mailbox, N, NULL);

    if (result != -1)
    {
      printf("Sine -> ");
      for (uint8_t i = 0; i < N; i++)
      {
        printf("%u ", mailbox[i]);
      }
      printf("\n");
    }
  }

  return NULL;
}

#define N_TASKS 2

int main(void) 
{
  pthread_t tasks[N_TASKS];
  pthread_attr_t task_attribute;

  pthread_attr_init(&task_attribute);

  struct mq_attr mailbox_attri = {
    .mq_flags   = 0,
    .mq_maxmsg  = N, 
    .mq_msgsize = sizeof(r32) * N,
    .mq_curmsgs = 0 
  };

  mqd_t mailbox = mq_open("/mailbox", O_CREAT | O_RDWR, (mode_t) 0777, &mailbox_attri);

  if (mailbox == -1)
  {
    perror("mq_open");
    return 0;
  }

  ThreadParams params = {
    .mailbox_descriptor = mailbox
  };

  pthread_create(
    &tasks[0], &task_attribute, (void*) task_one, (void*) &params);
  pthread_create(
    &tasks[1], &task_attribute, (void*) task_two, (void*) &params);

  for (u8 n = 0; n < N_TASKS; n++)
  {
    pthread_join(tasks[n], 0);
  }

  return 0;
}
