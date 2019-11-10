#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stock {
	char order[4];
	int o;
	double price;
	int number;
	char type;
	char code[4];
	int orderid;
	struct stock *next =NULL;
} stock;

typedef struct {
	stock *head;
	stock *tail;
	int size;
}Q;

void initialize(Q *q) {
	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
}

void del(Q *q, stock *s) {
	if (q->size == 0) printf("Not Found\n");
	else if (q->size == 1) {
		stock *tmp = (stock*)malloc(sizeof(stock));
		tmp = q->head;
		if (tmp->o == s->o) {
			q->head = NULL;
			q->tail = NULL;
			q->size = 0;
			free(tmp);
		}
		else printf("Not Found\n");
	}
	else {
		stock *tmp = (stock*)malloc(sizeof(stock));
		tmp = q->head;
		stock *p = (stock*)malloc(sizeof(stock));
		p = q->head;

		int count = 0;
		int flag = -1;
		while (tmp != NULL) {
			p = tmp;

			if (tmp->o == s->o) {
				if (tmp == q->head) {
					if (tmp->next != NULL) {
						q->head = tmp->next;
						p = tmp;
						q->size--;
						flag = 2;
						tmp = tmp->next;
						free(p);
					}
					else {
						printf("???\n");
					}
				}
				else {
					p->next = tmp->next;
					stock *temp = (stock*)malloc(sizeof(stock));
					temp = tmp;
					tmp = tmp->next;
					q->size--;
					free(temp);
					flag = 2;
				}
			}
			else tmp = tmp->next;
		}
		if (flag == -1) printf("Not Found\n");
	}
}

int DEL(Q *q, int s) {
	if (q->size == 0) return 0;
	else if (q->size == 1) {
		stock *tmp = (stock*)malloc(sizeof(stock));
		tmp = q->head;
		if (tmp->orderid == s) {
			q->head = NULL;
			q->tail = NULL;
			q->size = 0;
			printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1lf, quantity: %4d, b/s: %c\n", tmp->orderid, tmp->o, tmp->price, tmp->number, tmp->type);
			free(tmp);
		}
		else return 0;;
	}
	else {
		stock *tmp = (stock*)malloc(sizeof(stock));
		tmp = q->head;
		stock *p = (stock*)malloc(sizeof(stock));
		p = q->head;

		int count = 0;
		int flag = -1;
		while (tmp != NULL) {
			p = tmp;
			

			if (p->orderid == s) {
				if (p == q->head) {
					if (p->next != NULL) {
						q->head = p->next;
						q->size--;
						printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1lf, quantity: %4d, b/s: %c\n", p->orderid, p->o, p->price, p->number, p->type);
						free(p);
						return 1;
					}
					else {
						printf("???\n");
					}
				}
				else {
					stock *x = (stock*)malloc(sizeof(stock));
					x=q->head;
					while(x->next!=p){
						x=x->next;
					}
					x->next = p->next;
					printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1lf, quantity: %4d, b/s: %c\n", p->orderid, p->o, p->price, p->number, p->type);
					free(p);
					return 1;
				}
			}
			tmp = tmp->next;
		}
		if (flag == -1) return 0;;
	}
	return 1;
}

int push_buy(Q *q, stock *s) {
	if (s->number == 0) return -2;
	if (q->size == 0) {
		q->head = s;
		q->tail = s;
		q->size++;
		return 1;
	}
	else {
		stock *p = (stock*)malloc(sizeof(stock));
		p = q->head;
		while (1) {

			if (p->next == NULL) {
				q->tail->next = s;
				q->tail = s;
				q->size++;
				return 2;
			}
			else if (p->next->o == s->o && s->price > p->next->price) {
				s->next = p->next;
				p->next = s;
				return 3;
			}
			p = p->next;
		}
	}
}

int push_sale(Q *q, stock *s) {
	if (s->number == 0) return -2;
	if (q->size == 0) {
		q->head = s;
		q->tail = s;
		q->size++;
		return 1;
	}
	else {
		stock *p = (stock*)malloc(sizeof(stock));
		p = q->head;
		while (1) {

			if (p->next == NULL) {
				q->tail->next = s;
				q->tail = s;
				q->size++;
				return 2;
			}
			else if (p->next->o == s->o && s->price < p->next->price) {
				s->next = p->next;
				p->next = s;
				return 3;
			}
			p = p->next;
		}
	}
}

