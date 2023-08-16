#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(void) {

	List direct;

	InitList(&direct);
	
	int command = 0;
	while (command != 5) {

		printf("1. Добавить абонента.\t\t4. Удалить абонента.\n");
		printf("2. Вывести список абонетов.\t5. Выйти из справочника.\n3. Поиск абонента по имени.\n");
		printf("Введите номер команды: ");

		scanf("%d", &command);
		while (getchar() != '\n') {
			continue;
		}

		switch (command) {
			case 1:
				AddItem(&direct);
				break;
			case 2:
				ShowList(&direct);
				break;
			case 3:
				SearchItem(&direct);
				break;
			case 4:
				DeleteItem(&direct);
				break;
			case 5:
				ClearList(&direct);
				break;
			default:
				puts("Команда не распознана! Попробуйте ещё раз.");
		}
	}


	return 0;
}
