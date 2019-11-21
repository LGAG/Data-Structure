#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BiNode {
	char elem;
	BiNode *Lkid, *Rkid;
}BiNode,*BiTree;

int initializeBiTree(BiTree T) {
	T = (BiNode*)malloc(sizeof(BiNode));
	if (!T) exit(0);
	T->elem = 0;
	T->Lkid = NULL;
	T->Rkid = NULL;
}

int addBiTree(BiTree T, char c) {
	//printf("c : %c\n", c);
	if (c == '#') return -1;
	if (T == NULL) return -2;
	if (T->Lkid == NULL) {
		//printf("1\n");
		BiTree tmp;
		tmp = (BiNode*)malloc(sizeof(BiNode));
		tmp->elem = c;
		tmp->Lkid = NULL;
		tmp->Rkid = NULL;
		T->Lkid = tmp;
		return 1;
	}
	else if (T->Rkid == NULL) {
		//printf("2\n");
		BiTree tmp;
		tmp = (BiNode*)malloc(sizeof(BiNode));
		tmp->elem = c;
		tmp->Lkid = NULL;
		tmp->Rkid = NULL;
		T->Rkid = tmp;
		return 1;
	}
	else if (T->Lkid != NULL && T->Rkid != NULL) {
		//printf("3\n");
		if (addBiTree(T->Lkid, c) == 1)return 1;
		if (addBiTree(T->Rkid, c) == 1)return 1;
	}
	return 2;
}

int pretraverse(BiTree T) {
	if(T != NULL) {
		printf("%c", T->elem);
		pretraverse(T->Lkid);
		pretraverse(T->Rkid);
		return 1;
	}
	else {
		return -1;
	}
}
int midtraverse(BiTree T) {
	if (T != NULL) {
		midtraverse(T->Lkid);
		printf("%c", T->elem);
		midtraverse(T->Rkid);
		return 1;
	}
	else {
		return -1;
	}
}

int aftertraverse(BiTree T) {
	if (T != NULL) {
		aftertraverse(T->Lkid);
		aftertraverse(T->Rkid);
		printf("%c", T->elem);
		return 1;
	}
	else {
		return -1;
	}
}

int leaves_of_BiTree(BiTree T) {
	int L = 0, R = 0;
	if (T->Lkid == NULL && T->Rkid == NULL) {
		return 1;
	}
	if (T->Lkid != NULL) {
		L += leaves_of_BiTree(T->Lkid);
	}
	if (T->Rkid != NULL) {
		R += leaves_of_BiTree(T->Rkid);
	}
	return L + R;
}

int change_L_R(BiTree T) {
	if (T == NULL) return 0;
	else
	{
		BiTree tmp;
		tmp = (BiNode*)malloc(sizeof(BiNode));
		tmp = T->Lkid;
		T->Lkid = T->Rkid;
		T->Rkid = tmp;
		change_L_R(T->Lkid);
		change_L_R(T->Rkid);
		return 1;
	}//if (T->Lkid != NULL && T->Rkid != NULL) 
}

int indentateBiTree(BiTree T, int deep) {
	if (T != NULL) {
		for (int i = 0; i < deep; i++) {
			printf("    ");
		}
		printf("%c\n", T->elem);
	}
	else return 0;
	indentateBiTree(T->Lkid, deep + 1);
	indentateBiTree(T->Rkid, deep + 1);
	return 1;
}

int main(void) {
	int len = 0;;
	char str[100] = { 0 };
	BiTree node[100];
	while (1) {
		scanf("%c", &str[len]);
		node[len+1] = (BiNode*)malloc(sizeof(BiNode));
		node[len+1]->elem = str[len];
		node[len+1]->Lkid = NULL;
		node[len+1]->Rkid = NULL;
		if (str[len] == '\n') break;
		len++;
	}
	str[len] = '\0';
	BiTree T;
	T = (BiNode*)malloc(sizeof(BiNode));
	initializeBiTree(T);
	T->Lkid = NULL;
	T->Rkid = NULL;
	T->elem = str[0];
	//T = node[1];
	for (int i = 1; i < len; i++) {
		if (2 * i <= len) {
			if (node[2 * i]->elem != '#') {
				node[i]->Lkid = node[2 * i];
			}
			else {
				node[i]->Lkid = NULL;
			}
		}
		if (2 * i + 1 <= len) {
			if (node[2 * i + 1]->elem != '#') {
				node[i]->Rkid = node[2 * i + 1];
			}
			else {
				node[i]->Rkid = NULL;
			}
		}
	}
	T = node[1];
	printf("BiTree\n");
	indentateBiTree(T, 0);
	printf("pre_sequence  : ");
	pretraverse(T);
	printf("\n");
	printf("in_sequence   : ");
	midtraverse(T);
	printf("\n");
	printf("post_sequence : ");
	aftertraverse(T);
	printf("\n");
	printf("Number of leaf: %d\n", leaves_of_BiTree(T));

	change_L_R(T);
	printf("BiTree swapped\n");
	indentateBiTree(T,0);
	printf("pre_sequence  : ");
	pretraverse(T);
	printf("\n");
	printf("in_sequence   : ");
	midtraverse(T);
	printf("\n");
	printf("post_sequence : ");
	aftertraverse(T);
	printf("\n");
}
