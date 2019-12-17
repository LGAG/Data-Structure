#include <stdio.h> 
#include <stdlib.h>

#define LH 1;
#define EH 0;
#define RH - 1;

typedef char ElemType;

typedef struct BSTNode {
	ElemType elem;
	int bf;
	struct BSTNode *lchild, *rchild;
}BSTNode, *BSTree, *BiTree;

void R_rotate(BSTree &p) {
	BSTree lc;
	lc = (BSTNode*)malloc(sizeof(BSTNode));
	lc = p->lchild;
	p->lchild = lc->rchild;
	lc->rchild = p;
	p = lc;
}

void L_rotate(BSTree &p) {
	BSTree rc;
	rc = (BSTNode*)malloc(sizeof(BSTNode));
	rc = p->rchild;
	p->rchild = rc->lchild;
	rc->lchild = p;
	p = rc;
}

void LeftBalance(BSTree &T) {
	BSTree lc = T->lchild;
	switch (lc->bf) {
	case 1:
		T->bf = EH;
		lc->bf = EH;
		R_rotate(T);
		break;
	case -1:
		BSTree rd = lc->rchild;
		switch (rd->bf) {
		case 1:
			T->bf = RH;
			lc->bf = EH;
			break;
		case 0:
			T->bf = EH;
			lc->bf = EH;
			break;
		case -1:
			T->bf = EH;
			lc->bf = LH;
			break;
		}
		rd->bf = EH;
		L_rotate(T->lchild);
		R_rotate(T);
	}
}

void RightBalance(BSTree &T) {
	BSTree rc = T->rchild;
	switch (rc->bf) {
	case -1:
		T->bf = EH;
		rc->bf = EH;
		L_rotate(T);
		break;
	case 1:
		BSTree ld = rc->lchild;
		switch (ld->bf) {
			//
		case -1:
			T->bf = LH;
			rc->bf = EH;
			break;
		case 0:
			T->bf = EH;
			rc->bf = EH;
			break;
		case 1:
			T->bf = EH;
			rc->bf = RH;
			break;
		}//
		ld->bf = EH;
		R_rotate(T->rchild);
		L_rotate(T);
	}
}

int InsertAVL(BSTree &T, ElemType e, int &taller) {
	//printf("e=%c\n", e);
	if (e == -1)return 1;
	if (!T) {
		//T = (BSTree)malloc(sizeof(BSTNode));
		T->elem = e;
		T->lchild = NULL;
		T->rchild = NULL;
		T->bf = EH;
		taller = 1;
	}
	else {
		if (e == T->elem) {
			taller = 0;
			return 0;
		}
		if (e < T->elem) {
			int E = 0;
			if (T->lchild == NULL) {
				BiTree tmp;
				tmp = (BSTNode*)malloc(sizeof(BSTNode));
				tmp->elem = e;
				tmp->lchild = NULL;
				tmp->rchild = NULL;
				T->lchild = tmp;
				tmp->bf = EH;
				taller = 1;
				E = -1;
			}
			if (E == -1) {
				if (!InsertAVL(T->lchild, E, taller)) return 0;
			}
			else {
				if (!InsertAVL(T->lchild, e, taller)) return 0;
			}
			if (taller) {
				switch (T->bf) {
				case 1:
					LeftBalance(T);
					taller = 0;
					break;
				case 0:
					T->bf = LH;
					taller = 1;
					break;
				case -1:
					T->bf = EH;
					taller = 0;
					break;
				}
			}
		}
		else {
			int E = 0;
			if (T->rchild == NULL) {
				BiTree tmp;
				tmp = (BSTNode*)malloc(sizeof(BSTNode));
				tmp->elem = e;
				tmp->lchild = NULL;
				tmp->rchild = NULL;
				T->rchild = tmp;
				tmp->bf = EH;
				taller = 1;
				E = -1;
			}
			if (E == -1) {
				if (!InsertAVL(T->rchild, E, taller)) return 0;
			}
			else {
				if (!InsertAVL(T->rchild, e, taller)) return 0;
			}
			if (taller) {
				switch (T->bf) {
				case 1:
					T->bf = EH;
					taller = 0;
					break;
				case 0:
					T->bf = RH;
					taller = 1;
					break;
				case -1:
					RightBalance(T);
					taller = 0;
					break;
				}
			}
		}
	}
	return 1;
}



int pretraverse(BiTree T) {
	if (T != NULL) {
		printf("%c", T->elem);
		pretraverse(T->lchild);
		pretraverse(T->rchild);
		return 1;
	}
	else {
		return -1;
	}
}
int midtraverse(BiTree T) {
	if (T != NULL) {
		midtraverse(T->lchild);
		printf("%c", T->elem);
		midtraverse(T->rchild);
		return 1;
	}
	else {
		return -1;
	}
}

int aftertraverse(BiTree T) {
	if (T != NULL) {
		aftertraverse(T->lchild);
		aftertraverse(T->rchild);
		printf("%c", T->elem);
		return 1;
	}
	else {
		return -1;
	}
}

int indentateBiTree(BiTree T, int deep) {
	if (T != NULL) {
		indentateBiTree(T->rchild, deep + 1);
		for (int i = 0; i < deep; i++) {
			printf("    ");
		}
		printf("%c\n", T->elem);
		indentateBiTree(T->lchild, deep + 1);
		return 1;
	}
	else {
		return -1;
	}
}

int main(void) {
	BSTree T;
	T = (BSTNode*)malloc(sizeof(BSTNode));
	int taller = 0;
	int count = 0;
	while (1) {
		char tmp;
		tmp = getchar();
		if (count == 0) {
			T->elem = tmp;
			T->lchild = NULL;
			T->rchild = NULL;
			T->bf = EH;
			count++;
		}
		//printf("tmp : %c  %d\n", tmp, tmp);
		if (tmp == '\n') break;
		InsertAVL(T, tmp, taller);
		/*printf("Preorder: ");
		pretraverse(T);
		printf("\n");
		printf("Inorder: ");
		midtraverse(T);
		printf("\n");
		printf("Postorder: ");
		aftertraverse(T);
		printf("\n");
		indentateBiTree(T, 0);
		printf("\n\n-----------------------------------\n\n");*/
	}
	printf("Preorder: ");
	pretraverse(T);
	printf("\n");
	printf("Inorder: ");
	midtraverse(T);
	printf("\n");
	printf("Postorder: ");
	aftertraverse(T);
	printf("\n");
	printf("Tree:\n");
	indentateBiTree(T, 0);
}
