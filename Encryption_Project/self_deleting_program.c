#include <stdio.h>

int main(void)
{
	FILE * in = NULL;

#if 0
	if ( 
		(
			in = fopen("self_deleting_program.o","r+") 
		) 
			
			== 
			
			NULL 
	   )
	{
		fprintf(stderr,"Error: Failed to open file!\n");

		return 1;	
	}

	else
	{
		if (

			fclose(in)

			==

			EOF	
		   )
		{
			fprintf(stderr,"Error: Failed to close file!\n");

			return 1;
		}

	}
#endif
	remove("self_deleting_program.o");

	return 0;
}
