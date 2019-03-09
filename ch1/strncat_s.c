#include <stdio.h>
#include <string.h>
#include <stdint.h>

errno_t strncat_s(char * restrict s1, rsize_t s1max, const char * restrict s2, rsize_t n)
{
	
	errno_t violation_present = 0;

	rsize_t m = 0;

	int A_STRING_IS_NULL = 0;

	int S1MAX_NOT_IN_RANGE = 0;

	int N_NOT_IN_RANGE = 0;

	int M_IS_ZERO = 0;

	int S1MAX_IS_ZERO = 0;

	int M_LONGER_THAN_STR2LEN = 0;

#if 0

(s1 + m) points to the memory register

that stores the null char for s1.

#endif

	if ( ( m = ( s1max - strnlen( s1, s1max ) ) ) == 0 )
	{
	       M_IS_ZERO = 1;

	}

	if ( s1 == NULL || s2 == NULL )
	{ 
		A_STRING_IS_NULL = 1;		

	}

	if ( s1max > RSIZE_MAX )
	{ 
		S1MAX_NOT_IN_RANGE = 1; 
	
	}

	if ( n > RSIZE_MAX )
	{ N_NOT_IN_RANGE = 1; }

	if ( m > strnlen_s(s2,n) )
	{ M_LONGER_THAN_STR2LEN = 1; }


#if 0

The conditional statement below determines

if at least one of the booleans is true,

which counts as a runtime-constraint violation.

#endif
	if ( 
		A_STRING_IS_NULL || S1MAX_NOT_IN_RANGE || N_NOT_IN_RANGE 
			
		|| M_IS_ZERO || S1MAX_IS_ZERO || N_NOT_IN_RANGE	

		|| M_LONGER_THAN_STR2LEN
	   
	   )
	{ violation_present = 1; }

	if ( 	
		violation_present 
#if 0	
		&& (s1 != NULL ) 

		&& (s1max > 0) 
		
		&& (s1max <= RSIZE_MAX)
#endif	   
	   )
	
	{
		s1[0] = '\0';

		return violation_present;

	}

	else // No runtime-constraint violations found
	{


		strncat(s1,s2,s1max - strnlen_s(s1,s1max) - 1);

		return violation_present;
	}	
		






}



