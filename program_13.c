/*This code will print the contents of a Sym Link*/

#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>

int main(int argc, char *argv[])
{
	char array[513];
	int ret;
	/*get the link name from the command line.*/
	if (NULL == argv[1])
	{
		printf("Pl. enter the file name\n");
		exit(1);
	}
	/*Check for the existence of the file...*/
	ret = open(argv[1], O_RDONLY);
	if ( -1 == ret)
	{
		printf("Cannot open %s\n", argv[1]);
		perror("Error File Access\n");
		/*If the Symlink is broken then also, better to exit....*/
		exit(1);
	}

	close(ret); //I do not need the descriptor.
	/*Now call the Readlink Function*/ 
	ret = readlink(argv[1], array, 512);
	if (-1 == ret)
	{
		if(EINVAL == errno)
		{
			printf("%s is not a Sym Link", argv[1]);
			exit(1);
		}
		else
		{
			perror("File Error");
			exit(1);
		}
	}
	
	array[ret]='\0';
	printf("Content of the Link is %s\n", array);	
	return 0;	
}


