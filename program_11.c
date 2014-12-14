/***************************************************************************
*       FILENAME : fcopy.c
*       DESCRIPTION:Contains Code for a program that demonstrates the
*       use of  open/read/write calls. Copies source to destination 
*       Invoke the Executable as a.out source destination
*       Copyright 2014 Aricent
****************************************************************************/
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<errno.h>
#define BLOCKSIZE 100

int main(int argc, char *argv[])
{
	int fd1,fd2,bytesread, ret = 0, total =-1;
	char buf[BLOCKSIZE];
	
	/*Open the source file in Read Only Mode*/
	if(NULL == argv[1])
	{
		printf("Please specify the source file\n");
		exit(1);
	}
	if(NULL == argv[2])
	{
		printf("Please specify the destination file\n");
		exit(1);
	}
	/*Note the third argumnent was not required*/
	fd1=open(argv[1],O_RDONLY);
	if(fd1<0)
	{
		printf("Cant open File for reading \n");
		perror("Opening File error");
		exit(1);
	}

	/*Open the destination  file in Write Only Mode*/
	/*Also note we are giving the EXCL flag, so that if the destination 
	file exists, the function will return an error*/

	fd2=open(argv[2],O_WRONLY|O_CREAT|O_EXCL,S_IRWXU);
	
	if(fd2<0)
	{
		if (EEXIST == errno)
		{
		perror("open");	
		printf("Destination file exists so not overwrite\n");
			exit(1);
		}
		
		printf("Cant open file for writing\n");
		perror("File Writing Error");
		exit(1);
	}
	
	while((bytesread = read(fd1,buf,BLOCKSIZE))>0)
	{
		
		ret = write(fd2,buf,BLOCKSIZE);
		if (-1 == ret)
		{
			printf("File Write Error\n");
			exit(1);
		}
		total = total + ret;
	}
	
	if ( total  > 0)
	{
		printf("Written Successfully %d bytes\n", ret);
	}
	else
	{
		
		printf("Error/Zero Byte  case\n");
	}
	
	/*Closing the file descriptors explicitly*/
	close(fd1);
	close(fd2);
	return 0;
}
