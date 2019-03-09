#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAXSIZE 128
int main(int argc, char ** argv)
{

	static char dst[MAXSIZE];	
	
	if ( argc != 2 )
	{
		
		fprintf(stderr,"%d: Error: Less than three arguments!\n"
				
				"Format: [./test.o] [src_string]"
		       );

		return 1;

	}
	
	errno_t result = strncat_s(dst,MAXSIZE,argv[1],MAXSIZE-strnlen_s(dst,MAXSIZE)-1);
	
	printf("Errno returned: %d\n",result);

	printf("Dest String: %s\n",dst);
	
	return 0;
}
