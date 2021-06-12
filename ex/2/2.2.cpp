#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<locale.h>
#include<conio.h>

struct tree {
	int data;
	int n;
	tree* l, * r;
};

tree* create(tree*);
tree* add(tree*, int);
tree* search(tree*, int);
tree* delNode(tree*, int);
void output(tree*);

int main() {
	tree* tr = NULL, * tmp;
	int choise;
	int value;
	setlocale(LC_ALL, "ru");
	while (1) {
		puts("вид операции:\n1-создать дерево");
		puts("2-рекурсивный вывод содержимого дерева");
		puts("3-добавление элементов в дерево");
		puts("4-удаление любого элемента из дерева");
		puts("5-поиск элемента из дерева");
		puts("0-выход");
		scanf_s("%d", &choise);
		system("cls");
		switch (choise) {
		case 1:
			tr = create(tr);
			break;
		case 2:
			output(tr);
			break;
		case 3:
			puts("Введите элемент");
			scanf_s("%d", &value);
			tr=add(tr, value);
			break;
		case 4:
			puts("Введите значение элемента, который хотите удалить");
			scanf_s("%d", &value);
			tr=delNode(tr, value);
			break;
		case 5:
			puts("Введите значение элемента для поиска");
			scanf_s("%d", &value);
			tmp = search(tr, value);
			if (tmp)
				printf("элемент %d - есть в бинарном дереве\n", tmp->data);
			break;
		case 0:
			return 0;
		}
	}
}

tree* delNode(tree* root, int value) {
	if (root == NULL) {
		return root;
	}
	if (value < root->data) {
		root->l=delNode(root->l, value);
		return root;
	} 
	else if (value > root->data) {
		root->r = delNode(root->r, value);
		return root;
	}
	else if(root->r && root->l){
		tree* tmp = root->l;
		while (tmp->r)
			tmp = tmp->r;
		root->data = tmp->data;
		root->l=delNode(root->l, tmp->data);
		return root;
	}
	else if (root->l) {
		tree* tmp = root->l;
		free(root);
		return tmp;
	}
	else if (root->r) {
		tree* tmp = root->r;
		free(root);
		return tmp;
	}
	else {
		free(root);
		return NULL;
	}
}

tree* search(tree* root, int value) {
	if (!root)
	{
		puts("такого элемента нет в бинарном дереве");
		return NULL;
	}
	else if (value == root->data) {
		return root;
	}
	else if (value < root->data)
		search(root->l, value);
	else if (value > root->data)
		search(root->r, value);
}

tree* create(tree* root) {
	if (root) {
		puts("Бинарное дерево уже создано");
		return root;
	}
	if (!(root = (tree*)malloc(sizeof(tree)))) {
		puts("Недстаточно памяти");
		return NULL;
	}
	puts("Введите информацию в корень дерева");
	scanf_s("%d", &root->data);
	root->l = root->r = NULL;
	root->n = 1;
	return root;
}

tree* add(tree* root, int value) {
	if (root == NULL) {
		root = (tree*)malloc(sizeof(tree));
		root->data = value;
		root->n = 1;
		root->l = root->r = NULL;
	}
	else if (value == root->data)
		root->n++;
	else if (value < root->data)
		root->l = add(root->l, value);
	else
		root->r = add(root->r, value);
	return root;
}

void output(tree* root) {
	if (root) {
		output(root->l);
		printf("%d(%d)\n", root->data, root->n);
		output(root->r);
	}
}

