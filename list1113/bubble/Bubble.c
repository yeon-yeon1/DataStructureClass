#include <stdio.h>

void BubbleSort(int arr[], int n)
{
  int i, j;
  int temp;
  int cnt = 0, cnt2 = 0;

  for (i = 0; i < n - 1; i++)
  {
    for (j = 0; j < (n - i) - 1; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
        cnt++;
      }
      cnt2++;
    }
  }
  printf("데이터 이동 횟수: %d\n", cnt);
  printf("데이터 비교 횟수: %d\n", cnt2);
}
