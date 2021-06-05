#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>
#include<Windows.h>
#include<locale.h>

FILE* inputFile(const char*);
FILE* fun(const char*, const char*);
int printFile(const char*);
void sortUp(const char*);
void sortDown(const char*);

int main() {
	FILE* fup, * fdown,*f;
	setlocale(LC_ALL, "ru");

	puts("Ввод 1 файла:");
	if (!(fup = inputFile("fileUp.bin")))
		return 0;
	puts("Ввод 2 файла:");
	if (!(fdown = inputFile("fileDown.bin")))
		return 0;

	printf("\nФайл 1:");
	if (!(printFile("fileUp.bin")))
		return 0;
	printf("\nФайл 2:");
	if (!(printFile("fileDown.bin")))
		return 0;

	printf("\nФайл 1 отсортированный по возрастанию:");
	sortUp("fileUp.bin");
	if (!(printFile("fileUp.bin")))
		return 0;
	printf("\nФайл 2 отсортированный по убыванию:");
	sortDown("fileDown.bin");
	if (!(printFile("fileDown.bin")))
		return 0;
	f = fun("fileUp.bin", "fileDown.bin");
	printf("\nФайл из 1+2 по удыванию:\n");
	if (!(printFile("file.bin")))
		return 0;
	return 0;
}

FILE* inputFile(const char*name) {
	FILE* f;
	int value, n;
	if (!(f = fopen(name, "wb"))) {
		printf("НЕ удалось cоздать файл\n");
		return NULL;
	}
	printf("Введите количество элементов в файле\n");
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		printf("Введите %d элемент", i + 1);
		scanf("%d", &value);
		fwrite(&value, sizeof(int), 1, f);
	}
	system("cls");
	fclose(f);
	return f;
}

int  printFile(const char* name) {
	FILE* f;
	int value;
	if (!(f = fopen(name, "rb"))) {
		printf("НЕ удалось открыть файл\n");
		return 0;
	}
	while (1) {
		fread(&value, sizeof(int), 1, f);
		if (feof(f))
			break;
		printf("%d   ", value);
	}
	return 1;
}

void sortUp(const char* name) {
	FILE* f;
	fpos_t i, j;
	int tmp_i, tmp_j, size;
	f = fopen(name, "rb+");
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	for (fpos_t i = 0; i < size - 4; i += 4) {
		for (fpos_t j = i; j < size; j += 4) {
			fsetpos(f, &i);
			fread(&tmp_i, sizeof(int), 1, f);
			fsetpos(f, &j);
			fread(&tmp_j, sizeof(int), 1, f);
			if (tmp_j < tmp_i) {
				fsetpos(f, &i);
				fwrite(&tmp_j, sizeof(int), 1, f);
				fsetpos(f, &j);
				fwrite(&tmp_i, sizeof(int), 1, f);
			}
		}
	}
	fclose(f);
}
void sortDown(const char* name) {
	FILE* f;
	fpos_t i, j;
	int tmp_i, tmp_j, size;
	f = fopen(name, "rb+");
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	for (fpos_t i = 0; i < size - 4; i += 4) {
		for (fpos_t j = i; j < size; j += 4) {
			fsetpos(f, &i);
			fread(&tmp_i, sizeof(int), 1, f);
			fsetpos(f, &j);
			fread(&tmp_j, sizeof(int), 1, f);
			if (tmp_j > tmp_i) {
				fsetpos(f, &i);
				fwrite(&tmp_j, sizeof(int), 1, f);
				fsetpos(f, &j);
				fwrite(&tmp_i, sizeof(int), 1, f);
			}
		}
	}
	fclose(f);
}

FILE* fun(const char* nameup, const char* namedown) {
	FILE* fup, * fdown, * f;
	fpos_t ind_up, ind_down;
	int tmp1, tmp2, size;

	if (!(fup = fopen(nameup, "rb"))) {
		printf("НЕ удалось открыть файл");
		return 0;
	}
	if (!(fdown = fopen(namedown, "rb"))) {
		printf("НЕ удалось открыть файл");
		return 0;
	}
	if (!(f = fopen("file.bin", "wb"))) {
		printf("НЕ удалось создать файл");
		return 0;
	}
	fseek(fup, 0, SEEK_END);
	ind_up = ftell(fup)-4;
	ind_down = 0;
	while (ind_up>=0) {// пока не дошли до начала файла по возрастанию
		fsetpos(fup, &ind_up);
		fread(&tmp1, 4, 1, fup);
		fsetpos(fdown, &ind_down);
		fread(&tmp2, 4, 1, fdown);
		if (feof(fdown))// пока не дошли до конца файла по убыванию
			break;
		if (tmp1 > tmp2) {
			fwrite(&tmp1, 4, 1, f);
			ind_up -= 4;
		}
		else {
			fwrite(&tmp2, 4, 1, f);
			ind_down += 4;
		}
	}
	while (!feof(fdown)) {//дописываем файл по убыванию
		fread(&tmp2, 4, 1, fdown);
		fwrite(&tmp2, 4, 1, f);
	}
	while (ind_up >= 0) {//дописываем файл по возрастанию
		fsetpos(fup, &ind_up);
		fread(&tmp1, 4, 1, fup);
		fwrite(&tmp1, 4, 1, f);
		ind_up -= 4;
	}
	fclose(fup); fclose(fdown); fclose(f);
	return f;
}