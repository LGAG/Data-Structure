
#include <stdio.h>  
#include <stdlib.h>  

typedef struct node
{
	int         data;
	struct node * next;
} NODE;

void output(NODE *, int);
void change(int, int, NODE *);

void output(NODE * head, int kk)
{
	int k = 0;

	printf("0.");
	while (head->next != NULL && k < kk)
	{
		printf("%d", head->next->data);
		head = head->next;
		k++;
	}
	printf("\n");
}

int main()
{
	int n, m, k;
	NODE * head;

	scanf("%d%d%d", &n, &m, &k);
	head = (NODE *)malloc(sizeof(NODE));
	head->next = NULL;
	head->data = -1;
	change(n, m, head);
	output(head, k);
	return 0;
}


void change(int n, int m, NODE *head){
	NODE* num[m+2];
	for (int i = 0; i < m+2; i++) {
		num[i] = (NODE*)malloc(sizeof(NODE));
		num[i]->next = NULL;
	}
	if(n==0){
		NODE* p = (NODE*)malloc(sizeof(NODE));
		p->data=0;
		p->next=NULL;
		head->next=p;
		goto l;
	}
	for(int j=0;j<=m+2;j++){
		if(n == 0){
			head->next = NULL;
			break;
		} 
		NODE* p = (NODE*)malloc(sizeof(NODE));
		n = n * 10;
		p->data = n / m;
		p->next = NULL;
		head->next = p;
		int c=(n/10)%m;
		if (num[c]->next == NULL) num[c]->next = p;
		else {
			head->next = num[c]->next;
			break;
		}			
		head = head->next;
		n = n % m;
	}
	l: ;
}
