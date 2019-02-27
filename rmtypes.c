#include <stdio.h>
#include <string.h>


int main(int argc, char ** argv)
{
	if (argc < 2)
	{
		fprintf(stderr,"%d: ",__LINE__);
		perror("%s",*argv);

	}	
	
	FILE * ifs = NULL;

	while (*++argv != NULL)
	{

	}

	return 0;
}
