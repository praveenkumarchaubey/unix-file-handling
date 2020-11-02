/***************************************************************************
 *	Contains Code for a program that demonstrates the sharing of the file offset between parent and child. 
 *	Ensure a file named datafile is available in the current directory which is having some 15/20 caharacters.
 *	Invoke the Executable as a.out
 ****************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include<fcntl.h>

int main()
{
    char databuf[512];
    int retfork,fd,bytesread;

    /*Open a file in Read Only Mode*/
    fd=open("datafile",O_RDONLY);
    if (fd < 0)
    {
        printf("Error in Opening file \n");
        exit(1);
    }

    /*Request to read some bytes from the file in parent*/
    bytesread=read(fd,databuf,5);
    if (bytesread < 0)
    {
        printf("Error in Reading data\n");
        exit(1);
    }
    databuf[bytesread]='\0'; /*NULL Terminating to print as a string*/

    /*Creating a Child process which will read from the same open file*/
    retfork=fork();
    if (retfork < 0)
    {
        printf("Error in executing fork call\n");
        exit(1);
    }

    if (0 == retfork)/*Child Executing*/
    {
        /*uncomment the code below and see the changes*/
        //fd=open("datafile",O_RDONLY);

        /*Read some bytes from the open file*/
        /*Note - The same file offset is being used by the child*/
        bytesread=read(fd,databuf,5);
        databuf[bytesread]='\0';
        printf("Child has read:%s",databuf);
        exit(0);
    }

    printf("\n\n");
    printf("Parent has read :%s\n",databuf);
    return 0;
}

