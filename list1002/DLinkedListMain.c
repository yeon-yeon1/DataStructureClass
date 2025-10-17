#include <stdio.h>
#include "DLinkedList.h"

// 누가 더 앞서는 지를 위해 쓰는 함수
// 이후 *comp에 전달될 함수임
int WhoIsPrecede(LData d1, LData d2) {
	// d2가 더 클 때 0 작을 땐 1
	if(d1.stnum < d2.stnum)
		return 0;
	else
		return 1;
}

int main(void) {
	List list;
	LData data;
	// 초기화 함수
	ListInit(&list);

	// 정렬함수
	SetSortRule(&list, WhoIsPrecede);

	// 삽입함수
	LData d1 = {"Kim", 2024, 22, 20240879};
	LData d2 = {"Jin", 2023, 23, 20231234};
	LData d3 = {"Jun", 2024, 21, 20240864};
	LData d4 = {"Choi", 2021, 25, 20214321};
	LData d5 = {"Hae", 2022, 24, 20224567};

	LInsert(&list, d1); LInsert(&list, d2);
	LInsert(&list, d3); LInsert(&list, d4);
	LInsert(&list, d5);

	// 조회
	printf("현재 데이더의 수: %d\n\n", LCount(&list));

	// 전체 데이터 출력
	printf("[전체 데이터 출력]\n");
	if(LFirst(&list, &data)) {
		printf("이름: %s, 입학년도: %d, 나이: %d, 학번: %d\n",
       data.name, data.year, data.age, data.stnum);

		while(LNext(&list, &data)) {
			printf("이름: %s, 입학년도: %d, 나이: %d, 학번: %d\n",
       data.name, data.year, data.age, data.stnum);
		}
	}
	printf("\n\n");

    // 20240864 학번 데이터 삭제
  //   int target = 20240864;
  //   int target2 = 20240000; // 없는 학번
  //   if (LFirst(&list, &data)) {
  //       do {
	// 		if (data.stnum == target) {
	// 			LRemove(&list);
	// 			break; 
	// 		} else if (data.stnum == target2) {
	// 			LRemove(&list);
	// 			break; 
	// 		}
	// 	} while (LNext(&list, &data));
	// }

int target = 20240864;
int target2 = 20240000; // 없는 학번

if (LFirst(&list, &data)) {
    while (1) {
        if ((data.stnum == target) || (data.stnum == target2))  {
            LRemove(&list);
            break;
        } 
				if (!LNext(&list, &data))
            break;
    }
}

	printf("현재 데이더의 수: %d\n", LCount(&list));

	//  삭제 후 전체 데이터 출력
	if(LFirst(&list, &data)) {
		printf("이름: %s, 입학년도: %d, 나이: %d, 학번: %d\n",
       data.name, data.year, data.age, data.stnum);

		while(LNext(&list, &data)) {
			printf("이름: %s, 입학년도: %d, 나이: %d, 학번: %d\n",
       data.name, data.year, data.age, data.stnum);
		}
	}
	printf("\n\n");

	return 0;
}
