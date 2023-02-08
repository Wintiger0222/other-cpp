#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

int main(void)
{
	FILE* pFile = fopen("FE8_test.txt", "r");
	if (pFile == NULL)
	{
		printf("파일을 열 수 없음\n");
		return -1;
	}
	unsigned char chTemp;
	unsigned char chTemp2;
	unsigned char whatisnow = ']';
	unsigned char HANGUL = 0;
	while (!feof(pFile))
	{

		chTemp = fgetc(pFile);
		if (chTemp >= 0x80)
		{
			chTemp2 = fgetc(pFile);
			printf("%c%c",chTemp, chTemp2);
		}
		else {
			if (whatisnow == '[' && chTemp == '[')
			{
				printf("<<error>>");
				_getch();
			}
			else if (whatisnow == ']' && chTemp == ']')
			{
				printf("<<error>>");
				_getch();
			}
			else if (chTemp == '[')
			{
				whatisnow = '[';
			}
			else if (chTemp == ']')
			{
				whatisnow = ']';
			}
			printf("%c",chTemp);
		}
	}

	fclose(pFile);
}