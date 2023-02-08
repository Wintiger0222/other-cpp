#define _CRT_SECURE_NO_WARNINGS
// font.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
//#define CHUCHUL
#include <iostream>

int main()
{
	FILE* fin = NULL;
	FILE* fout = NULL;

#ifdef CHUCHUL
	fin = fopen("input.bin", "rb");
	fout = fopen("output.bin", "wb");
#else
	//fin = fopen("input_2.bin", "rb");
	fin = fopen("font.bin", "rb");
	fout = fopen("fox_moji_data.c", "w");
#endif
	if (fin == NULL)
	{
		printf("인풋을 열지 못함\n");
		return -1;
	}
	if (fout == NULL)
	{
		printf("아웃풋을 열지 못함\n");
		return -1;
	}

	fseek(fin, 0, SEEK_END);    // 파일 포인터를 파일의 끝으로 이동시킴
	int size = ftell(fin);

	fseek(fin, 0, SEEK_SET);
	//112

#ifdef CHUCHUL
	unsigned char temp[112] = { 0 };
	for (; ftell(fin) < size; )
	{
		fread(&temp[0], 112, sizeof(char), fin);
		for (int i = 0; i < 112; i++)
			fprintf(fout, "%c", temp[i] & 0B00010001);
		for (int i = 0; i < 112; i++)
			fprintf(fout, "%c", (temp[i] & 0B00100010) >> 1);
		for (int i = 0; i < 112; i++)
			fprintf(fout, "%c", (temp[i] & 0B01000100) >> 2);
		for (int i = 0; i < 112; i++)
			fprintf(fout, "%c", (temp[i] & 0B10001000) >> 3);

	}
#else
	unsigned char temp1[112] = { 0 };
	unsigned char temp2[112] = { 0 };
	unsigned char temp3[112] = { 0 };
	unsigned char temp4[112] = { 0 };
	fprintf(fout, "unsigned char font_00[] = {\n\t");
	for (; ftell(fin) < size; )
	{
		fread(&temp1[0], 112, sizeof(char), fin);
		fread(&temp2[0], 112, sizeof(char), fin);
		fread(&temp3[0], 112, sizeof(char), fin);
		fread(&temp4[0], 112, sizeof(char), fin);
		for (int i = 0; i < 112; i++)
		{	//fprintf(fout, "%c", (temp1[i] | (temp2[i] << 1) | (temp3[i] << 2) | (temp4[i] << 3)));
			unsigned char temp = (temp1[i] | (temp2[i] << 1) | (temp3[i] << 2) | (temp4[i] << 3));
			fprintf(fout, "0x%X%X, ", (temp & 0xF0) >> 4, (temp & 0xF) );
			if (i % 8 == 7)
				fprintf(fout, "\n\t");
		}
	}
	fprintf(fout, "};\n");
#endif
	return 0;
}
