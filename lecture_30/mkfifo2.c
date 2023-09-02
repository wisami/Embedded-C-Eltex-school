#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    
    int fd1, fd2;
    char mes[] = "Hi!";
    char buf[100];

    fd1 = open("/tmp/pipeTmp1", O_RDONLY);
    fd2 = open("/tmp/pipeTmp2", O_WRONLY);

    if (fd1 == -1 || fd2 == -1) {
        fprintf(stderr, "Ошибка открытия канала\n");
        exit(EXIT_FAILURE);
    }
    

    write(fd2, mes, strlen(mes) + 1);
    printf("Пишет: %s\n", mes);
    close(fd2);

    read(fd1, buf, sizeof(buf));
    printf("Читает %s\n", buf);
    close(fd1);

    return 0;
}
