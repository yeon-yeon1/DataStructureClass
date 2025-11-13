#include <stdio.h>

void BubbleSort(int arr[], int n);

int main(void)
{
  int arr[] = {3, 2, 4, 1};
  int i;

  BubbleSort(arr, sizeof(arr) / sizeof(arr[0]));

  for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
  {
    printf("%d ", arr[i]);
  }

  printf("\n");

  return 0;
  // 
}
