/*Write a program to open 2 files (the names of the files should be taken as command line arguments) one in read only mode and the other in write only mode  and then read the contents of the first file and write them into the second file, word by word. However the words should be written in the reverse order, the first word of the first file should be the last word of second file and the last word of the first file should be the first word of the second file.*/

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
	memset(buf,0,SIZE*sizeof(char));
	char *token[SIZE];
	int return1 = 0;
	int return2 = 0;
	int return3 = 0;
	int return4 = 0;
	int len = 0;
	int i = 0;

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

 	return1 = read(fd1,buf,sizeof(buf));
	if(-1 == return1)
	{
		printf("Error in reading the file %s", argv[1]);
		exit(1);
	}

	token[i] = strtok(buf, " ,.	\n;");
	while(token[i] != NULL)
	{
		i++;
		token[i] = strtok(NULL, " ,.	\n;");
	}
	--i;
	while(0 <= i)
	{
		len = strlen(token[i]);
		return2 = write(fd2, token[i],len*sizeof(char));
		if(-1 == return2)
		{
			printf("Error in writing to the file %s", argv[2]);
			exit(1);
		}
		write(fd2, " ", 1);
		i--;
	}

	return3 = close(fd1);
	if(return3 != -1)
	{
		printf("File %s successfully closed\n", argv[1]);
	}
	else
	{
		printf("Error in closing the file  %s \n", argv[1]);
		perror("File closing error");
	}

	return4 = close(fd2);
	if(return4 != -1)
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


