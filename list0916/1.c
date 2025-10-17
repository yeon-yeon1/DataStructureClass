#include <stdio.h>
#include <stdlib.h>
#define MAX 10

// 관리하고자하는 학생 데이터
typedef struct __Student {
  char name[11];
  int year;
  int age;
  int sno;
} student_t;

// 함수 참조를 위한 구조체
typedef struct __ArrayList {
  student_t arr[MAX];
  int numOfData;
  int cur;
} ArrayList_t;

typedef ArrayList_t List;

// 초기화 함수
void Init(List *plist);
// 데이터 삽입 함수
void Insert(List *plist, student_t data);
// 첫 데이터 참조
int First(List *plist, student_t *pdata);
// 두 번째 이후 데이터 참조
int Next(List *plist, student_t *pdata);
// 데이터 출력함수
void PrintStudent(List *plist);
// 데이터 삭제 함수
int Remove(List *plist);
// 한 명 출력(헬퍼)
void PrintOne(const student_t *s);
// 전체 출력(기존 PrintStudent를 구현)
// 학번으로 검색 (찾으면 cur을 그 위치로 이동)
int FindBySno(List *plist, int sno, student_t *out);
// 학번으로 삭제 (찾으면 해당 항목 삭제)
int RemoveBySno(List *plist, int sno);

int main(void){
  List list;
  Init(&list);

  // scanf 없이 초기 더미 데이터 6개 이상 삽입
  student_t seeds[] = {
    {"Kim",  2, 21, 20250001},
    {"Lee",  1, 20, 20250002},
    {"Park", 3, 22, 20250003},
    {"Choi", 4, 23, 20250004},
    {"Jung", 2, 21, 20250005},
  };
  int seedCount = sizeof(seeds)/sizeof(seeds[0]);
  for(int i=0;i<seedCount;i++){
    Insert(&list, seeds[i]);
  }

  puts("[1] 초기 전체 목록");
  PrintStudent(&list);

  // 새 학생 삽입
  student_t newStu = {"Shin", 1, 20, 20259999};
  Insert(&list, newStu);
  puts("\n[2] 새 학생 삽입 후 전체 목록");
  PrintStudent(&list);

  // 학번으로 검색
  student_t found;
  int target = 20250003;
  if(FindBySno(&list, target, &found)){
    puts("\n[3] 학번으로 검색 성공");
    PrintOne(&found);
  } else {
    printf("\n[3] 학번 %d 검색 실패\n", target);
  }

  // 학번으로 삭제
  int delTarget = 20250004;
  if(RemoveBySno(&list, delTarget)){
    printf("\n[4] 학번 %d 삭제 완료\n", delTarget);
  } else {
    printf("\n[4] 학번 %d 삭제 실패 (존재하지 않음)\n", delTarget);
  }

  puts("\n[5] 삭제 후 전체 목록");
  PrintStudent(&list);

  return 0;
}

// 초기화 함수
void Init(List *plist){
  (plist -> numOfData) = 0;
  (plist -> cur) = -1;
}
// 데이터 삽입 함수
void Insert(List *plist, student_t data){
  if(plist->numOfData >= MAX){
    puts("저장이 불가합니다.");
    return;
  }
  plist->arr[plist->numOfData] = data;
  (plist->numOfData)++;
}
// 첫 데이터 참조
int First(List *plist, student_t *pdata) {
  if(plist -> numOfData == 0) return 0;
  
  (plist -> cur) = 0;
  *pdata = plist->arr[0];
  return 1;
}
// 두 번째 이후 데이터 참조
int Next(List *plist, student_t *pdata){
  if(plist -> cur >= (plist -> numOfData) -1) return 0;

  (plist -> cur)++;
  *pdata = plist -> arr[plist -> cur];
  return 1;
}
// 데이터 출력함수
void PrintStudent(List *plist) {
  student_t data;
  int idx = 0;
  if(First(plist, &data)){
    printf("%2d) name=%s, year=%d, age=%d, sno=%d\n", ++idx, data.name, data.year, data.age, data.sno);
    while(Next(plist, &data)){
      printf("%2d) name=%s, year=%d, age=%d, sno=%d\n", ++idx, data.name, data.year, data.age, data.sno);
    }
  } else {
    puts("(비어있음)");
  }
  // 순회가 끝나면 cur는 마지막 요소를 가리킵니다.
}

void PrintOne(const student_t *s){
  printf("name=%s, year=%d, age=%d, sno=%d\n", s->name, s->year, s->age, s->sno);
}

int FindBySno(List *plist, int sno, student_t *out){
  student_t data;
  if(First(plist, &data)){
    if(data.sno == sno){
      *out = data;
      return 1;
    }
    while(Next(plist, &data)){
      if(data.sno == sno){
        *out = data;
        return 1;
      }
    }
  }
  return 0;
}

int RemoveBySno(List *plist, int sno){
  // First/Next로 순회하면서 cur가 해당 위치를 가리키도록 설정한 뒤 Remove 호출
  student_t data;
  if(First(plist, &data)){
    if(data.sno == sno){
      return Remove(plist);
    }
    while(Next(plist, &data)){
      if(data.sno == sno){
        return Remove(plist);
      }
    }
  }
  return 0;
}
// 데이터 삭제 함수
int Remove(List *plist){
  int rpos = plist->cur;
  int num = plist->numOfData;

  if(num == 0 || rpos < 0 || rpos >= num) return 0;

  for(int i = rpos; i < num - 1; i++)
    plist->arr[i] = plist->arr[i+1];

  (plist->numOfData)--;
  (plist->cur)--;
  return 1;
}