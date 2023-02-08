#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main(void)
{
	FILE* pf = NULL;
	unsigned char a[2];
	unsigned short b[1];
	int i,j;
	int temp;
	pf = fopen("test.nds", "rb");
	if (pf == NULL)
	{
		//printf("파일 읽기 에러\n");
		return -1;
	}
	//printf("파일 읽기 성공\n");
	fseek(pf, 0x1820A00, SEEK_SET);

	for (; ftell(pf)<0x1B3BD80; )
	{
		fread(a, sizeof(char), 2, pf);
		if (a[0] == 0x95 && a[1] == 0x10)
		{

			printf("ScriptLong\t");
			printf("0x%X\t", ftell(pf));
			fread(b, sizeof(short), 1, pf);
			printf("%d\t", b[0]);//lenb
			fread(b, sizeof(short), 1, pf);
			printf("%d\t", b[0]);//len
			for (j = 0; j < ((int)b[0] / 2); j++)
			{
				fread(a, sizeof(char), 2, pf);
				if (a[0] == 0x00) a[0] = ';';
				if (a[1] == 0x00) a[1] = ';';
				if (a[0] == '\n') a[0] = 'n';
				if (a[1] == '\n') a[1] = 'n';
				if (a[0] == '\r') a[0] = 'r';
				if (a[1] == '\r') a[1] = 'r';
				printf("%c%c", a[0], a[1]);
				
			}
			printf("");
			printf("\n");
		}
		if (a[0] == 0x55 && a[1] == 0x08)
		{
			printf("ScriptShort\t");
			printf("0x%X\t", ftell(pf));
			fread(a, sizeof(char), 2, pf);
			printf("%d\t", a[0]);//lenb
			printf("%d\t", a[1]);//len
			temp = (int)a[1];
			for (j = 0; j < (temp / 2); j++)
			{
				fread(a, sizeof(char), 2, pf);
				if (a[0] == 0x00) a[0] = ';';
				if (a[1] == 0x00) a[1] = ';';
				if (a[0] == '\n') a[0] = 'n';
				if (a[1] == '\n') a[1] = 'n';
				if (a[0] == '\r') a[0] = 'r';
				if (a[1] == '\r') a[1] = 'r';
				printf("%c%c", a[0], a[1]);
				
			}
			printf("");
			printf("\n");
		}
		
	}
		
	

	
	return 0;
}