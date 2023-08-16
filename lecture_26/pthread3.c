#include <stdio.h>

long count = 0;

int main(void) {


	for (long i = 0; i < 18000000000; i++) {
		count++;
	}

	printf("%ld\n", count);

	return 0;
}