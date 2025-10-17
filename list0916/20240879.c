#include <stdio.h>
#include <stdlib.h>
#define max 10

// 학생 정보를 저장하기 위한 구조체 정의
typedef struct __Student {
    char name[11];  // 학생 이름 (최대 10자 + 널문자)
    int year;       // 입학년도
    int age;        // 나이
    int stnum;      // 학번 (학생 번호)
} student_t;

// 학생 배열과 관련 정보를 담는 구조체 정의
typedef struct __Array {
    student_t arr[max];  // 학생 데이터 배열, 최대 max명 저장 가능
    int cur;             // 현재 참조 중인 인덱스 (탐색 위치)
    int numofData;       // 현재 저장된 학생 데이터 수
} Array_t;

// Array_t를 List라는 이름으로 사용
typedef Array_t List;

// 함수 원형 선언
void Init(List *list);  // 리스트 초기화
void Insert(List *list, student_t data);  // 학생 데이터 삽입
void PrintAll(List *list);  // 리스트에 있는 모든 학생 출력
void SearchByStnum(List *list, int stnum);  // 학번으로 학생 검색
void RemoveByStnum(List *list, int stnum);  // 학번으로 학생 삭제
int  Remove(List *list, student_t *rdata);  // 현재 참조 위치의 학생 삭제

int First(List *list, student_t *mdata);  // 첫 번째 데이터 참조
int Next(List *list, student_t *mdata);   // 다음 데이터 참조

int main(void) {

    // 학생 정보를 저장할 리스트 변수 선언
    List mlist ;

    // 리스트 초기화 함수 호출
    // 주소를 넘겨서 리스트 내부 데이터 초기화
    Init(&mlist);
    

    // 미리 정의된 학생 데이터 5명
    student_t students[5] = {
    {"Kim", 2024, 22, 20240879},
    {"Jin", 2023, 23, 20231234},
    {"Jun", 2024, 21, 20240864},
    {"Choi", 2021, 25, 20214321},
    {"Hae", 2022, 24, 20224567}
};

// 학생 데이터를 리스트에 삽입
printf("1. 새로운 학생 데이터 삽입\n\n");
for (int i = 0; i < 5; i++) {
    Insert(&mlist, students[i]);
}

printf("2. 학생 데이터 출력\n");
// 리스트에 저장된 모든 학생 정보 출력
PrintAll(&mlist);
printf("\n");

printf("3. 리스트에 포함된 학번으로 검색\n");
// 리스트에 있는 학번으로 검색 (성공 케이스)
SearchByStnum(&mlist, 20240879);

printf("\n4. 리스트에 포함되지 않은 학번으로 검색\n");
// 리스트에 없는 학번으로 검색 (실패 케이스)
SearchByStnum(&mlist, 12345678);

printf("\n5. 리스트에 포함되지 않은 학번으로 삭제\n");
// 리스트에 없는 학번으로 삭제 시도 (실패)
RemoveByStnum(&mlist, 12345678);

printf("\n6. 리스트에 포함된 학번으로 삭제\n");
// 리스트에 있는 학번으로 삭제 시도 (성공)
RemoveByStnum(&mlist, 20240864);

printf("\n7. 삭제 후 전체 데이터 출력\n");
// 삭제 후 남은 학생들 출력
PrintAll(&mlist);

    return 0;
}

// 리스트 초기화 함수
// cur은 현재 탐색 위치를 나타내며, -1로 초기화하여 아직 탐색 시작 전임을 표시
// numofData는 현재 저장된 학생 수를 나타내며 0으로 초기화
void Init(List *list) {
    list -> cur = -1; 
    list -> numofData = 0;
    printf("리스트 초기화 끝\n\n");
}

// 학생 데이터 삽입 함수
// 리스트가 가득 찬 경우 삽입 불가 메시지 출력 후 종료
// 그렇지 않으면 배열의 다음 빈 공간에 학생 데이터를 저장하고 개수 증가
void Insert(List *list, student_t data) {
    if(list -> numofData >= max){
        puts("저장할 공간이 더이상 없습니다.");
        return;
    }
    list -> arr[list -> numofData] = data;
    list -> numofData++;
}

// 리스트에서 첫 번째 데이터를 참조하는 함수
// 데이터가 없으면 0 반환하여 실패 알림
// 있으면 cur을 0으로 설정하고 첫 번째 데이터를 mdata에 복사 후 1 반환
int First(List *list, student_t *mdata) {
  if (list -> numofData == 0) return 0;

  list -> cur = 0;
  *mdata = list -> arr[list -> cur];
  return 1;
}

