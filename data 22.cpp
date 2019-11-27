#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <algorithm>

typedef struct vex{
	int vexh;
	int vext;
	int weight;
	int flag;
}vex;

typedef struct point{
	int data;
	int srt;
}point;

int comp(const void *p1,const void *p2){
	vex *c=(vex*)p1;
	vex *d=(vex*)p2;
	return d->weight<c->weight?1:-1;
}

using namespace std;
int main(void){
	int N,M;
	vex v[4000];  	//M
	point p[2000];	//N
	scanf("%d %d",&N,&M);
	getchar();
	for(int i=0;i<=N;i++){
		p[i].data=i;
		p[i].srt=i;
	}
	for(int i=0;i<M;i++){
		int tmp1,tmp2,tmp3;
		scanf("%d %d %d",&tmp1,&tmp2,&tmp3);
		v[i].vexh=tmp1;
		v[i].vext=tmp2;
		v[i].weight=tmp3;
		v[i].flag=0;
		getchar();
	}
	int count=0;
	qsort(v,M,sizeof(v[0]),comp);
//	for(int i=0;i<M;i++){
//		printf("%d : <vexh = %d> <vext = %d> <weight = %d>\n",i,v[i].vexh,v[i].vext,v[i].weight);
//	}
	for(int i=0;i<N-1;i++){
		int f=-1;
		for(int j=0;j<M;j++){
			if(p[v[j].vexh].srt!=p[v[j].vext].srt && v[j].flag == 0){
				f=j;
				v[j].flag=1;
				count+=v[j].weight;
				//printf("<p[v[%d].vexh].srt = %d> <p[v[%d].vext].srt = %d>  count=%d\n",j,p[v[j].vexh].srt,j,p[v[j].vext].srt,count);
				break;
			}
		}
		if(f==-1){
			printf("-1\n");
			return 0;
		}
		int ff=p[v[f].vext].srt;
		int gg=p[v[f].vexh].srt;
		
		//printf("ff=%d  %d\n",ff,p[v[f].vext].srt);
		//p[v[f].vext].srt=p[v[f].vexh].srt;
		//printf("now change the srt equals %d to %d:\n",p[v[f].vext].srt,p[v[f].vexh].srt);
		for(int j=1;j<=N;j++){
			//printf("srt[%d]=%d   ",j,p[j].srt);
			if(ff==p[j].srt){
				p[j].srt=gg;
				//printf("<%d> ",j);
			}
		}
	//	printf("\n");
//		for(int j=1;j<=N;j++){
//			printf("p[%d].data=%d , p[%d].srt=%d\n\n",j,p[j].data,j,p[j].srt);
//		}
	}
	printf("%d\n",count);
}
