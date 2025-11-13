#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Que.h"

int main(int argc, char **argv)
{
  unsigned int seed;
  if (argc >= 2)
    seed = (unsigned int)strtoul(argv[1], NULL, 10);
  else
    seed = (unsigned int)time(NULL);

  SimResult r;
  RunSimulation(seed, &r);

  printf("======== 식당 대기실 시뮬레이션 ========\n");
  printf("- 총 고객 수 : %d명\n", r.total_customers);
  printf("- 메뉴 분포  : 17초=%d, 20초=%d, 26초=%d\n\n", r.cnt17, r.cnt20, r.cnt26);
  printf("[질문 1] 대기실 최대 수용 인원 = %d명\n\n", r.max_occupancy);
  printf("[질문 2] 주문 후 ~ 수령까지 소요 시간\n");
  printf(" -> 최소: %d초, 평균: %.2f초, 최대: %d초\n", r.min_system, r.avg_system, r.max_system);
  return 0;
}