/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

/*
��һ��ͷ����˫��ѭ�������ʾ�����Ա�
L =��a1, a2, ���� , an��
��д��һ��ʱ�临�Ӷ�ΪO(n)���㷨����L����Ϊ��
L =��a1, a2, ����, an-1, an, an-1, ����, a2, a1��
*/

#include <stdio.h>  
#include <stdlib.h>   

typedef int ElemType;
typedef struct DuLNode {
	ElemType        data;      // ������  
	struct DuLNode  *prior;    // ָ��ǰ����ָ����  
	struct DuLNode  *next;     // ָ���̵�ָ����  
} DuLNode, *DuLinkList;

// ����ԭ��   
void out_next(DuLinkList);
void out_prior(DuLinkList);
void rcopy(DuLinkList);     //������Ҫ��д�ĺ���   

// ��������   
void out_next(DuLinkList DHead)
{
	DuLinkList p = DHead->next;
	while (p != DHead)
	{
		printf("%d,", p->data);
		p = p->next;
	}
	printf("\n");
}
void out_prior(DuLinkList DHead)
{
	DuLinkList p = DHead->prior;
	while (p != DHead)
	{
		printf("%d,", p->data);
		p = p->prior;
	}
	printf("\n");
}

int main()
{
	DuLinkList DHead, p;
	int num;

	DHead = (DuLNode*)malloc(sizeof(DuLNode));
	DHead->data = -1;
	DHead->prior = DHead->next = DHead;       // ���ɱ�ͷ  

	scanf("%d", &num);
	while (num != -1)
	{
		p = (DuLNode*)malloc(sizeof(DuLNode));
		p->data = num;
		p->next = DHead->next;    // 1.����p��next��   
		DHead->next = p;     // 2.����DHead��next��  
		p->next->prior = p;       // 3.����p��next��prior��  
		p->prior = DHead;        // 4.����p��prior��  
		scanf("%d", &num);
	}
	printf("Link  next:");  out_next(DHead);
	printf("Link prior:");  out_prior(DHead);
	rcopy(DHead);
	printf("NewL  next:");  out_next(DHead);
	printf("NewL prior:");  out_prior(DHead);
	return 0;
}
/**************************************/
void rcopy(DuLinkList DHead)
{
	//This function is wating for you.
	DuLinkList p = DHead->next;
	DuLinkList q = DHead->next;
	while (p->next != p->prior) {
		p = p->next;
		q = q->next;
	}
	while (1) {
		p->next = q->prior;
		q = q->prior;
		if (q->next == q->next->prior) break;
		//q->next->prior = NULL;
	}
}
/***************************************/

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */
