#ifndef __D_LINKED_LIST_H__
#define __D_LINKED_LIST_H__

#define TRUE 1
#define FALSE 0


typedef struct _student {
		char name[11];  // 학생 이름 (최대 10자 + 널문자)
		int year;       // 입학년도
		int age;        // 나이
		int stnum;      // 학번 (학생 번호)
} LData;

typedef struct _node {
	LData data;
	struct _node *next;
} Node;

typedef struct _linkedList {
	Node *head;
	Node *cur;
	Node *before;
	int numOfData;
	int (*comp)(LData d1, LData d2);
} LinkedList;

typedef LinkedList List;

void ListInit(List *plist);
void LInsert(List *plist, LData data);

int LFirst(List *plist, LData *pdata);
int LNext(List *plist, LData *pdata);

LData LRemove(List *plist);
int LCount(List *plist);

void SetSortRule(List *plist, int (*comp)(LData d1, LData d2));

#endif