// 리스트에서 다음 데이터를 참조하는 함수
// 현재 위치가 마지막이면 0 반환 (더 이상 데이터 없음)
// 그렇지 않으면 cur 증가시키고 해당 데이터를 mdata에 복사 후 1 반환
int Next(List *list, student_t *mdata) {  
  if (list -> cur >= (list -> numofData)-1) return 0;

  (list -> cur)++;
  *mdata = list -> arr[list -> cur];
  return 1;
}

// 리스트에 저장된 모든 학생 데이터를 출력하는 함수
// First 함수를 사용해 첫 데이터를 가져오고 출력
// Next 함수를 반복 호출하여 다음 데이터들을 출력
// 데이터가 없으면 "(비어있음)" 메시지 출력
void PrintAll(List *list) {
  student_t data;
  int idx = 0;
  if(First(list, &data)){
    printf("%2d) 이름=%s, 입학년도=%d, 나이=%d, 학번=%d\n", ++idx, data.name, data.year, data.age, data.stnum);
    while(Next(list, &data)){
      printf("%2d) 이름=%s, 입학년도=%d, 나이=%d, 학번=%d\n", ++idx, data.name, data.year, data.age, data.stnum);
    }
  } else {
    puts("(비어있음)");
  }
}

// 현재 참조 위치(cur)에 있는 학생 데이터를 삭제하는 함수
// 삭제 전에 유효한 위치인지 검사 (데이터가 없거나 cur이 범위 밖이면 삭제 실패)
// 삭제할 위치 이후의 데이터들을 한 칸씩 앞으로 당겨 빈 공간을 메움
// numofData를 1 줄이고 cur도 1 감소시켜 탐색 위치를 조정
// 삭제한 데이터를 rdata에 복사하여 반환
int  Remove(List *list, student_t *rdata) {
    // 삭제할 대상은 현재 참조 위치(cur)로 간주한다
    if (list->numofData == 0 || list->cur < 0 || list->cur >= list->numofData) return 0;

    int rpos = list->cur;           // 삭제할 인덱스
    int num  = list->numofData;     // 현재 데이터 수
    *rdata   = list->arr[rpos];     // 삭제 전 데이터 보관

    // 뒤의 데이터들을 한 칸씩 앞으로 당김
    for (int i = rpos; i < num - 1; i++) {
        list->arr[i] = list->arr[i + 1];
    }

    (list->numofData)--;  // 데이터 수 감소
    (list->cur)--;        // 참조 위치를 하나 뒤로 돌려놓음
    return 1;             // 삭제 성공
}

// 학번을 기준으로 학생을 검색하는 함수
// First와 Next를 이용해 리스트 전체를 탐색하며 학번 비교
// 찾으면 학생 정보를 출력하고 found 플래그를 1로 설정하여 탐색 종료
// 못 찾으면 "찾을 수 없습니다" 메시지 출력
void SearchByStnum(List *list, int stnum) {
    student_t data;
    int found = 0;
    if (First(list, &data)) {
        if (data.stnum == stnum) {
            printf("학번 %d 학생 정보: 이름=%s, 입학년도=%d, 나이=%d\n", stnum, data.name, data.year, data.age);
            found = 1;
        }
        while (!found && Next(list, &data)) {
            if (data.stnum == stnum) {
                printf("학번 %d 학생 정보: 이름=%s, 입학년도=%d, 나이=%d\n", stnum, data.name, data.year, data.age);
                found = 1;
            }
        }
    }
    if (!found) {
        printf("%d 학번을 찾을 수 없습니다.\n", stnum);
    }
}

// 학번을 기준으로 학생을 삭제하는 함수
// 리스트를 탐색하며 학번이 일치하는 학생을 찾으면 Remove 함수 호출하여 삭제
// 삭제 성공 시 삭제한 학생 이름과 학번 출력
// 찾지 못하면 "찾을 수 없습니다" 메시지 출력
void RemoveByStnum(List *list, int stnum) {
    student_t data;
    int found = 0;

    if (First(list, &data)) {
        if (data.stnum == stnum) found = 1;            // cur는 이미 0
        while (!found && Next(list, &data)) {
            if (data.stnum == stnum) found = 1;        // cur는 일치하는 위치
        }
    }

    if (found) {
        student_t removed;
        if ( Remove(list, &removed)) {
            printf("학번 %d 학생 데이터를 삭제했습니다. (이름=%s)\n", removed.stnum, removed.name);
        } else {
            printf("삭제에 실패했습니다.\n");
        }
    } else {
        printf("삭제할 %d 학번을 찾을 수 없습니다.\n", stnum);
    }
}