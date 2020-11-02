/**************************************************************************
 * Contains Code for a program that demonstrates the use of  lseek call (Finding the size of a file)
 * Invoke the Executable as a.out
 ****************************************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
    int fd,cbytes;
    off_t currpos;
    struct stat localstat;

    if ( NULL == argv[1])
    {
        printf("Pl. provide the name of the file\n");
        exit(1);
    }

    fd = open(argv[1],O_RDONLY);
    if (fd < 0)
    {
        printf("File opening failed \n");
        perror("File Opening Error:");
        exit(0);
    }

    /*Printing the Current File offset after going at the end*/
    currpos=lseek(fd,0,SEEK_END);
    if ( (off_t)-1 == currpos)
    {
        printf("Cannot Lseek\n");
        perror("Lseek Error:");
        exit(1);
    }

    printf("The size of the file = %d\n",currpos);

    /* Calculating the size of the file directly using stat/fstat*/

    /*setting the offset to the beginning*/
    lseek(fd,0,SEEK_SET);
    fstat(fd,&localstat);	
    printf("The size of the file using fstat is %d\n", localstat.st_size);
    close(fd);
    return (0);
}