void out_a_stock(stock *s) {
	//printf("orderid: %04d, stockid:%c%c%c%c, price: %.1f, quantity: %d, b/s: %c\n",s->orderid,s->order[0],s->order[1],s->order[2],s->order[3],s->price,s->number,s->type);
	printf("orderid: %04d, stockid:%04d, price: %6.1lf, quantity: %4d, b/s: %c\n", s->orderid, s->o, s->price, s->number, s->type);
}

int traverse(Q *q, int o) {
	stock *s = (stock*)malloc(sizeof(stock));
	if (q->size == 0) return -1;
	s = q->head;
	if (s->o == o) out_a_stock(s);
	while (s->next != NULL) {
		s = s->next;
		if (s->o == o) out_a_stock(s);
	}
	return 0;
}

int search_for_sale(Q *q, stock *s) {
	stock *tmp = (stock*)malloc(sizeof(stock));
	if (q->size == 0) return -1;
	tmp = q->head;
	if (tmp->o == s->o && ((int)(tmp->price * 2 + 0.1) <= (int)(s->price * 2 + 0.1))) {
		if (s->number > tmp->number) {
			stock *p = (stock*)malloc(sizeof(stock));
			p = q->head;
			printf("deal--price:%6.1lf  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (tmp->price + s->price) / 2.0, tmp->number, s->orderid, tmp->orderid);
			s->number -= tmp->number;
			del(q, p);
			tmp = q->head;
		}
		else if (s->number == tmp->number) {
			stock *p = (stock*)malloc(sizeof(stock));
			p = q->head;
			printf("deal--price:%6.1lf  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (tmp->price + s->price) / 2.0, tmp->number, s->orderid, tmp->orderid);
			s->number -= tmp->number;
			del(q, p);
			return 0;
		}
		else {
			printf("deal--price:%6.1lf  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (tmp->price + s->price) / 2.0, s->number, s->orderid, tmp->orderid);
			tmp->number -= s->number;
			return 0;
		}
	}
	while (tmp != NULL) {
		stock *p = (stock*)malloc(sizeof(stock));
		p = tmp;
		if (p->o == s->o && ((int)(p->price * 2 + 0.1) <= (int)(s->price * 2 + 0.1))) {
			if (s->number > p->number) {
				printf("deal--price:%6.1lf  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (p->price + s->price) / 2.0, p->number, s->orderid, p->orderid);
				s->number -= p->number;
				del(q, p);

			}
			else if (s->number == p->number) {
				printf("deal--price:%6.1lf  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (p->price + s->price) / 2.0, p->number, s->orderid, p->orderid);
				s->number -= p->number;
				del(q, p);
				return 0;
			}
			else {
				printf("deal--price:%6.1lf  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (p->price + s->price) / 2.0, s->number, s->orderid, p->orderid);
				tmp->number -= s->number;
				return 0;
			}
		}
		tmp = tmp->next;
	}
	return 1;
}

int search_for_buy(Q *q, stock *s) {
	stock *tmp = (stock*)malloc(sizeof(stock));
	if (q->size == 0) return -1;
	tmp = q->head;
	if (tmp->o == s->o && ((int)(tmp->price * 2 + 0.1) >= (int)(s->price * 2 + 0.1))) {
		if (s->number > tmp->number) {
			stock *p = (stock*)malloc(sizeof(stock));
			p = q->head;
			printf("deal--price:%6.1lf  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (tmp->price + s->price) / 2.0, tmp->number, s->orderid, tmp->orderid);
			s->number -= tmp->number;
			//tmp=tmp->next;

			del(q, p);
			tmp = q->head;
		}
		else if (s->number == tmp->number) {
			stock *p = (stock*)malloc(sizeof(stock));
			p = q->head;
			printf("deal--price:%6.1lf  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (tmp->price + s->price) / 2.0, tmp->number, s->orderid, tmp->orderid);
			s->number -= tmp->number;
			del(q, p);
			return 0;
		}
		else {
			printf("deal--price:%6.1lf  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (tmp->price + s->price) / 2.0, s->number, s->orderid, tmp->orderid);
			tmp->number -= s->number;
			return 0;
		}
	}
	while (tmp != NULL) {
		stock *p = (stock*)malloc(sizeof(stock));
		p = tmp;
		if (p->o == s->o && ((int)(tmp->price * 2 + 0.1) >= (int)(s->price * 2 + 0.1))) {
			if (s->number > p->number) {
				printf("deal--price:%6.1lf  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (p->price + s->price) / 2.0, p->number, s->orderid, p->orderid);
				s->number -= p->number;
				del(q, p);

			}
			else if (s->number == p->number) {
				printf("deal--price:%6.1lf  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (p->price + s->price) / 2.0, p->number, s->orderid, p->orderid);
				s->number -= p->number;
				del(q, p);
				return 0;
			}
			else {
				printf("deal--price:%6.1lf  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (p->price + s->price) / 2.0, s->number, s->orderid, p->orderid);
				tmp->number -= s->number;
				return 0;
			}
		}
		tmp = tmp->next;
	}
	return 1;
}


int main(void) {
	Q *head_buy = (Q*)malloc(sizeof(Q));
	Q *head_sale = (Q*)malloc(sizeof(Q));
	initialize(head_buy);
	initialize(head_sale);
	int count = 0;
	while (1) {
		char c = getchar();
		getchar();
		if (c == '0') break;
		else if (c == '1') {
			count++;
			stock *tmp = (stock*)malloc(sizeof(stock));
			for (int i = 0; i < 4; i++) {
				scanf("%c", &tmp->order[i]);
			}
			tmp->o = (tmp->order[0] - '0') * 1000 + (tmp->order[1] - '0') * 100 + (tmp->order[2] - '0') * 10 + (tmp->order[3] - '0');
			getchar();
			scanf("%lf", &tmp->price);
			getchar();
			scanf("%d", &tmp->number);
			getchar();
			tmp->type = getchar();
			getchar();

			tmp->next = NULL;

			tmp->orderid = count;
			tmp->code[0] = tmp->orderid / 1000;
			tmp->code[1] = (tmp->orderid - 1000 * (tmp->orderid / 1000)) / 100;
			tmp->code[2] = (tmp->orderid - tmp->code[0] * 1000 - tmp->code[1] * 100) / 10;
			tmp->code[3] = tmp->orderid % 10;

			if (tmp->type == 'b') {
				printf("orderid: %d%d%d%d\n", tmp->code[0], tmp->code[1], tmp->code[2], tmp->code[3]);
				if (head_sale->size != 0) {
					if (search_for_sale(head_sale, tmp) == 0) {
						free(tmp);
					}
					else {
						push_buy(head_buy, tmp);
					}
				}
				else {
					push_buy(head_buy, tmp);
				}
			}
			else {
				printf("orderid: %d%d%d%d\n", tmp->code[0], tmp->code[1], tmp->code[2], tmp->code[3]);
				//	printf("head_buy->size=%d\n",head_buy->size);
				if (head_buy->size != 0) {
					if (search_for_buy(head_buy, tmp) == 0) {
						free(tmp);
					}
					else {
						push_sale(head_sale, tmp);
					}
				}
				else {
					push_sale(head_sale, tmp);
				}
			}
		}
		else if (c == '2') {
			char inquiry[4];
			for (int i = 0; i < 4; i++) {
				inquiry[i] = getchar();
			}
			int INQUIRY = (inquiry[0] - '0') * 1000 + (inquiry[1] - '0') * 100 + (inquiry[2] - '0') * 10 + (inquiry[3] - '0');
			getchar();
			printf("buy orders:\n");
			traverse(head_buy, INQUIRY);
			printf("sell orders:\n");
			traverse(head_sale, INQUIRY);
		}
		else if (c == '3') {
			char ctrlz[4];
			for (int i = 0; i < 4; i++) {
				ctrlz[i] = getchar();
			}
			getchar();
			int CTRLZ = (ctrlz[0] - '0') * 1000 + (ctrlz[1] - '0') * 100 + (ctrlz[2] - '0') * 10 + (ctrlz[3] - '0');
			int index1 = DEL(head_buy, CTRLZ);
			int index2 = DEL(head_sale, CTRLZ);
			if (index1 == 0 && index2 == 0) printf("not found\n");
		}
	}
}
