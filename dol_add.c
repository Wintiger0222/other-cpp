#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define CONVERT_TO_BIG(X) ((X)=(temp[3]+(temp[2]*0x100)+(temp[1]*0x10000)+(temp[0]*0x1000000)))
#define ORG(X) (X+0x20)
int main(void)
{
	FILE* pf = NULL;
	pf = fopen("start.dol", "rb");
	if (pf == NULL)
	{
		printf("파일 읽기 에러\n");
		return -1;
	}

	fseek(pf, 0x25EB80, SEEK_SET);
	for (; ftell(pf) < 0x27AF60;)
	{
		char tempchar[2] = { 0xff, 0xff };
		printf("//;0x%X\n", ftell(pf)-0x25EB80+0x80261B80);
		printf(";.org 0x%X\n", ftell(pf));
		printf(";.string \"");
		while (tempchar[0]) {
			fread(tempchar, sizeof(char), 1, pf);
			if (tempchar[0] == '\n')
				printf("\\n");
			else if (tempchar[0] == '\r')
				printf("\\r");
			else
				printf("%c", tempchar[0]);
		}
		printf("\n");
	}


	return 0;
}