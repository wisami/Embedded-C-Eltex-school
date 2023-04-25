/*
	2. Вывести заданный массив размером N
	в обратном порядке.

	Пример:
	Ввод  -> 12345
	Вывод -> 54321
*/

#include <stdio.h>

#define N 5

int main(void) {

	int arr[N];
	int temp = 0;

	for (int i = 0; i < N; i++) {
		arr[i] = i + 1;
	}

	for (int i = 0, j = N - 1; i < j; i++, j--) {
		temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}

	for (int i = 0; i < N; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}