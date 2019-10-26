#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct polynomial {
	ElemType data;
	ElemType index;
	struct polynomial *next;
};
polynomial *tmp;

void CreatePolyn(polynomial &P, int m);
void AddPolyn(polynomial &Pa, polynomial Pb);
void PrintPolyn(polynomial P);

int main(void) {
	int n;
	polynomial *HEAD1, *HEAD2, *HEAD3;
	scanf("%d", &n);
	if (n == 0) return 0;
	HEAD1 = (polynomial*)malloc(sizeof(polynomial));
	HEAD1->next = NULL;
	scanf("%d", &n);
	CreatePolyn(*HEAD1, n);
		
	HEAD2 = (polynomial*)malloc(sizeof(polynomial));
	HEAD2->next = NULL;
	scanf("%d", &n);
	CreatePolyn(*HEAD2, n);

	HEAD3 = (polynomial*)malloc(sizeof(polynomial));
	HEAD3->next = NULL;
	scanf("%d", &n);
	CreatePolyn(*HEAD3, n);

	PrintPolyn(*HEAD1);
	PrintPolyn(*HEAD2);
	PrintPolyn(*HEAD3);
	AddPolyn(*HEAD1, *HEAD2);
	PrintPolyn(*HEAD1);
	AddPolyn(*HEAD1, *HEAD3);
	PrintPolyn(*HEAD1);
}

void CreatePolyn(polynomial &P, int m) {
	polynomial *p = &P;
	while (m--) {
		int tmp1, tmp2;
		scanf("%d", &tmp1);
		scanf("%d", &tmp2);
		tmp = (polynomial*)malloc(sizeof(polynomial));
		tmp->data = tmp1;
		tmp->index = tmp2;
		p->next = tmp;
		p = p->next;
		p->next = NULL;
	}
}

void AddPolyn(polynomial &Pa, polynomial Pb) {
	polynomial *a = &Pa;
	polynomial *b = &Pb;
	polynomial *pa = a->next;
	polynomial *pb = b->next;
	while (pa && pb) {
		if (pa->index < pb->index) {
			a = pa;
			pa = pa->next;
		}
		else if (pa->index == pb->index) {
			pa->data += pb->data;
			if (pa->data == 0) {
				a->next = pa->next;
				pa->next = NULL;
				free(pa);
			}
			b->next = pb->next;
			free(pb);
			pa = a->next;
			pb = b->next;
		}
		else if (pa->index > pb->index) {
			b->next = pb->next;
			pb->next = pa;
			a->next = pb;
			pb = b->next;
		}
	}
	if (pb != NULL) {
		if (a->next != NULL) {
			pa->next = pb;
		}
		else a->next = pb;
	}
}

void PrintPolyn(polynomial P) {
	polynomial *p = &P;
	if(p->next==NULL) printf("<0,0>\n");
	while (p->next != NULL) {
		p = p->next;
		if(p->next!=NULL)	printf("<%d,%d>,", p->data, p->index);
		else printf("<%d,%d>\n", p->data, p->index);
	}
	
}
