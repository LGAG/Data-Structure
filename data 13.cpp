#include <stdio.h>
#include <stdlib.h>

typedef struct Triple{
	int i , j;
	int e;
}Triple;

typedef struct TSMatrix{
	Triple data [200 + 1];
	int mu,nu,tu;
}TSMatrix;

void insert(TSMatrix *M, Triple T){
	M->data[M->tu] = T;
	M->tu++;
}

int main(void){
	TSMatrix *M = (TSMatrix*)malloc(sizeof(TSMatrix));
	TSMatrix *N = (TSMatrix*)malloc(sizeof(TSMatrix));
	M->tu = 0;
	int a1,a2,a3;
	scanf("%d %d %d",&a1,&a2,&a3);
	while(a3--){
		int ei,ej,value;
		scanf("%d %d %d",&ei,&ej,&value);
		Triple elem;
		elem.i = ei;
		elem.j = ej;
		elem.e = value;
		insert(M , elem);
	}
	int num[200]={0};
	int cpot[200]={0};
	for(int t=0;t<M->tu;t++){
		num[M->data[t].j]++;
		if(M->data[t].j > M->nu) M->nu = M->data[t].j;
	}
	M->mu = M->data[M->tu-1].i;
	cpot[1] = 1;
	for(int t = 2 ; t <= a2;t++){
		cpot[t] = cpot[t-1] + num[t-1];
	}
	printf("处理前:\n");
	printf("num:");
	for(int x = 1 ; x <= a2 ; x++){
		printf("%d,",num[x]);
	}
	printf("\ncpot:");
	for(int x = 1 ; x <= a2 ; x++){
		printf("%d,",cpot[x]);
	}
	printf("\n");
	for(int p=0;p<M->tu;p++){
		int col = M->data[p].j;
		int q = cpot[col];
		N->data[q].i=M->data[p].j;
		N->data[q].j=M->data[p].i;
		N->data[q].e=M->data[p].e;
		cpot[col]++;
	}
	printf("处理后:\n");
	printf("num:");
	for(int x = 1 ; x <= a2 ; x++){
		printf("%d,",num[x]);
	}
	printf("\ncpot:");
	for(int x = 1 ; x <= a2 ; x++){
		printf("%d,",cpot[x]);
	}
	printf("\n");
	printf("输出的矩阵:\n");
	for(int x = 1 ; x <= M->tu ; x++){
		printf("%d,%d,%d\n",N->data[x].i,N->data[x].j,N->data[x].e);
	}
	
}
