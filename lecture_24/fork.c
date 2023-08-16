/*
*	Написать программу которая пораждает два новых процесса, а затем 
*	один из новых процессов порождает ещё два новых процесса, а другой 
*	только один новый процесс. (см. граф ниже)
*	    0
*	   / \
*	  0   0
*	 / \   \
*	0   0   0
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {

	pid_t cpid1, cpid2, cpid3, cpid4, cpid5;

	cpid1 = fork();
	if (0 == cpid1) {

		cpid2 = fork();
		if (0 == cpid2) {
			printf("Child pid 2 = %d, Parent pid = %d\n", getpid(), getppid());
		}
		else {
			printf("Child pid 1 = %d, Parent pid = %d\n", getpid(), getppid());
			wait(NULL); // Ожидание завершения cpid2
		}

	}
	else {
		printf("Parent pid = %d\n", getpid());
		wait(NULL);	// Ожидание завершения cpid1

		cpid3 = fork();
		if (0 == cpid3) {
			printf("Child pid 3 = %d, Parent pid = %d\n", getpid(), getppid());

			cpid4 = fork();
			if (0 == cpid4) {
				printf("Child pid 4 = %d, Parent pid = %d\n", getpid(), getppid());
			}
			else {
				wait(NULL);	// Ожидание завершения cpid4

				cpid5 = fork();
				if (0 == cpid5) {
					printf("Child pid 5 = %d, Parent pid = %d\n", getpid(), getppid());
				}
				else{
					wait(NULL);	// Ожидание завершения cpid5
				}
			}
		}
		else {
			wait(NULL);	// Ожидание завершения cpid3
		}

	}

	return 0;
}