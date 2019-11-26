#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>

typedef struct ArcNode {
	int adjvex;
	struct ArcNode *nextarc;

}ArcNode;

typedef struct VNode {
	char data;
	ArcNode *firstarc;
	int vis;
}VNode,adjList[60];

using namespace std;
int main(void) {
	int count = 0;
	VNode node[100];
	while (1) {
		scanf("%c", &node[count].data);
		getchar();
		if (node[count].data == '*') {
			break;
		}
		node[count].firstarc = NULL;
		node[count].vis = 0;
		count++;
	}
	while (1) {
		int x1, x2;
		scanf("%d,%d", &x1, &x2);
		getchar();
		if (x1 == -1 && x2 == -1) {
			break;
		}
		ArcNode *n1, *n2;
		n1=(ArcNode*)malloc(sizeof(ArcNode));
		n2 = (ArcNode*)malloc(sizeof(ArcNode));
		n1->adjvex = x2;
		n2->adjvex = x1;
		
		n1->nextarc = node[x1].firstarc;
		node[x1].firstarc = n1;
		n2->nextarc = node[x2].firstarc;
		node[x2].firstarc = n2;
	}
	printf("the ALGraph is\n");
	for (int i = 0; i < count; i++) {
		printf("%c", node[i].data);
		ArcNode *tmp = node[i].firstarc;
		while (1) {
			if (tmp == NULL) {
				printf("\n");
				break;
			}
			printf(" %d", tmp->adjvex);
			tmp = tmp->nextarc;
		}
	}
	printf("the Breadth-First-Seacrh list:");
	queue<int> que;
	for(int i=0;i<count;i++){
		if(node[i].vis==0){
			que.push(i);
			node[i].vis = 1;
		}
		else{
			continue;
		}
		while (!que.empty()) {
			int temp = que.front();
			que.pop();
			ArcNode *tmp = node[temp].firstarc;
			printf("%c",node[temp].data);
			while (1) {
				if(tmp==NULL){
					break;
				}
				if(node[tmp->adjvex].vis==0){
					que.push(tmp->adjvex);
					node[tmp->adjvex].vis=1;
				}
				tmp=tmp->nextarc;
			}
		}		
	}
	printf("\n");
}
