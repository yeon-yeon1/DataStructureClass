// 점심시간 대기열 시뮬레이션

#include "CircularQueue.h"
// 원형 큐 헤더(정수 인덱스 저장용), 랜덤/시간 사용
#include <stdlib.h>
#include <time.h>

#define LUNCH_SECONDS 3600                        // 점심시간 총 1시간(초 단위)
#define ARRIVAL_GAP 20                            // 20초마다 1명 도착
#define N_CUSTOMERS (LUNCH_SECONDS / ARRIVAL_GAP) // 총 손님 수 = 180

static const int SERVICE_TIMES[3] = {17, 20, 26}; // 메뉴별 조리시간(햄버거/샌드위치/김밥), 동일확률

// 17/20/26 중 하나를 무작위로 골라 조리시간 반환
static int pick_service_seconds(void) { return SERVICE_TIMES[rand() % 3]; }

// 한 손님(idx)의 '시작/완료/대기시간'을 계산하고, 전체 통계(min/max/sum)를 갱신
// start_time: 이 손님이 실제로 조리를 시작하는 시각(도착 즉시 시작 or 이전 손님 종료 시각)
void StartAndAccount(int idx, int start_time, int *min_w, int *max_w, int *sum_w, int arrival[], int service[], int start[], int finish[], int wait[])
{
  // 실제 시작 시각을 기록(도착 즉시 또는 직전 완료 시각)
  start[idx] = start_time;
  // 완료 시각 = 시작 + 조리시간
  finish[idx] = start[idx] + service[idx];
  // 주문~수령까지 걸린 총 시간(=대기+조리)
  wait[idx] = finish[idx] - arrival[idx];

  // 첫 손님이면 min/max 초기화, 아니라면 갱신
  if (*sum_w == 0)
  {
    *min_w = *max_w = wait[idx];
  }
  else
  {
    if (wait[idx] < *min_w)
      *min_w = wait[idx];
    if (wait[idx] > *max_w)
      *max_w = wait[idx];
  }
  *sum_w += wait[idx];
}

// 시뮬레이션 메인 루프
// - 입력: 난수 seed, 출력: SimResult(최대 동시 인원, 최소/평균/최대 대기시간 등)
void RunSimulation(int seed, SimResult *out)
{
  if (!out)
    return;
  srand(seed);

  // 각 손님의 타임라인(도착/시작/완료/대기) 정보를 담는 배열
  int arrival[N_CUSTOMERS];
  int service[N_CUSTOMERS];
  int start[N_CUSTOMERS] = {0};  // 시작 시각(초)
  int finish[N_CUSTOMERS] = {0}; // 완료 시각(초)
  int wait[N_CUSTOMERS] = {0};   // 주문~수령 총 시간

  // 20초 간격으로 도착시각을 채우고, 각 손님의 조리시간을 무작위로 설정
  int cnt17 = 0, cnt20 = 0, cnt26 = 0;
  for (int i = 0; i < N_CUSTOMERS; ++i)
  {
    arrival[i] = i * ARRIVAL_GAP;
    service[i] = pick_service_seconds();
    if (service[i] == 17)
      ++cnt17;
    else if (service[i] == 20)
      ++cnt20;
    else
      ++cnt26;
  }

  CQueue q; /* 대기열: 아직 시작 못한 손님들의 인덱스를 큐로 저장 */
  // 큐 초기화
  QueueInit(&q);

  int server_busy = 0;    // 0=비어있음, 1=조리 중
  int current_finish = 0; // 현재 조리 중인 손님이 끝나는 시각
  int in_room = 0;        // 대기실 내 인원(조리 중 포함)
  int max_occupancy = 0;  // 대기실 최대 동시 인원

  int min_w = 0, max_w = 0, sum_w = 0;
  int next_arrival_idx = 0;

  // - 더 올 손님이 있거나(next_arrival_idx),
  // - 주방이 일하는 중이거나(server_busy),
  // - 대기열에 손님이 남아있으면(!QIsEmpty)
  // 계속 시뮬레이션
  while (next_arrival_idx < N_CUSTOMERS || server_busy || !QIsEmpty(&q))
  {
    // 다음 도착 이벤트가 남았는지 체크
    int has_arrival = (next_arrival_idx < N_CUSTOMERS);
    int next_arrival_time = has_arrival ? arrival[next_arrival_idx] : 0; // 다음 손님의 도착 시각(없으면 0)

    // (1) 주방이 비었고 큐에 손님이 있으면: 즉시 다음 손님 시작
    if (!server_busy && !QIsEmpty(&q))
    {
      int idx = Dequeue(&q);
      StartAndAccount(idx, current_finish, &min_w, &max_w, &sum_w, arrival, service, start, finish, wait);

      server_busy = 1;
      current_finish = finish[idx];
      continue;
    }

    // (2) 완료 이벤트가 먼저 오면: 현재 손님 수령, 대기실 인원 감소, 다음 손님 시작 시도
    if (server_busy && (!has_arrival || current_finish <= next_arrival_time))
    {
      if (in_room > 0)
        --in_room;
      server_busy = 0;

      // 큐에 누가 남아있으면 바로 이어서 시작
      if (!QIsEmpty(&q))
      {
        int idx = Dequeue(&q);
        StartAndAccount(idx, current_finish, &min_w, &max_w, &sum_w, arrival, service, start, finish, wait);

        server_busy = 1;
        current_finish = finish[idx];
      }
    }
    // (3) 도착 이벤트가 먼저 오면: 도착 처리(조리중이 아니면 즉시 시작, 아니면 큐에 대기)
    else if (has_arrival)
    {
      int idx = next_arrival_idx++;
      // 대기실 총 인원 업데이트(조리 중인 사람도 포함)
      ++in_room;
      if (in_room > max_occupancy)
        max_occupancy = in_room;

      // 주방이 비어 있으면 곧바로 조리 시작
      if (!server_busy)
      {
        StartAndAccount(idx, arrival[idx], &min_w, &max_w, &sum_w, arrival, service, start, finish, wait);

        server_busy = 1;
        current_finish = finish[idx];
      }
      // 바쁘면 큐에 넣어 순서 기다림
      else
      {
        Enqueue(&q, idx);
      }
    }
  }

  // 최종 결과 채우기
  out->total_customers = N_CUSTOMERS;
  out->max_occupancy = max_occupancy;
  out->min_wait = sum_w > 0 ? min_w : 0;
  out->max_wait = sum_w > 0 ? max_w : 0;
  out->avg_wait = (double)sum_w / (double)N_CUSTOMERS;
  out->cnt17 = cnt17;
  out->cnt20 = cnt20;
  out->cnt26 = cnt26;
}