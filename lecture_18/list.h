#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>

#define NAME_SIZE 255
#define PHONE_SIZE 255
#define EMAIL_SIZE 255

struct subscriber {
	char name[NAME_SIZE];
	char phone[PHONE_SIZE];
	char email[EMAIL_SIZE];
};

typedef struct subscriber Item;

typedef struct node {
	Item item;
	struct node *next;
}Node;

typedef Node *List;

void InitList(List *plist);
bool AddItem(List *plist);
void ShowList(List *plist);
void SearchItem(List *plist);
void DeleteItem(List *plist);
void ClearList(List *plist);

#endif
