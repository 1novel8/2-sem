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

int main() {
	FILE* fup, * fdown, * f;
	setlocale(LC_ALL, "ru");

	puts("Ввод 1 файла:");
	if (!(fup = inputFile("file1.txt")))
		return 0;
	puts("Ввод 2 файла:");
	if (!(fdown = inputFile("file2.txt")))
		return 0;

	printf("\nФайл 1:");
	if (!(printFile("file1.txt")))
		return 0;
	printf("\nФайл 2:");
	if (!(printFile("file2.txt")))
		return 0;

	printf("\nФайл 1 отсортированный по возрастанию:");
	sortUp("file1.txt");
	if (!(printFile("file1.txt")))
		return 0;
	printf("\nФайл 2 отсортированный по возрастанию:");
	sortUp("file2.txt");
	if (!(printFile("file2.txt")))
		return 0;
	f = fun("file1.txt", "file2.txt");
	printf("\nФайл из 1+2 по убыванию:\n");
	if (!(printFile("FILE.txt")))
		return 0;
	return 0;
}

FILE* inputFile(const char* name) {
	FILE* f;
	int value, n;
	if (!(f = fopen(name, "w"))) {
		printf("НЕ удалось cоздать файл\n");
		return NULL;
	}
	printf("Введите количество элементов в файле\n");
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		printf("Введите %d элемент", i + 1);
		scanf("%d", &value);
		fprintf(f, "%4d", value);
	}
	system("cls");
	fclose(f);
	return f;
}

int  printFile(const char* name) {
	FILE* f;
	int value;
	if (!(f = fopen(name, "r"))) {
		printf("НЕ удалось открыть файл\n");
		return 0;
	}
	while (1) {
		fscanf(f, "%4d", &value);
		printf("%d   ", value);	
		if (feof(f))
			break;
	}
	return 1;
}

void sortUp(const char* name) {
	FILE* f;
	fpos_t i, j;
	int tmp_i, tmp_j, size;
	f = fopen(name, "r+");
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	for (fpos_t i = 0; i < size; i += 4) {
		for (fpos_t j = i; j < size; j += 4) {
			fsetpos(f, &i);
			fscanf(f, "%4d", &tmp_i);
			fsetpos(f, &j);
			fscanf(f, "%4d", &tmp_j);
			if (tmp_j < tmp_i) {
				fsetpos(f, &i);
				fprintf(f, "%4d", tmp_j);
				fsetpos(f, &j);
				fprintf(f, "%4d", tmp_i);
			}
		}
	}
	fclose(f);
}

FILE* fun(const char* nameup, const char* namedown) {
	FILE* f1, * f2, * f;
	fpos_t ind_1, ind_2;
	int tmp1, tmp2, size;

	if (!(f1 = fopen(nameup, "r"))) {
		printf("НЕ удалось открыть файл");
		return 0;
	}
	if (!(f2 = fopen(namedown, "r"))) {
		printf("НЕ удалось открыть файл");
		return 0;
	}
	if (!(f = fopen("FILE.txt", "w"))) {
		printf("НЕ удалось создать файл");
		return 0;
	}
	fseek(f1, 0, SEEK_END);
	ind_1 = ftell(f1)-4;
	fseek(f2, 0, SEEK_END);
	ind_2 = ftell(f2)-4;
	while (ind_1 >= 0&& ind_2>=0) {// пока не дошли до начала файла по возрастанию
		fsetpos(f1, &ind_1);
		fscanf(f1, "%4d", &tmp1);
		fsetpos(f2, &ind_2);
		fscanf(f2,"%4d", &tmp2);
		if (tmp1 > tmp2) {
			fprintf(f, "%4d", tmp1);
			ind_1 -= 4;
		}
		else {
			fprintf(f, " % 4d", tmp2);
			ind_2 -= 4;
		}
	}
	while (ind_1>=0) {//дописываем файл по убыванию
		fsetpos(f1, &ind_1);
		fscanf(f1, "%4d", &tmp1);
		fprintf( f, "%4d", tmp1);
		ind_1 -= 4;
	}
	while (ind_2 >= 0) {//дописываем файл по возрастанию
		fsetpos(f2, &ind_2);
		fscanf(f2, "%4d",&tmp2 );
		fprintf(f, "%4d", tmp2);
		ind_2 -= 4;
	}
	fclose(f1); fclose(f2); fclose(f);
	return f;
}