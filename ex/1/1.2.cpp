#include<stdio.h>
#include<malloc.h>
#include<locale.h>

struct tree {
	int data;
	tree* l,* r;
};

tree* createTree();
tree* add(tree*, int);
void printUp(tree*);

int main() {
	setlocale(LC_ALL, "ru");
	tree* tr;
	int val, i=0;
	tr = createTree();
	while (i<5) {
		puts("Введите число");
		scanf_s("%d", &val);
		add(tr, val);
		i++;
	}
	printUp(tr);
	return 0;
}

tree* createTree() {
	tree* tr = (tree*)malloc(sizeof(tree));
	int value;

	puts("Введите число в корень дерева");
	scanf_s("%d", &value);
	tr->data = value;
	tr->l = tr->r = NULL;
	return tr;
}

tree* add(tree* root, int value) {

	if (root == NULL) {
		root = (tree*)malloc(sizeof(tree));
		root->data = value;
		root->l = root->r=NULL;
	}
	else if (value < root->data)
		root->l=add(root->l, value);
	else if (value > root->data)
		root->r=add(root->r, value);
	return root;
}

void printUp(tree* root) {
	if (root) {
		printUp(root->l);
		printf("%d", root->data);
		printUp(root->r);
	}
}