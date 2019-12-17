#include <stdio.h> 
#include <stdlib.h>

typedef char ElemType;

typedef struct BSTNode{
	ElemType elem;
	int bf;
	struct BSTNode *lchild, *rchild;
}BSTNode, *BSTree;

void R_rotate(BSTree &p){
	BSTree *lc;
	lc = (BSTNode*)malloc(sizeof(BSTNode));
	lc = p->lchild;
	p->lchild = lc->rchild;
	lc->rchild = p;
	p = lc;
}

void L_rotate(BSTree &p){
	BSTree *rc;
	rc = (BSTNode*)malloc(sizeof(BSTNode));
	rc = p->rchild;
	p->rchild = rc->lchild;
	rc->lchild = p;
	p = rc;
}
