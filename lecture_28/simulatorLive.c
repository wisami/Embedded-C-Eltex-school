#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#define NUM_SHOPS 5
#define NUM_CUSTOMERS 3
#define SLEEP_CUSTOMER 1 /*second*/
#define NUM_WORKERS 1
#define SLEEP_WORKER 2   /*second*/
#define ADD_PRODUCTS 500
#define MAX_PRODUCTS 1000
#define NEED_PRODUCTS 10000

int shop[NUM_SHOPS];
static pthread_mutex_t shop_mtx[NUM_SHOPS];

void *worker(void *arg) {

    int num = *((int *) arg);
    int i;

    while (1) {

        i = rand() % NUM_SHOPS;

        if (pthread_mutex_trylock(&shop_mtx[i]) != EBUSY) {
            shop[i] += ADD_PRODUCTS;
            pthread_mutex_unlock(&shop_mtx[i]);
            printf("Рабочий    %d: Магазин %d свободен. Отгрузил товара %d. Всего товаров %d. \
Уснул на %d секунды.\n", num, i + 1, ADD_PRODUCTS, shop[i], SLEEP_WORKER);
            sleep(SLEEP_WORKER);
        }
        else
            printf("Рабочий    %d: Магазин %d занят. Иду в следующий.\n", num, i + 1);
        
    }
}

void *customer(void *arg) {

    int num = *((int *) arg);
    int need = NEED_PRODUCTS;
    int i;

    while (1) {

        i = rand() % NUM_SHOPS;

        if (pthread_mutex_trylock(&shop_mtx[i]) != EBUSY) {

            need -= shop[i];
            if (need <= 0) {
                shop[i] = 0;
                shop[i] += abs(need);
                printf("Покупатель %d: Магазин %d свободен. Купил достаточно. В магазине осталось %d.\n", num, i + 1, shop[i]);
                pthread_mutex_unlock(&shop_mtx[i]);
                break;
            }
            shop[i] = 0;

            printf("Покупатель %d: Магазин %d свободен. Купил весь товар. Ещё надо %d. \
Уснул на %d секунды.\n", num, i + 1, need, SLEEP_CUSTOMER);
            pthread_mutex_unlock(&shop_mtx[i]);
            sleep(SLEEP_CUSTOMER);
        }
        else
             printf("Покупатель %d: Магазин %d занят. Иду в следующий.\n", num, i + 1);

    }
}

int main(void) {
   
    pthread_t pthWorker[NUM_WORKERS];
    pthread_t pthCustomer[NUM_CUSTOMERS];
    int num_worker[NUM_WORKERS];
    int num_customer[NUM_CUSTOMERS];
    int s;

    srand(time(NULL));

    for (int i = 0; i < NUM_SHOPS; i++)
        shop[i] = MAX_PRODUCTS;

    for (int i = 0; i < NUM_SHOPS; i++) {
        s = pthread_mutex_init(&shop_mtx[i], NULL);
        if (s != 0) {
            fprintf(stderr, "error %d pthread_mutex_init", s);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_WORKERS; i++) {
        num_worker[i] = i + 1;
        s = pthread_create(&pthWorker[i], NULL, worker, &num_worker[i]);
        if (s != 0) {
            fprintf(stderr, "error %d pthread_create", s);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        num_customer[i] = i + 1;
        s = pthread_create(&pthCustomer[i], NULL, customer, &num_customer[i]);
        if (s != 0) {
            fprintf(stderr, "error %d pthread_create", s);
            exit(EXIT_FAILURE);

        }
    }

    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        s = pthread_join(pthCustomer[i], NULL);
        if (s != 0) {
            fprintf(stderr, "error %d pthread_join", s);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_WORKERS; i++) {
        s = pthread_cancel(pthWorker[i]);
        if (s != 0) {
            fprintf(stderr, "error %d pthread_cancel", s);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_SHOPS; i++) {
        s = pthread_mutex_destroy(&shop_mtx[i]);
        if (s != 0) {
            fprintf(stderr, "error %d pthread_mutex_destroy", s);
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
