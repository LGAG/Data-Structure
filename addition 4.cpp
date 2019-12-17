#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>

using namespace std;

typedef struct BiNode {
	int elem;
	BiNode *Lkid, *Rkid;
}BiNode,*BiTree;

int initializeBiTree(BiTree T) {
	T = (BiNode*)malloc(sizeof(BiNode));
	if (!T) exit(0);
	T->elem = -1;
	T->Lkid = NULL;
	T->Rkid = NULL;
}

int add(BiTree T, int data){
	if(T->elem == -1){
		T->elem = data;
		return 1;
	}
	if(data < T->elem){
		if(T->Lkid == NULL){
			BiTree tmp;
			tmp = (BiNode*)malloc(sizeof(BiNode));
			tmp->elem = data;
			tmp->Lkid = NULL;
			tmp->Rkid = NULL;
			T->Lkid = tmp;
			return 2;
		}
		else{
			add(T->Lkid,data);
		}
	}
	if(data > T->elem){
		if(T->Rkid == NULL){
			BiTree tmp;
			tmp = (BiNode*)malloc(sizeof(BiNode));
			tmp->elem = data;
			tmp->Lkid = NULL;
			tmp->Rkid = NULL;
			T->Rkid = tmp;
			return 2;
		}
		else{
			add(T->Rkid,data);
		}
	}
}

int midtraverse(BiTree T) {
	if (T != NULL) {
		midtraverse(T->Lkid);
		printf(" %d", T->elem);
		midtraverse(T->Rkid);
		return 1;
	}
	else {
		return -1;
	}
}

int indentateBiTree(BiTree T, int deep) {
	if (T != NULL) {
		indentateBiTree(T->Lkid,deep+1);
		for(int i=0;i<=deep;i++){
			printf("    ");
		}
		printf("%d\n", T->elem);
		indentateBiTree(T->Rkid,deep+1);
		return 1;
	}
	else {
		return -1;
	}
}

int main(void) {
	BiTree T;
	T = (BiNode*)malloc(sizeof(BiNode));
	initializeBiTree(T);
	T->elem = -1;
	T->Lkid = NULL;
	T->Rkid = NULL;
	while(1){
		int data;
		scanf("%d",&data);
		if(data == 0){
			getchar();
			getchar();
			break;
		}
		getchar();
		add(T,data);
	}
	indentateBiTree(T,0);
	midtraverse(T);
}
