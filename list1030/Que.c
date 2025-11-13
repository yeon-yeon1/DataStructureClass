#include <stdlib.h>
#include <stdio.h>
#include "Que.h"

void QInit(Queue *q, int capacity)
{
  q->buf = (Customer *)malloc(sizeof(Customer) * capacity);
  if (!q->buf)
  {
    perror("malloc");
    exit(1);
  }
  q->cap = capacity;
  q->front = q->rear = q->size = 0;
}

void QFree(Queue *q)
{
  if (q->buf)
    free(q->buf);
  q->buf = NULL;
  q->cap = q->front = q->rear = q->size = 0;
}

int QEmpty(Queue *q) { return q->size == 0; }
int QFull(Queue *q) { return q->size == q->cap; }

void QEnq(Queue *q, Customer c)
{
  if (QFull(q))
  {
    printf("큐가 가득 찼습니다!\n");
    exit(1);
  }
  q->buf[q->rear] = c;
  q->rear = (q->rear + 1) % q->cap;
  q->size++;
}

Customer QDeq(Queue *q)
{
  if (QEmpty(q))
  {
    printf("큐가 비었습니다!\n");
    exit(1);
  }
  Customer c = q->buf[q->front];
  q->front = (q->front + 1) % q->cap;
  q->size--;
  return c;
}

Customer *QPeek(Queue *q)
{
  if (QEmpty(q))
    return NULL;
  return &q->buf[q->front];
}
