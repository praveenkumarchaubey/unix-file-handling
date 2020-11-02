/**************************************************************************
 * Contains Code for a program that demonstrates the use of stat call. 
 * It checks whether the command line args in this code are Regular files/directories.
 * Invoke the Executable as a.out <file1> <file2> ......
 ****************************************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(int argc, char *argv[])
{
    struct stat sbuf;//Structure to hold the File's attributes
    int index, ret;

    if (1 == argc)
    {
        printf("Pl. provide at least one filename\n");
        exit(1);
    }
    /*Move through the arg list*/
    for (index =1; index <= (argc-1);index++)
    {
        /*Stat cmd line args*/
        ret=stat(argv[index],&sbuf);
        if (-1 == ret)
        {
            printf("Cannot Stat %s", argv[index]);
            continue;
        }

        if (S_ISREG(sbuf.st_mode))
            printf("%s is a regular file\n",argv[index]);
        else
            printf("%s is not a regular file\n", argv[index]);
    }
    return 0;
}
