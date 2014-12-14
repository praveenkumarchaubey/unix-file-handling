#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int openclose()
{
	int fd1;
	int fd2;
	size_t buffsize1 = 0;
	size_t buffsize2 = 0;
	char buffer1[40];
	char buffer2[40];

	printf("Enter function openclose\n");

	strcpy(buffer1, "writing into abcfile\n");
	strcpy(buffer2, "writing into deffile\n");
	buffsize1 = strlen(buffer1);
	buffsize2 = strlen(buffer2);

	fd1 = open ("abcfile", O_RDWR);
       if(fd1 == -1)
	{
	   perror("fd1:open");
	   exit(-1);
        }
	fd2 = open ("deffile", O_CREAT|O_RDWR|O_TRUNC|O_EXCL, S_IRWXU|S_IRWXG|S_IRWXO);
       if(fd2 == -1)
	{
	   printf("File already exists\n");
	   exit(-1);
        }

	printf("%s", buffer1);
	buffsize1 = write(1, buffer1, buffsize1);

	buffsize1 = write(fd1, buffer1, buffsize1);
	buffsize1 = write(fd2, buffer2, buffsize2);

	printf("fd1: %d fd2: %d\n", fd1, fd2);
	close(fd1);
	close(fd2);
	printf("Exit function openclose\n");
	return 1;
}

int append()
{
	int fd1;
	int fd2;
	int fd3;
	int fd4;
	int retval = 0;
	printf("Enter function append\n");
	fd1 = open ("abcfile", O_RDWR|O_APPEND|O_CREAT,S_IRWXU);
	fd2 = open ("deffile", O_APPEND|O_RDWR);
	printf("original fd1: %d fd2: %d\n", fd1, fd2);
	/*close(1);*/
        fd3 = dup(fd1);
	printf("appending into the file \n");
	printf("dup fd1: %d\n", fd3);
	retval = close(fd1);
	printf("error closing : %d : %d\n", errno, retval);
        fd4 = dup(fd2);
	printf("dup fd2: %d\n", fd4);
	close(fd2);
	close(fd4);
	printf("Exit function append\n");
	return 1;
}

int duptest()
{
	int fd1;
	int fd2;
	int fd3;
	int fd4=0;
	int retval = 0;
	printf("Enter function duptest\n");
	fd1 = open ("abcfile", O_CREAT|O_RDWR, S_IRWXU);
	fd2 = open ("deffile", O_CREAT|O_RDWR, S_IRWXU);
	printf("original fd1: %d fd2: %d\n", fd1, fd2);
	close(1);
	fd3 = dup(fd1);
	printf("dup fd1: %d\n", fd3);
	retval = close(fd1);
	printf("writing onto standard output\n");
	printf("error closing : %d : %d\n", errno, retval);
        fd4 = dup(fd2);
        printf("dup fd2: %d\n", fd4);
	close(fd2);
	close(fd4);
	printf("Exit function duptest\n");
	return 1;
}

int lseektest()
{
	int fd1;
	char buff[5];
        int nobytes;
        fd1=open("input.txt",O_RDWR);
	lseek(fd1,5,SEEK_SET);
        while(1)
          {
	     nobytes = read(fd1,buff,5);
	     write(STDOUT_FILENO,buff,nobytes);
	     lseek(fd1,0,SEEK_SET);
          }
	return 1;
}



int main ()
{
	int lchoice = 0;
	printf("what do you want to test?\n");
	printf("for file create : enter 1\n");
	printf("for file open with append : enter 2\n");
	printf("for testing dup : enter 3\n");
	printf("\nfor testing lseek:enter 4\n");
        scanf("%d", &lchoice);
	switch (lchoice)
	{
		case 1: 
			openclose();
			break;
		case 2: 
			append();
			break;
		case 3: 
			duptest();
			break;
                case 4:
                        lseektest();
                        break;
	}
	printf("hello hall no\n");
	return 1;
}
