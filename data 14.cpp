#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
	ATOM, LIST
	//ATOM = 0: 原子 , LIST = 1: 子表 
} ElemTag;

typedef struct GLNode {
	ElemTag tag;
	union {
		char atom;
		struct {
			struct GLNode *hp, *tp;
		} ptr;
	};
} GLNode;

typedef GLNode *Glist;


void createGlist(Glist &g, char *str) {
	if (strcmp(str, "()") == 0) {
		g = (Glist)malloc(sizeof(GLNode));
		g->tag = ATOM;
		g->atom = '1';
	}
	else {
		if (strlen(str) == 1) {
			g = (Glist)malloc(sizeof(GLNode));
			g->tag = ATOM;
			g->atom = str[0];
		}
		else {
			g = (Glist)malloc(sizeof(GLNode));
			g->tag = LIST;
			Glist p = (Glist)malloc(sizeof(GLNode));
			p = g;
			int len = strlen(str);
			char sub[1000] = { 0 };
			for (int i = 1; i < len - 1; i++) {
				sub[i - 1] = str[i];
			}
			sub[len - 2] = '\0';
			do {
				char hsub[1000] = { 0 };
				int n = strlen(sub);
				int i = 0, k = 0;
				while (1) {
					if (sub[i] == '(') k++;
					else if (sub[i] == ')') k--;
					i++;
					if (i >= n || (sub[i] == ',' && k == 0)) break;
				}
				if (i < n) {
					for (int x = 0; x < i; x++) {
						hsub[x] = sub[x];
					}
					hsub[i] = '\0';
					for (int x = i + 1; x <= n - 1; x++) {
						sub[x - i - 1] = sub[x];
					}
					sub[n - i - 1] = '\0';
				}
				else {
					for (int i = 0; i < n; i++) {
						hsub[i] = sub[i];
						sub[i] = 0;
					}
				}
				createGlist(p->ptr.hp, hsub);
				if (sub[0] != 0) {
					p->ptr.tp = (Glist)malloc(sizeof(GLNode));
					p->tag = LIST;
					p = p->ptr.tp;
				}
			} while (sub[0] != 0);
			p->ptr.tp = NULL;
		}
	}
}
void printGlist(Glist g) {
	printf("(");
	while (1) {
		if (g->ptr.hp->tag == ATOM) {
			if (g->ptr.hp->atom == '1') printf("()");
			else printf("%c", g->ptr.hp->atom);
			if (g->ptr.tp != NULL) {
				printf(",");
				g = g->ptr.tp;
			}
			else {
				printf(")");
				break;
			}
		}
		else if (g->ptr.hp->tag == LIST) {
			printGlist(g->ptr.hp);
			if (g->ptr.tp == NULL) {
				printf(")");
				break;
			}
			else if (g->ptr.tp != NULL) {
				g = g->ptr.tp;
				printf(",");
			}
		}
	}
}

int main(void) {
	char str[1000] = { 0 };
	int count = 0;
	while (1) {
		scanf("%c", &str[count]);
		if (str[count] == '\n') {
			str[count] = '\0';
			break;
		}
		count++;
	}
	Glist g;
	g = (Glist)malloc(sizeof(GLNode));
	createGlist(g, str);
	Glist temp;
	temp = (Glist)malloc(sizeof(GLNode));
	temp = g;
	printf("generic list: ");
	printGlist(temp);
	printf("\n");
	while (1) {
		int op;
		scanf("%d", &op);
		if (op == 1) {
			printf("destroy tail\nfree list node\ngeneric list: ");
			if (g->ptr.hp == NULL || g->ptr.hp->atom == '1') {
				printf("()\n");
				break;
			}
			else if (g->ptr.hp->tag == ATOM) {
				printf("%c\n", g->ptr.hp->atom);
				break;
			}
			g = g->ptr.hp;
			Glist tmp = g;
			printGlist(tmp);
			printf("\n");
		}
		else if (op == 2) {
			printf("free head node\nfree list node\ngeneric list: ");
			if (g->ptr.tp == NULL) {
				printf("()\n");
				break;
			}
			g = g->ptr.tp;
			Glist tmp;
			tmp = (Glist)malloc(sizeof(GLNode));
			tmp = g;
			printGlist(tmp);
			printf("\n");
		}
	}
}
