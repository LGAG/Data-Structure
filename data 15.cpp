#include <stdio.h> 
int main(void){
	int n,I,J;
	scanf("%d",&n);
	int tree[1000+1]={0}; //assume the n less than 1000
	for(int i=0;i<n;i++){
		scanf("%d",&tree[i+1]); // store numbers from index 1.
	}
	scanf("%d %d",&I,&J); //make sure 1 <= I , J <= n.
	if(tree[1] == 0){
		printf("ERROR: T[1] is NULL\n");
		return 3;
	}
	if(tree[I] == 0) printf("ERROR: T[%d] is NULL\n",I);
	else if(tree[J] == 0) printf("ERROR: T[%d] is NULL",J);
	else{
		while(1){
			if(I==1 || J==1){
				printf("1 %d\n",tree[1]);
				return 2;
			}
			if(I < J){
				J = J/2;
			}
			else if(I > J){
				I = I/2;
			}
			else if(I == J){
				printf("%d %d\n",I,tree[I]);
				return 1;
			}
		}
	}
}
