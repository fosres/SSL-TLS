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

