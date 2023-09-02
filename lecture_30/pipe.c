#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void) {

    int fdParentWrite[2];
    int fdChildWrite[2];
    pid_t pid;

    if (-1 == pipe(fdParentWrite)) {
        fprintf(stderr, "error pipe");
        exit(EXIT_FAILURE);
    }

    if (-1 == pipe(fdChildWrite)) {
        fprintf(stderr, "error pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (-1 == pid) {
        fprintf(stderr, "error fork");
        exit(EXIT_FAILURE);
    }

    if (0 != pid) {

        char mes[] = "Hello!";
        char buf[100];

        close(fdParentWrite[0]);
        close(fdChildWrite[1]);

        printf("Родитель отправляет: %s\n", mes);
        write(fdParentWrite[1], mes, strlen(mes) + 1);

        read(fdChildWrite[0], buf, sizeof(buf));
        printf("Родитель получает: %s\n", buf);

        close(fdParentWrite[1]);
        close(fdChildWrite[0]);
    }
    else {

        char mes[] = "Hi!";
        char buf[100];

        close(fdParentWrite[1]);
        close(fdChildWrite[0]);

        read(fdParentWrite[0], buf, sizeof(buf));
        printf("Дочерний получает: %s\n", buf);

        printf("Дочерний отправляет: %s\n", mes);
        write(fdChildWrite[1], mes, strlen(mes) + 1);


        close(fdParentWrite[0]);
        close(fdChildWrite[1]);
    }

    return 0;
}
