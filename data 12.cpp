#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stock {
	int stockid;
	double price;
	int quantity;
	char type;
	int orderid;
	struct stock *next;
	int size;
} stock;

int Sell(stock *q, stock *s) {
	while (q->next != NULL) {
		q = q->next;
		if (q->quantity == 0) {
			continue;
		}
		if (q->stockid == s->stockid) {		
			if ((int)(s->price * 2 + 0.1) >= (int)(q->price * 2 + 0.1)) {
				int min = s->quantity < q->quantity ? s->quantity : q->quantity;
				printf("deal--price:%6.1lf  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (s->price + q->price) / 2.0, min, s->orderid, q->orderid);
				s->quantity -= min;
				q->quantity -= min;
				if (s->quantity == 0) {
					return 0;
				}
			}
		}
	}
	return 1;
}

int Buy(stock *q, stock *s) {
	while (q->next != NULL) {
		q = q->next;
		if (q->quantity == 0) {
			continue;
		}
		if (q->stockid == s->stockid) {
			if ((int)(s->price * 2 + 0.1) <= (int)(q->price * 2 + 0.1)) {
				int min = s->quantity < q->quantity ? s->quantity : q->quantity;
				printf("deal--price:%6.1lf  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (s->price + q->price) / 2.0, min, s->orderid, q->orderid);
				s->quantity -= min;
				q->quantity -= min;
				if (s->quantity == 0) {
					return 0;
				}
			}
		}
	}
	return 1;
}

int pushbuy(stock *q, stock *s) {
	int flag = 0;
	if (q->next == NULL) {
		flag = 2;
		q->next = s;
		s->next = NULL;
	}
	else {
		stock *tmp = (stock*)malloc(sizeof(stock));
		while (q->next != NULL) {
			tmp = q;
			q = q->next;
			if (s->stockid == q->stockid) {
				if (s->price > q->price) {
					s->next = q;
					tmp->next = s;
					flag = 1;
					return flag;
				}
			}
		}
	}
	if (flag == 0) {
		q->next = s;
		s->next = NULL;
	}
	return flag;
}

int pushsell(stock *q, stock *s) {
	int flag = 0;
	if (q->next == NULL) {
		flag = 2;
		q->next = s;
		s->next = NULL;
	}
	else {
		stock *tmp = (stock*)malloc(sizeof(stock));
		while (q->next != NULL) {
			tmp = q;
			q = q->next;
			if (q->stockid == s->stockid) {
				if (s->price < q->price) {
					s->next = q;
					tmp->next = s;
					flag = 1;
					return flag;
				}
			}
		}
	}
	if (flag == 0) {
		q->next = s;
		s->next = NULL;
	}
	return flag;
}

int searchbuy(stock *q, int s) {
	int index = 0;
	while (q->next != NULL) {
		q = q->next;
		if (q->stockid == s && q->quantity >0) {
			index = 1;
			printf("orderid: %04d, stockid:%04d, price: %6.1lf, quantity: %4d, b/s: %c\n", q->orderid, q->stockid, q->price, q->quantity, q->type);
		}
	}
	return index;
}

int searchsell(stock *q, int s) {
	int index = 0;
	while (q->next != NULL) {
		q = q->next;
		if (q->stockid == s && q->quantity>0) {
			index = 1;
			printf("orderid: %04d, stockid:%04d, price: %6.1lf, quantity: %4d, b/s: %c\n", q->orderid, q->stockid, q->price, q->quantity, q->type);
		}
	}
	return index;
}

int DEL(stock *q, int s) {
	while (q->next != NULL) {
		q = q->next;
		if (q->orderid == s && q->quantity > 0) {
			printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1lf, quantity: %4d, b/s: %c\n", q->orderid,q->stockid ,q->price, q->quantity, q->type);
			q->quantity = 0;
			return 0;
		}
	}
	return -1;
}

int main(void) {
	int count = 0;
	stock *buy = (stock*)malloc(sizeof(stock));
	stock *sell = (stock*)malloc(sizeof(stock));
	sell->next = NULL;
	sell->size = 0;
	sell->quantity = 0;
	buy->next = NULL;
	buy->size = 0;
	buy->quantity = 0;
	while (1) {
		int number;
		scanf("%d", &number);
		if (number == 1) {
			int flag = 0;
			stock *s = (stock*)malloc(sizeof(stock));
			s->next = NULL;
			scanf("%d %lf %d %c", &s->stockid, &s->price, &s->quantity, &s->type);
			
			count++;
			s->orderid = count;
			printf("orderid: %04d\n", count);
			//if (s->quantity == 0)continue;
			if (s->type == 'b') flag = Sell(sell, s);
			else if (s->type == 's') flag = Buy(buy, s);
			if (flag == 1) {
				if (s->type == 'b') flag = pushbuy(buy, s);
				else if (s->type == 's') flag = pushsell(sell, s);
			}
		}
		else if (number == 2) {
			int order;
			scanf("%d", &order);
			printf("buy orders:\n");
			searchbuy(buy, order);
			printf("sell orders:\n");
			searchsell(sell, order);
		}
		else if (number == 3) {
			int x, f1 = 0, f2 = 0;
			scanf("%d", &x);
			f1 = DEL(buy, x);
			f2 = DEL(sell, x);
			if (f1 == -1 && f2 == -1) {
				printf("not found\n");
			}
		}
		else if (number == 0) break;
	}
}
