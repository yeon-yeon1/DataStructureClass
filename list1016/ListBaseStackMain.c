#include <stdio.h>
#include "ListBaseStack.h"
#include <string.h>

// 문자열을 입력하세요: hello
// 뒤집은 문자열: olleh

int main(void)
{
	char str[100];
	Stack stack;

	StackInit(&stack);

	printf("문자열을 입력하세요: ");
	scanf("%s", str);

	for (int i = 0; i < strlen(str); i++)
	{
		SPush(&stack, str[i]);
	}

	printf("뒤집은 문자열: ");
	while (!SIsEmpty(&stack))
	{
		printf("%c", SPop(&stack));
	}
	printf("\n");
	return 0;
}
