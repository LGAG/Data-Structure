#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

/*
typedef struct col_stack {
	ElemType data;
	PCol next;
}Col_Stack, *PCol;

typedef struct row_stack {
	PCol next_col;
	PRow next_row;
	int size_c;
}Row_Stack, *PRow;
*/

typedef struct pile_stack {
	ElemType data;
	P_Pile next_row;
	P_Pile next_col;
}Pile_Stack, *P_Pile;

void initialize_pile(P_Pile pile) {
	pile->next_col = NULL;
	pile->next_row = NULL;
}

void Destroy_col(P_Pile pile) {
	free(pile);
}

void Destroy_row(P_Pile pile) {
	while (pile->next_col != NULL) {
		P_Pile tmp;
		tmp = (Pile_Stack*)malloc(sizeof(Pile_Stack));
		tmp = pile->next_col;
		pile->next_col = tmp->next_col;
		Destroy_col(tmp);
	}
}

void Destroy_pile(P_Pile pile) {
	while (pile->next_row != NULL) {
		P_Pile tmp;
		tmp = (Pile_Stack*)malloc(sizeof(Pile_Stack));
		tmp = pile->next_row;
		pile->next_row = tmp->next_row;
		Destroy_row(tmp);
	}
}

void push(P_Pile P, ElemType e) {
	P_Pile tmp;
	tmp = (Pile_Stack*)malloc(sizeof(Pile_Stack));
	tmp->next_col = P->next_row->next_col;
	tmp = P->next_row->next_col;
	tmp->data = e;
}

void push_a_stack(P_Pile P, P_Pile e_stack) {
	e_stack->next_row = P->next_row;
	P->next_row = e_stack;
}

int pop(P_Pile P) {
	if (P->next_row == NULL) {
		printf("error(null stack)!\n");
		return -1;
	}
	if (P->next_row->next_col == NULL) {
		printf("error(null elem)!\n");
		return -2;
	}
	P_Pile tmp;
	tmp = (Pile_Stack*)malloc(sizeof(Pile_Stack));
	tmp = P->next_row->next_col;
	P->next_row->next_col = tmp->next_col;
	free(tmp);
	return 0;
}//懒得优化了

int pop_a_stack(P_Pile P) {
	if (P->next_row == NULL) {
		printf("error(null stack)!\n");
		return -1;
	}
	P_Pile tmp;
	tmp = (Pile_Stack*)malloc(sizeof(Pile_Stack));
	tmp = P->next_row;
	P->next_row = tmp->next_row;
	free(tmp);
	return 0;
}

ElemType front(P_Pile P) {
	if (P->next_row == NULL) {
		printf("error(null stack)!\n");
		return -1;
	}
	if (P->next_row->next_col == NULL) {
		printf("error(null elem)!\n");
		return -2;
	}
	return P->next_row->next_col->data;
}

P_Pile front_a_stack(P_Pile P) {
	if (P->next_row == NULL) {
		printf("error(null stack)!\n");
		return NULL;
	}
	return P->next_row;
}

int main(void) {
	P_Pile pile;
	pile = (Pile_Stack*)malloc(sizeof(Pile_Stack));
	initialize_pile(pile);
}
