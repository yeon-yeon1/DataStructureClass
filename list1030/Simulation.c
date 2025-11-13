// 주문, 대기 시뮬레이션
#include "Que.h"
#include <time.h>
#include <stdlib.h>

#define LUNCH_SECONDS 3600
#define ARRIVAL_GAP 20
#define N_CUSTOMERS (LUNCH_SECONDS / ARRIVAL_GAP)

static const int SERVICE_TIMES_[3] = {17, 20, 26};
static int pick_service_seconds_(void) { return SERVICE_TIMES_[rand() % 3]; }

void RunSimulation(unsigned int seed, SimResult *out)
{
  if (!out)
    return;
  srand(seed);

  int in_room = 0;
  int max_occupancy = 0;

  int server_busy = 0;
  Customer working;
  int current_finish = 0;

  int min_sys = 0, max_sys = 0;
  int have_sys = 0;
  long long sum_sys = 0;
  int cnt17 = 0, cnt20 = 0, cnt26 = 0;

  Queue q;
  QInit(&q, N_CUSTOMERS + 8);

  int next_arrival_idx = 0;

  while (next_arrival_idx < N_CUSTOMERS || server_busy || !QEmpty(&q))
  {

    if (!server_busy && !QEmpty(&q))
    {
      working = QDeq(&q);
      working.start = working.arrival;
      working.finish = working.start + working.service;
      working.system = working.finish - working.arrival;

      if (!have_sys)
      {
        min_sys = max_sys = working.system;
        have_sys = 1;
      }
      else
      {
        if (working.system < min_sys)
          min_sys = working.system;
        if (working.system > max_sys)
          max_sys = working.system;
      }
      sum_sys += working.system;

      server_busy = 1;
      current_finish = working.finish;
      continue;
    }

    int has_arrival = (next_arrival_idx < N_CUSTOMERS);
    int next_arrival = has_arrival ? (next_arrival_idx * ARRIVAL_GAP) : 0;

    if (server_busy && (!has_arrival || current_finish <= next_arrival))
    {

      if (in_room > 0)
        in_room--;

      if (!QEmpty(&q))
      {
        working = QDeq(&q);
        working.start = current_finish;
        working.finish = working.start + working.service;
        working.system = working.finish - working.arrival;

        if (!have_sys)
        {
          min_sys = max_sys = working.system;
          have_sys = 1;
        }
        else
        {
          if (working.system < min_sys)
            min_sys = working.system;
          if (working.system > max_sys)
            max_sys = working.system;
        }
        sum_sys += working.system;

        server_busy = 1;
        current_finish = working.finish;
      }
      else
      {
        server_busy = 0;
      }
    }
    else if (has_arrival)
    {

      Customer c = (Customer){0};
      c.id = next_arrival_idx + 1;
      c.arrival = next_arrival;
      c.service = pick_service_seconds_();

      if (c.service == 17)
        cnt17++;
      else if (c.service == 20)
        cnt20++;
      else
        cnt26++;

      in_room++;
      if (in_room > max_occupancy)
        max_occupancy = in_room;

      if (!server_busy)
      {
        c.start = c.arrival;
        c.finish = c.start + c.service;
        c.system = c.finish - c.arrival;

        if (!have_sys)
        {
          min_sys = max_sys = c.system;
          have_sys = 1;
        }
        else
        {
          if (c.system < min_sys)
            min_sys = c.system;
          if (c.system > max_sys)
            max_sys = c.system;
        }
        sum_sys += c.system;

        server_busy = 1;
        current_finish = c.finish;
        working = c;
      }
      else
      {
        QEnq(&q, c);
      }
      next_arrival_idx++;
    }
    else
    {

      ;
    }
  }

  out->total_customers = N_CUSTOMERS;
  out->max_occupancy = max_occupancy;
  out->min_system = have_sys ? min_sys : 0;
  out->max_system = have_sys ? max_sys : 0;
  out->avg_system = (double)sum_sys / (double)N_CUSTOMERS;
  out->cnt17 = cnt17;
  out->cnt20 = cnt20;
  out->cnt26 = cnt26;

  QFree(&q);
}
