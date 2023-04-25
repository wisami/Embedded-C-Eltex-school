/*
	1. Вывести квадратную
	матрицу по заданному N.

	Пример: N = 3:
	123
	456
	789
*/

#include <stdio.h>

#define N 3

int main(void) {

	int arr[N][N];

	for (int i = 0; i < N * N; i++) {
		**arr + i = i + 1;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}

	return 0;
}