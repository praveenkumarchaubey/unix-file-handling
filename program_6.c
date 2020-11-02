/*Write a program to create 2 files using open system call and then write the string .open system call. in one file and .write system call. in the second file.*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>

#define SUCCESS 1

int main(int argc, char *argv[])
{
    int fd1;
    int fd2;
    int return1 = 0;
    int return2 = 0;
    if(3 != argc)
    {
        printf("Insufficient number of arguments\n");
        printf("<1>Input file name\n");
        printf("<2>Output file name\n");
        exit(1);
    }

    fd1 = open(argv[1], O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    if(0 > fd1)
    {
        printf("Error in opening the file %s in write only mode\n", argv[1]);
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

    write(fd1,"open system call",16*sizeof(char));
    write(fd2,"write system call",17*sizeof(char));

    return1 = close(fd1);
    if(return1 != -1)
    {
        printf("File %s successfully closed\n", argv[1]);
    }
    else
    {
        printf("Error in closing the file  %s \n", argv[1]);
        perror("File closing error");
    }

    return2 = close(fd2);
    if(return2 != -1)
    {
        printf("File %s successfully closed\n", argv[2]);
    }
    else
    {
        printf("Error in closing the file  %s \n", argv[2]);
        perror("File closing error");
    }
    return SUCCESS;
}//end of main

