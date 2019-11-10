#include <stdio.h>
#include <stack>
#include <iostream>

typedef struct {
	int x;
	int y;
	int north;
	int east;
	int south;
	int west;
	int block;
}point;

using namespace std;
int main(void) {
	stack <point> sta;
	int n, m;
	scanf("%d %d", &n, &m);
	point map[101][101];
	int num[101][101] = { 0 };
	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &num[i][j]);
		}
	}*/
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &map[i][j].block);
			getchar();
			map[i][j].x = i;
			map[i][j].y = j;
			if (i != 0)map[i][j].north = 0;
			else map[i][j].north = 1;
			if (i != m - 1)map[i][j].south = 0;
			else map[i][j].south = 1;
			if (j != 0)map[i][j].west = 0;
			else map[i][j].west = 1;
			if (j != n - 1)map[i][j].east = 0;
			else map[i][j].east = 1;
		}
	}
	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%d ", map[i][j].block);
		}
		printf("\n");
	}*/
	sta.push(map[0][0]);
	while (!sta.empty()) {
		//printf("map[%d][%d]\n", sta.top().x, sta.top().y);
		if (sta.top().x == n - 1 && sta.top().y == n - 1) break;
		point t = sta.top();
		if (map[t.x][t.y].south == 0) {
			//printf("t.south=%d,t+1.block=%d\n",t.south,t.block);
			if (map[t.x + 1][t.y].block == 0) {
				map[t.x][t.y].south = 1;
				map[t.x + 1][t.y].north = 1;
				sta.push(map[t.x + 1][t.y]);
				continue;
			}
			else {
				map[t.x][t.y].south = 1;
			}
		}
		if (map[t.x][t.y].east == 0) {
			//printf("t.east=%d,t+1.block=%d\n", t.east, t.block);
			if (map[t.x][t.y + 1].block == 0) {
				map[t.x][t.y].east = 1;
				map[t.x][t.y + 1].west = 1;
				sta.push(map[t.x][t.y + 1]);
				continue;
			}
			else {
				map[t.x][t.y].east = 1;
			}
		}
		if (map[t.x][t.y].north == 0) {
			//printf("t.north=%d,t+1.block=%d\n", t.north, t.block);
			if (map[t.x - 1][t.y].block == 0) {
				map[t.x][t.y].north = 1;
				map[t.x - 1][t.y].south = 1;
				sta.push(map[t.x - 1][t.y]);
				continue;
			}
			else {
				map[t.x][t.y].north = 1;
			}
		}
		if (map[t.x][t.y].west == 0) {
			//printf("t.west=%d,t+1.block=%d\n", t.west, t.block);
			if (map[t.x][t.y - 1].block == 0) {
				map[t.x][t.y].west = 1;
				map[t.x][t.y - 1].east = 1;
				sta.push(map[t.x][t.y - 1]);
				continue;
			}
			else {
				map[t.x][t.y].west = 1;
			}
		}
		sta.pop();
	}
	if (sta.empty()) {
		printf("There is no solution!\n");
		return 0;
	}
	stack <point> tmp;
	while (!sta.empty()) {
		tmp.push(sta.top());
		sta.pop();
	}
	while (1) {
		if (tmp.empty()) break;
		point t = tmp.top();
		tmp.pop();
		if (tmp.empty()) printf("<%d,%d> \n", t.x + 1, t.y + 1);
		else printf("<%d,%d> ", t.x + 1, t.y + 1);
	}
}
