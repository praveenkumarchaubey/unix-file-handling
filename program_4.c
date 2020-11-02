/*Write a program to open a file in RDWR mode and read the characters from the file and append them in the same file.*/

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
    int fd;
    int return1 = 0;
    int return2 = 0;
    int len = 0;
    char buf[SIZE];
    memset(buf,0,SIZE*sizeof(char));
    if(2 != argc)
    {
        printf("Insufficient number of arguments\n");
        printf("Input file name\n");
        exit(1);
    }

    fd = open(argv[1], O_RDWR);
    if(0 > fd)
    {
        printf("Error in opening the file %s in append mode\n", argv[1]);
        perror("opening file error");
        exit(1);
    }

    return1 = read(fd,buf,sizeof(buf));
    if(-1 == return1)
    {
        printf("error in reading the file\n");
    }

    len = strlen(buf);
    write(fd,buf,len*sizeof(char));

    return2 = close(fd);
    if(return2 != -1)
    {
        printf("File %s successfully closed\n", argv[1]);
    }
    else
    {
        printf("Error in closing the file  %s \n", argv[1]);
        perror("File closing error");
    }

    return SUCCESS;
}//end of main

