#ifndef __C_QUEUE_H__
#define __C_QUEUE_H__

#define TRUE 1
#define FALSE 0

#define QUE_LEN 100
typedef int Data;

typedef struct _cQueue
{
	int front;
	int rear;
	Data queArr[QUE_LEN];
} CQueue;

typedef CQueue Queue;

void QueueInit(Queue *pq);
int QIsEmpty(Queue *pq);

void Enqueue(Queue *pq, Data data);
Data Dequeue(Queue *pq);
Data QPeek(Queue *pq);

//  시뮬레이션을 위한 부분 --------------------------

// Simulation.h (선택)
#ifndef SIMULATION_H_
#define SIMULATION_H_

typedef struct
{
	int total_customers;		 // 총 고객 수 (180)
	int max_occupancy;			 // 대기실 최대 동시 인원
	int min_wait;						 // 주문~수령 최소 시간(초)
	int max_wait;						 // 주문~수령 최대 시간(초)
	double avg_wait;				 // 주문~수령 평균 시간(초)
	int cnt17, cnt20, cnt26; // 메뉴 분포 집계
} SimResult;

void RunSimulation(int seed, SimResult *out);

#endif

#endif