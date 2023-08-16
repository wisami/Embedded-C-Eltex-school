#include <stdio.h>
#include <pthread.h>

int count = 0;

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c1 = PTHREAD_COND_INITIALIZER;

void *thread_cond(void *args) {
	pthread_mutex_lock(&m1);
	pthread_cond_wait(&c1, &m1);
	count += 2000000;
	pthread_mutex_unlock(&m1);

	return NULL;
}

void *thread_calc(void *args) {
	
	for (int i = 0; i < 10000000; i++) {
		pthread_mutex_lock(&m1);
		if (count >= 50000000) {
			pthread_cond_signal(&c1);
		}
		count++;
		pthread_mutex_unlock(&m1);
	}

	return NULL;
}

int main(void) {

	int i;
	pthread_t thread[19];

	for (i = 0; i < 18; i++) {
		pthread_create(&thread[i], NULL, thread_calc, NULL);
	}

	pthread_create(&thread[i], NULL, thread_cond, NULL);

	for (i = 0; i < 19; i++) {
		pthread_join(thread[i], NULL);
	}

	printf("%d\n", count);

	return 0;
}