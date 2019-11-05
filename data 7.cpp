#include <stdio.h>  
#include <stdlib.h>  
typedef struct node  
{   int         data;  
    struct node * next;  
} NODE;  
  
NODE * find( NODE * , int * );  
void outputring( NODE * );  
void change( int , int , NODE * );  
void outputring( NODE * pring )  
{   NODE * p;  
    p = pring;  
    if ( p == NULL )  
        printf("NULL");  
    else  
        do  {   printf("%d", p->data);  
            p = p->next;  
        } while ( p != pring );  
    printf("\n");  
    return;  
}  
  
int main()  
{   int n, m;  
    NODE * head, * pring;  
  
    scanf("%d%d", &n, &m);  
    head = (NODE *)malloc( sizeof(NODE) );  
    head->next = NULL;  
    head->data = -1;  
  
    change( n, m, head );  
    pring = find( head, &n );  
    printf("ring=%d\n", n);  
    outputring( pring );  
  
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
 
NODE * find( NODE * head, int * n ) 
{ 
	int count = 1;
	NODE* p1 = (NODE *)malloc(sizeof(NODE));
	NODE* p2 = (NODE *)malloc(sizeof(NODE));
	NODE* pa = (NODE *)malloc(sizeof(NODE));
	pa = head;
	p1 = head;
	p2 = head;
	while(1){
		if(p1 == p2 || p2 == NULL || p1 == NULL) break;
		p1 = p1->next;
		if(p1 == p2 || p2 == NULL || p1 == NULL) break;
		p2 = p2->next;
		if(p1 == p2 || p2 == NULL || p1 == NULL) break;
		p2 = p2->next;
		if(p1 == p2 || p2 == NULL || p1 == NULL) break;
		count ++;
	}
	if(p2 != NULL){
		p1=p1->next;
		p2=p2->next;
		p2=p2->next; 
		while(p1!=p2){
			p1 = p1->next;
			if (p2 == NULL) {
				*n=0;
				return p2;
			}
			p2 = p2->next;
			if (p2 == NULL) {
				*n=0;
				return p2;
			}
			p2 = p2->next;
			if (p2 == NULL) {
				*n=0;
				return p2;
			}
			count++;
		}
	}
	*n = count;
	if(p1 == NULL || p2 == NULL)  {
		return NULL;
	}
	while(1){
		int index=0;
		for(int i=0;i<count;i++){
			p2 = p2->next;
			if(pa == p2){
				index =1 ;
				break;
			}
		}
		if(index==1) break;
		pa = pa->next;
		if(pa == p2) break;
	}
	return pa;
} 
