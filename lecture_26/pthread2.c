#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long count = 0;

void *thread_calc(void *args) {
	
	int *n = (int *) malloc(sizeof(long));

	for (long i = 0; i < 1000000000; i++) {
		(*n)++;
	}

	return (void *) n;
}

int main(void) {
	int i;
	int a[5];
	int *s;

	pthread_t thread[18];

	for (i = 0; i < 18; i++) {
		pthread_create(&thread[i], NULL, thread_calc, NULL);
	}

	for (i = 0; i < 18; i++) {
		pthread_join(thread[i], (void **) &s);
		count += *s;
	}

	printf("%ld\n", count);

	return 0;
}