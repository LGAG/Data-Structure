#include <stdio.h>
#include <stack>
#include<stdlib.h>
#include<string.h>
using namespace std;

typedef struct node2{
    int num;
    int value;
    int e;
    int l;
    struct node2 *next;
}Node2;

typedef struct VEX {
	char start;
	char end;
	int value;
}VEX;

typedef struct node{
    char name[10];
    int visited;
    int inDegree;
    int outDegree;
    struct node2 *next;
}Node;

typedef struct POINT {
	char data[5];
	int in;
	stack <int> sta;
	stack <int> s;
}POINT;

int sequence[100][100]={0};
int head;
int max_value = 0;
Node2* node2[500];
Node node[500];
int stack[500] = {-1};
int tail;
int vNum, eNum;
int topo = 0;
int Topolist[500];
int ve[500] = {0};
int vl[500] = {0};


int main(void) {
	VEX vex[100];
	POINT point[100];
	char str[1000];
	int n, m;
	scanf("%d,%d", &n, &m);
	vNum=n;
	eNum=m;
	getchar();
	int k=0;
    int qtemp=0;
    int len=0;
	for (int i = 0; i < n; i++) {
		int count = 0;
		while (1) {
			char tmp;
			scanf("%c", &tmp);
			str[len]=tmp;
			len++;
			if (tmp == ',' || tmp == '\n'){
				break;
			}
			point[i].data[count] = tmp;
			count++;
		}
		point[i].data[count] = '\0';
		point[i].in = 0;
	}
	str[len]='\0';
	for(int i=0;i<strlen(str);i++){
        if(str[i]!=','){
            node[k].name[qtemp++]=str[i];
        }
        else {
            node[k].name[qtemp]='\0';
            node[k].inDegree = 0;
            node[k].outDegree = 0;
            node[k].next = NULL;
            node[k].visited = 0;
            k++;
            qtemp=0;
        }
    }
	for (int i = 0; i < m; i++) {
		getchar();
		scanf("%d,%d,%d", &vex[i].start, &vex[i].end, &vex[i].value);
		getchar();
		point[vex[i].end].in++;
		printf("vex[%d]=%d\n",i,vex[i].end);
		getchar();
		point[vex[i].start].sta.push(vex[i].end);
		point[vex[i].start].s.push(vex[i].end);
	}
	printf("----------------------------------\n");
	int flag=0;
	for(int i=0;i<n;i++){
		printf("point[%d] = %d\n",i,point[i].in);
	}
	for(int i=0;i<n;i++){
		if(point[i].in==0){
			if(i==0) {
				printf("%s",point[i].data);
				flag++;
				head=i;
				point[i].in=-1;
			}
			else {
				//printf("-%s",point[i].data);
				point[i].in=-1;
			}
			tail=i;
		}
	}
	for (int i = 0; i < n; i++) {
		if(point[i].in==-1 && i!=0) continue;
		while (!point[i].sta.empty()) {
			point[point[i].sta.top()].in--;
			point[i].sta.pop();
		}
		for(int j=0;j<n;j++){
			if(point[j].in==0){
				if(flag==0) {
					printf("%s",point[j].data);
					flag++;
					point[j].in=-1;
					head=j;
				}
				else {
					printf("-%s",point[j].data);
					point[j].in=-1;
				}
				tail=j;
			}
		}
	}
	
}

