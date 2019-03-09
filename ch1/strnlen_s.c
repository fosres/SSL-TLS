#include <stdio.h>
#include <string.h>

size_t strnlen_s(const char * s,size_t maxsize)
{
	if ( s == NULL )
	{ return 0; }

	size_t i = 0;

	while ( (i < maxsize) && ( s[i] != '\0' ) )
	{
		i++;
	}

	return i;

}

#if 0
int main(int argc,char ** argv)
{
	if ( argc < 2 )
	{ 
		fprintf(stderr,"Error: %d: Please provide a non-spaced string argument!\n",__LINE__);
	}

	size_t len = strnlen_s(argv[1],1024);	
	
	printf("Length of string argument is: %llu\n",len);

		

	return 0;
}
#endif
