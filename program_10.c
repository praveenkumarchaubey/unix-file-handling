/**************************************************************************
*       DESCRIPTION:Contains Code for a program that demonstrates the
*       use of  lseek/open/read/write etc.Reads the characters and append 
*	them in the same file.
*       Invoke the Executable as a.out
*       Copyright 2014 Aricent
****************************************************************************/
#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

int main(int argc, char *argv[])
{
	int fd,cbytes;
	off_t currpos;
	int initialfilesize, finalfilesize, retread, retwrite;
	char buf;
	if ( NULL == argv[1])
	{
		printf("Pl. provide the name of the file\n");
		exit(1);
	}
	
	fd = open(argv[1],O_RDWR|O_APPEND);
	if (fd < 0)
	{
		printf("File opening failed \n");
		perror("File Opening Error:");
		exit(0);
	}
	/*Print the current file offset in RDWR mode*/
	currpos = lseek(fd, 0, SEEK_CUR);
	printf("The value of the current file offset =%d\n", currpos);

	/*Printing the Current File offset after going at the end*/

	currpos = lseek(fd,0,SEEK_END);
	if ( (off_t)-1 == currpos)
	{
		printf("Cannot Lseek\n");
		perror("Lseek Error:");
		exit(1);
	}

	printf("The size of the file = %d\n",currpos);
	
	initialfilesize = currpos;

	/*Bringing the offset in the beginning to start reading*/
	lseek(fd,0, SEEK_SET);
	while (currpos)
	{

		retread = read (fd, &buf, sizeof(char));
		/*Before write file offset is set at the end, since append mode*/
		retwrite = write(fd, &buf, retread);
	
		/*Bringing file offset to read the next byte from beginning*/
		
		lseek(fd, (0 - initialfilesize), SEEK_END);
	
		/*Tracking How many bytes to read, which is the initialfilesize*/
		currpos--; 
	}
	finalfilesize = lseek(fd, 0, SEEK_END);
	printf("The size of the file now  = %d\n",finalfilesize);
	return 0;	 
}
