#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    
    int fd1, fd2;
    char mes[] = "Hello!";
    char buf[100];

    mkfifo("/tmp/pipeTmp1", 0666);
    mkfifo("/tmp/pipeTmp2", 0666);

    fd1 = open("/tmp/pipeTmp1", O_WRONLY);
    fd2 = open("/tmp/pipeTmp2", O_RDONLY);

    if (fd1 == -1 || fd2 == -1) {
        fprintf(stderr, "Ошибка открытия канала\n");
        exit(EXIT_FAILURE);
    }
    

    write(fd1, mes, strlen(mes) + 1);
    printf("Пишет: %s\n", mes);
    close(fd1);

    read(fd2, buf, sizeof(buf));
    printf("Читает: %s\n", buf);
    close(fd2);

    return 0;
}
