#include <stdio.h>

#define Cutoff (5)

int stack[1000];
int head = 0;
int tail = 0;

void Swap(int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void insertsort(int A[], int n) {
	int j,p;
	int tmp;
	for(p = 1; p < n; p++){
		tmp = A[p];
		for(j = p; j > 0 && A[j - 1] > tmp; j--){
			A[j] = A[j - 1];
		}
		A[j] = tmp;
	}
}

int Median3(int A[], int Left, int Right){
	int Center = (Left + Right) / 2;
	
	if(A[Left] > A[Center]){
		Swap(&A[Left], &A[Center]);
	}
	if(A[Left] > A[Right]){
		Swap(&A[Left], &A[Right]);
	}
	if(A[Center] > A[Right]){
		Swap(&A[Center], &A[Right]);
	}

	Swap(&A[Center], &A[Right - 1]);
	return A[Right-1];
}

void Qsort(int A[], int Left, int Right){
	int i,j;
	int pivot;
	
	if(Left + Cutoff <= Right){
		pivot = Median3(A,Left,Right);
		stack[tail] = pivot;
		tail++;
		i = Left;
		j = Right - 1;
		while(1){
			while(A[++i] < pivot);
			while(A[--j] > pivot);
			if(i<j){
				Swap(&A[i],&A[j]);
			}
			else{
				break;
			}
		}
		Swap(&A[i], &A[Right - 1]);
		
		Qsort(A,Left,i-1);
		Qsort(A,i+1,Right);
	}
	else{
		insertsort(A+Left,Right - Left + 1);
	}
}

int main(void){
	int A[10000]={0};
	char tmp;
	int count=0;
	while(1){
		int a = scanf("%d",&A[count],&tmp);
		//printf("    a = %d                         %d  %d\n",a,A[count],tmp);
		if(a == 0){
			//printf("count = %d\n",count);
			count--;
			getchar();
			getchar();
			break;
		}
		count++;
	}
	Qsort(A,0,count);
	printf("After Sorting:\n");
	for(int i=0;i<=count;i++){
		printf("%d ",A[i]);
	}
	printf("\nMedian3 Value:\n");
	if(tail == 0){
		printf("none\n");
	}
	else{
		for(int i=0;i<tail;i++){
			printf("%d ",stack[i]);
		}
		printf("\n");
	}
}
