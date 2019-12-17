#include <stdio.h>
#include <limits.h>

int main(void) {
	char alphabet[200] = { 0 };
	int ad[150][150];
	for (int i = 0; i < 150; i++) {
		for (int j = 0; j < 150; j++) {
			ad[i][j] = INT_MAX;
		}
	}
	int dist[150] = { 0 };
	for(int i=0;i<150;i++){
		dist[i]=INT_MAX;
	}
	char pre[150] = { 0 };
	int n, e;
	char root;
	scanf("%d,%d,%c", &n, &e, &root);
	getchar();
	for (int i = 0; i < e; i++) {
		char c1, c2;
		int value;
		int index1 = 0, index2 = 0;
		scanf("<%c,%c,%d>", &c1, &c2, &value);
		getchar();
		alphabet[c1] = c1;
		alphabet[c2] = c2;
		ad[c1][c2] = value;
	}
	int count = 0;
	for (int i = 'A'; i <= 'z'; i++) {
		if (alphabet[i] != 0) {
			if (alphabet[i] == root) dist[root] = INT_MAX;
			else dist[i] = ad[root][i];
			pre[i] = root;
			count++;
		}
	}
	for (int i = 0; i < n - 1; i++) {
		int min = INT_MAX;
		char minc;
		for (int j = 'A'; j <= 'z'; j++) {
			if (j != root && min > dist[j] && ad[j][j] != 1 && dist[j] != INT_MAX) {
				min = dist[j];
				minc = j;
			}
		}
		ad[minc][minc] = 1;
		for (int j = 'A'; j <= 'z'; j++) {
			if (j != root && j != minc && dist[minc] != INT_MAX && ad[minc][j] != INT_MAX && dist[minc] + ad[minc][j] < dist[j]) {
				dist[j] = dist[minc] + ad[minc][j];
			}
		}
	}
	for (int i = 'A'; i <= 'z'; i++) {
		if (alphabet[i] != 0) {
			if(i==root) printf("%c:0\n", alphabet[i]);
			else printf("%c:%d\n", alphabet[i], dist[i]);
		}
	}
}
