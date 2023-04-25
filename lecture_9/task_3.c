/*
	3. Заполнить верхний треугольник матрицы 1, 
	а нижний 0.
	
	Пример:
	001
	011
	111
*/

#include <stdio.h>

#define N 5

int main(void) {

	int arr[N][N];

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if ((i + j) >= (N - 1)) {
				arr[i][j] = 1;
			}
			else {
				arr[i][j] = 0;
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}

	return 0;
}