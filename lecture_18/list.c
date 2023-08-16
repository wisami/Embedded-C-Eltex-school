#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

#define BUF_SIZE 255

static char *s_gets(char *st, int n);

void InitList(List *plist) {
	*plist = NULL;
}

bool AddItem(List *plist) {
	Node *pnew;
	Node *current = *plist;

	pnew = (Node *) malloc(sizeof(Node));
	if (pnew == NULL)
		return false;
	
	pnew->next = NULL;

	printf("Введите имя: ");
	s_gets(pnew->item.name, NAME_SIZE);
	printf("Введите номер телефона: ");
	s_gets(pnew->item.phone, PHONE_SIZE);
	printf("Введите e-mail: ");
	s_gets(pnew->item.email, EMAIL_SIZE);


	if (current == NULL) {
		*plist = pnew;
	}
	else {
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = pnew;
	}
}

void ShowList(List *plist) {
       Node *current = *plist;

	while (current != NULL) {
		printf("%s, %s, %s\n", current->item.name, current->item.phone, current->item.email);
		current = current->next;
	}
}

void SearchItem(List *plist) {
	Node *current = *plist;
	char buf[BUF_SIZE];
	
	printf("Введите имя для поиска: ");
	s_gets(buf, BUF_SIZE);

	while (current != NULL) {
		if (!strcmp(buf, current->item.name)) {
			printf("%s, %s, %s\n", current->item.name, current->item.phone, current->item.email);
		}
		current = current->next;
	}
}

void DeleteItem(List *plist) {
	Node *current = *plist;
	Node *prev = NULL;
	char buf[BUF_SIZE];

	printf("Введите имя для удаления: ");
	s_gets(buf, BUF_SIZE);

	while (current != NULL && strcmp(buf, current->item.name)) {
		prev = current;
		current = current->next;
	}

	if(prev == NULL) {
		*plist = current->next;
		free(current);
	}
	else {
		prev->next = current->next;
		free(current);
	}

}

void ClearList(List *plist) {

	Node *current = *plist;

	while (current != NULL) {
		*plist = current->next;
		free(current);
		current = *plist;
	}
}

static char *s_gets(char *st, int n) {
	char *ret_val;
	char *find;

	ret_val = fgets(st, n, stdin);
	if (ret_val) {
		find = strchr(st, '\n');
		if (find) {
			*find = '\0';
		}
		else {
			while (getchar() != '\n')
				continue;
		}
	}

	st = ret_val;

	return ret_val;
}
