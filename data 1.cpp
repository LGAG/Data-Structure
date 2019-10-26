#include <stdio.h>
#include <iostream>
#include <queue>
using namespace std;
int main(void)
{
	int n,k,m;
	scanf("%d,%d,%d",&n,&k,&m);
	if(n<1||k<1||m<1) printf("n,m,k must bigger than 0.\n");
	else if(k>n) printf("k should not bigger than n.\n");
	else{
		queue<int> que;
		queue<int> list;
		for(int i=k;i<=n;i++) que.push(i);
		for(int i=1;i<k;i++) que.push(i);
		int count=0,flag=0;
		while(1){
			for(int i=1;i<m;i++){
				int tmp=que.front();
				que.pop();
				que.push(tmp);
			}
			int tmp=que.front();
			que.pop();
			list.push(tmp);
			count++;
			if(count==n) break;
		}
		for(int i=1;i<=n;i++){
			if((i-1)%10==0) printf("%d",list.front());
			else printf(" %d",list.front());
			if(i%10==0) printf("\n");
			list.pop();
		}
	}
	
}
