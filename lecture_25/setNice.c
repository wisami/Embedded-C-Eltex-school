#include <stdio.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "usage: %s priority\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pr = atoi(argv[1]); 
    pid_t childPid;

    childPid = fork();

    if (childPid == -1) {
        fprintf(stderr, "Ошибка создания процесса\n");
        exit(EXIT_FAILURE);
    }

    if (childPid == 0) {
        
        pid_t pid = getpid();

        int result = setpriority(PRIO_PROCESS, pid, pr);
        int priority = getpriority(PRIO_PROCESS, pid);

        if (result == -1) {
            fprintf(stderr, "Ошибка изменения приоритета процесса\n");
            exit(EXIT_FAILURE);
        }

        printf("Дочерний процесс. PID: %d Приоритет: %d\n", pid, priority);

        for (int i = 0; i < 100000000; i++)
            getpid();

    }
    else {

        wait(NULL);
        
        pid_t pid = getpid();
        int priority = getpriority(PRIO_PROCESS, pid);

        printf("Родительский процесс. PID: %d Приоритет: %d\n", pid, priority);
    }

    return 0;
}
