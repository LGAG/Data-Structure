#include <stdio.h>

#define Cutoff (3)

int Median3(int A[], int Left, int Right){
	int Center = (Left + Right) / 2;
	
	if(A[Left] > A[Center]){
		swap;
	}
	if(A[Left] > A[Right]){
		swap;
	}
	if(A[Center] > A[Right]){
		swap;
	}
	
	swap;
	return A[Right-1];
}

void Qsort(int A[], int Left, int Right);

int main(void){
	int A[10000]={0};
	char tmp;
	int count=0;
	while(1){
		scanf("%d%c",&A[count],&tmp);
		if(tmp=='\n') break;
		count++;
	}
	Qsort(A,0,count);
}
