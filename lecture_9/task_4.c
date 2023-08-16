/*
	4. Заполнить матрицу числами от 1 до N^2 улиткой.

	Пример:
	1  2  3  4  5
	16 17 18 19 6
	15 24 25 20 7
	14 23 22 21 8
	13 12 11 10 9
*/


#include <stdio.h>

#define N 5

int main(void) {

	int arr[N][N];

	int count = 1, i = 0, j = 0;
	int lim_left_up = 0, lim_right_down = N - 1;

	while (lim_left_up <= lim_right_down) {

		while (j < lim_right_down) {
			arr[i][j++] = count++;
		}

		while (i < lim_right_down) {
			arr[i++][j] = count++;
		}

		while (j > lim_left_up) {
			arr[i][j--] = count++;
		}
    
		lim_left_up++;
		lim_right_down--;

		while (i > lim_left_up) {
			arr[i--][j] = count++;
		}
	}
	arr[i][j] = count;


	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%.2d ", arr[i][j]);
		}
		printf("\n");
	}

	return 0;
}
