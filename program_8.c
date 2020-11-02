/*Open a file in the RDWR mode and then using lseek() system call read the contents starting from the 10th byte in the file*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>

#define SIZE 100
#define SUCCESS 1

int main(int argc, char *argv[])
{
    int fd1;
    int fd2;
    char buf[SIZE];
    memset(buf,0,SIZE);

    if(3 != argc)
    {
        printf("Insufficient number of arguments\n");
        printf("<1>Input file name\n");
        printf("<2>Output file name\n");
        exit(1);
    }

    fd1 = open(argv[1], O_RDWR);
    if(0 > fd1)
    {
        printf("Error in opening the file %s in read only mode\n", argv[1]);
        perror("opening file error");
        exit(1);
    }

    fd2 = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    if(0 > fd2)
    {
        printf("Error in opening the file %s in write only mode\n", argv[2]);
        perror("file writing error");
        exit(1);
    }

    lseek(fd1,10,SEEK_SET);

    while(0 != read(fd1,buf,sizeof(char)))
    {
        write(fd2,buf,sizeof(char));
    }
    close(fd1);
    close(fd2);
    return SUCCESS;
}//end of main

