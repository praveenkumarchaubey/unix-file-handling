/*Write a program to open 2 files (the names of the files should be taken as command line arguments) one in read only mode and the other in write only mode  and then read all the characters from the first file and write them into the second file. Also check whether the opened file exists and if not then catch the exception by writing the code for the error also.*/

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
    int return1 = 0;
    int return2 = 0;
    char buf[SIZE];
    if(3 != argc)
    {
        printf("Insufficient number of arguments\n");
        printf("<1>Input file name\n");
        printf("<2>Output file name\n");
        exit(1);
    }

    fd1 = open(argv[1], O_RDONLY);
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

    while(0 != read(fd1,buf,sizeof(char)))
    {
        write(fd2,buf,sizeof(char));
    }

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

