#include <stdio.h>
#include <limits.h>

int main(void) {
	int n;
	int wpl = 0;
	scanf("%d", &n);
	getchar();
	int w[2 * 1000 + 1] = { 0 }, p[2 * 1000 + 1] = { 0 }, lch[2 * 1000 + 1] = { 0 }, rch[2 * 1000 + 1] = { 0 }, path[2 * 1000 + 1] = { 0 };  //n视有多少元素而定 
	for (int i = 0; i < n; i++) {
		scanf("%d", &w[i]);
		getchar();
	}
	int min1, min2;
	for (int i = 0; i < n - 1; i++) {
		min1 = INT_MAX;
		min2 = INT_MAX;
		int tmp1, tmp2;
		for (int k = 0; k < n + i; k++) {
			if (p[k] == 0) {
				if (w[k] < min1) {
					min1 = w[k];
					tmp1 = k;
				}
			}
		}
		p[tmp1] = n + i;
		for (int k = 0; k < n + i; k++) {
			if (p[k] == 0) {
				if (w[k] < min2) {
					min2 = w[k];
					tmp2 = k;
				}
			}
		}
		p[tmp2] = n + i;
		w[n + i] = w[tmp1] + w[tmp2];
	}
	for (int i = 0; i < n; i++) {
		int temp = i;
		while (1) {
			temp = p[temp];
			path[i]++;
			if (temp == 0) break;
		}
	}
	for (int i = 0; i < n; i++) {
		wpl += w[i] * (path[i] - 1);
	}
	printf("WPL=%d\n", wpl);
}
