#include <stdio.h>

//#define LeftChild( i ) ( 2 * (i) + 1 )
//
//
//
//void perdown (int A[], int i, int N){
//	int Child;
//	int tmp;
//	
//	for(tmp = A[i]; LeftChild( i ) < N; i = Child){
//		Child = LeftChild( i );
//		if(Child != N-1 && A[Child + 1] > A[Child]){
//			Child++;
//		}
//		if(tmp < A[Child]){
//			A[i] = A[Child];
//		}
//		else{
//			break;
//		}
//	}
//	A[i] = tmp;
//}
//
//void heapsort(int A[], int n){
//	int i;
//	for(i = n/2;i>=0;i--){
//		perdown(A,i,n);
//	}
//	for(i = n-1;i>0;i--){
//		int tmp = A[0];
//		A[0]=A[i];
//		A[i]=tmp;
//		perdown(A,0,i);
//	}
//}

int heap[1000000];



int main(void){
	int size;
	int temp;
	scanf("%d",&size);
	getchar();
	for(int i = 1;i<=size;i++){
		scanf("%d",&heap[i]);
		getchar();
		
	}
	
	for(int i=size/2;i>=1;i--){
		int j=i;
		if(2*j+1>size){
			if(heap[2*j]>heap[j]){
				int tmp=heap[j];
				heap[j]=heap[j*2];
				heap[j*2]=tmp;
			}
		}
		else{
			if(heap[2*j]>=heap[2*j+1]){
				if(heap[2*j]>heap[j]){
					int tmp=heap[j];
					heap[j]=heap[j*2];
					heap[j*2]=tmp;
					j=j*2;
				}
			}
			else{
				if(heap[2*j+1]>heap[j]){
					int tmp=heap[j];
					heap[j]=heap[j*2+1];
					heap[j*2+1]=tmp;
					j=j*2+1;
				}
			}
				while(1){
		if(j*2>size){
			break;
		}
		int a1=heap[j],a2=heap[j*2],a3=heap[2*j+1];
		int max;
		if(2*j+1>size){
			a3=a2-1;
		}
		if(a2>=a3){
			
			max=a2;
			if(max>heap[j]){
				temp = heap[j];
				heap[j]=heap[2*j];
				heap[2*j]=temp;
				j=2*j;
			}
			else{
				break;
			}
		}
		else{
			if(j*2+1>size){
				break;
			}
			max=a3;
			if(max>heap[j]){
				temp = heap[j];
				heap[j]=heap[2*j+1];
				heap[1+2*j]=temp;
				j=2*j+1;
			}
			else{
				break;
			}
		}
	}
		}
//		while(1){
//			if(j==0){
//				break;
//			}
//			int a1=heap[j],a2=heap[2*j],a3=heap[2*j+1];
//			int max;
//			if(2*j+1>size){
//				a3=a2-1;
//			}
//			if(a2<a3){
//				max = a3;
//				if(max > a1){
//					int tmp = heap[j];
//					heap[j]=heap[2*j+1];
//					heap[2*j+1]=tmp;
//					j=j/2;
//				}
//				else{
//					break;
//				}
//			}
//			else{
//				max = a2;
//				if(max > a1){
//					int tmp = heap[j];
//					heap[j]=heap[2*j];
//					heap[2*j]=tmp;
//					j=j/2;
//				}
//				else{
//					break;
//				}
//			}		
//		}
	}
	
	for(int j=1;j<=size;j++){
		printf("%d ",heap[j]);
	}
	
	
	
	temp = heap[size];
	heap[size]=heap[1];
	heap[1]=temp;
	
	int j=1;
	
	while(1){
		if(j*2>=size){
			break;
		}
		int a1=heap[j],a2=heap[j*2],a3=heap[2*j+1];
		int max;
		if(2*j+1>=size){
			a3=a2-1;
		}
		if(a2>=a3){
			
			max=a2;
			if(max>heap[j]){
				temp = heap[j];
				heap[j]=heap[2*j];
				heap[2*j]=temp;
				j=2*j;
			}
			else{
				break;
			}
		}
		else{
			if(j*2+1>=size){
				break;
			}
			max=a3;
			if(max>heap[j]){
				temp = heap[j];
				heap[j]=heap[2*j+1];
				heap[1+2*j]=temp;
				j=2*j+1;
			}
			else{
				break;
			}
		}
	}
	
	printf("\n");
	for(int j=1;j<size;j++){
		printf("%d ",heap[j]);
	}
	
	printf("\n");
	
	temp = heap[size-1];
	heap[size-1]=heap[1];
	heap[1]=temp;
	
	j=1;
	
	while(1){
		if(j*2>=size-1){
			break;
		}
		int a1=heap[j],a2=heap[j*2],a3=heap[2*j+1];
		int max;
		if(2*j+1>=size-1){
			a3=a2-1;
		}
		if(a2>=a3){
			max=a2;
			if(max>heap[j]){
				temp = heap[j];
				heap[j]=heap[2*j];
				heap[2*j]=temp;
				j=2*j;
			}
			else{
				break;
			}
		}
		else{
			if(j*2+1>=size-1){
				break;
			}
			max=a3;
			if(max>heap[j]){
				temp = heap[j];
				heap[j]=heap[2*j+1];
				heap[1+2*j]=temp;
				j=2*j+1;
			}
			else{
				break;
			}
		}
	}
	
	for(int j=1;j<size-1;j++){
		printf("%d ",heap[j]);
	}
	printf("\n");
}
