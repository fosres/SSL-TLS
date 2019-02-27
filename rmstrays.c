#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char ** argv)
{
	if (argc < 2)
	{
		fprintf(stderr,"%d: ",__LINE__);

		perror(*argv);

		exit(EXIT_FAILURE);

	}	
	
	FILE * ifs = NULL;

	char ch = 0;

	while (*++argv != NULL)
	{
		if ( (ifs = fopen(*argv,"r+")) == NULL )
		{
			fprintf(stderr,"%d: ",__LINE__);
			perror(*argv);
			exit(EXIT_FAILURE);
		}
		

		while ( (ch = getc(ifs)) != EOF)
		{
			if ( ch > '\u177')
			{
				fseek(ifs,-1,SEEK_CUR);

				fputc(' ',ifs);

				fseek(ifs,0,SEEK_CUR);

				
			
			}

		}

		if ( fclose(ifs) != 0)
		{
			fprintf(stderr,"%d: ",__LINE__);
			perror("fclose");
			exit(EXIT_FAILURE);

		}	

	}

	return 0;
}
