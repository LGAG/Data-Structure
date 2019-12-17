#include <stdio.h>
//#include <algorithm>
#include<stdlib.h>
typedef struct D {
	int number;
	int order;
}D;

D d[300000];

int comp(const void *p1, const void *p2) {
	D *c = (D*)p1;
	D *d = (D*)p2;
	return d->order < c->order ? 1 : -1;
}

//using namespace std;
int main(void) {
	int n, search;
	scanf("%d", &n);
	getchar();
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &d[i].number, &d[i].order);
		getchar();
	}
	scanf("%d", &search);
	qsort(d, n, sizeof(d[0]), comp);
	for (int i = 0; i < n; i++) {
		printf("(%d %d)", d[i].number, d[i].order);
	}
	printf("\n");
	int low = 0;
	int high = n - 1;
	int mid = (low + high) / 2;
	while (low <= high) {
		mid = (low + high) / 2;
		if (d[mid].number == search) {
			printf("(%d %d)\n", d[mid].number, d[mid].order);
			return 1;
		}
		else if (search < d[mid].number) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}
	printf("error\n");
}
