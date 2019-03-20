#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define MSGSIZE sizeof(int)

/**
 * 0 standard input
 * 1 standard output
 */

int main() {
    int fd1[2];

    int input_number;
    int output_number;
    pid_t p;

    if (pipe(fd1) == -1) {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }

    p = fork();

    if (p < 0) {
        fprintf(stderr, "Fork Failed");
        return 1;
    } else if (p > 0) {
        scanf("%d", &input_number);
        write(fd1[1], &input_number, MSGSIZE);
        wait(NULL);
        read(fd1[0], &output_number, MSGSIZE);
        printf("Result is %d\n", output_number);
    } else {
        int number;
        read(fd1[0], &number, MSGSIZE);
        number = number * number;
        write(fd1[1], &number, MSGSIZE);
        exit(0);
    }
} 
