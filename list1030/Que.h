#ifndef QUEUE_H_
#define QUEUE_H_

typedef struct
{
    int id;
    int arrival;
    int service;
    int start;
    int finish;
    int system;
} Customer;

typedef struct
{
    Customer *buf;
    int cap;
    int front;
    int rear;
    int size;
} Queue;

void QInit(Queue *q, int capacity);
void QFree(Queue *q);
int QEmpty(Queue *q);
int QFull(Queue *q);
void QEnq(Queue *q, Customer c);
Customer QDeq(Queue *q);
Customer *QPeek(Queue *q);

typedef struct
{
    int total_customers;
    int max_occupancy;
    int min_system;
    int max_system;
    double avg_system;
    int cnt17, cnt20, cnt26;
} SimResult;

void RunSimulation(unsigned int seed, SimResult *out);

#endif
