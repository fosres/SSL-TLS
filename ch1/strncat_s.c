#include <stdio.h>
#include <string.h>
#include <stdint.h>

errno_t strncat_s(char * restrict s1, rsize_t s1max, const char * restrict s2, rsize_t n)
{
	
	errno_t violation_present = 0;

	rsize_t m = 0;

	int S2_STRING_IS_NULL = 0;

	int N_NOT_IN_RANGE = 0;

	int M_IS_ZERO = 0;

	int M_SHORTER_THAN_STR2NLEN = 0;

#if 0

(s1 + m) points to the memory register

that stores the null char for s1.

#endif

	if ( ( m = ( s1max - strnlen_s( s1, s1max ) ) ) == 0 )
	{
	       M_IS_ZERO = 1;

	       fprintf(stderr,"strncat_s: Error: M_IS_ZERO\n");

	}

	if ( s1max == 0 )
	{

		fprintf(stderr,"strncat_s: Error: %d: s1max is 0\n",__LINE__);

		return 1;
	}

	if ( s1 == NULL  )
	{ 
		fprintf(stderr,"strncat_s: Error: %d: Source string "
				
				"s1 is NULL!\n",
				
			__LINE__);

		return 1;

	}

	if ( s2 == NULL )
	{
		S2_STRING_IS_NULL = 1;

		fprintf(stderr,"strncat_s: Error: S2_STRING_IS_NULL\n");
	}
	
	if ( s1max > RSIZE_MAX )
	{
	 
		fprintf(stderr,"strncat_s: Error: %d: s1max is"

				"larger than RSIZE_MAX",

				__LINE__);

		return 1;
	}

	if ( n > RSIZE_MAX )
	{ 
		N_NOT_IN_RANGE = 1; 
		
		fprintf(stderr,"strncat_s: Error: N_NOT_IN_RANGE\n");	
	}

#if 0
Bug found: Testcase r3 from C11 N1570 Draft for strncat_s fails

	For securitys sake: n == s1max - strnlen_s(s1,s1max) - 1
#endif

	if ( ( m <= n ) && ( m <= strnlen_s(s2,n) ) )
	{ 
		M_SHORTER_THAN_STR2NLEN = 1; 
		
		fprintf(stderr,"strncat_s: Error: M_SHORTER_THAN_STR2NLEN\n");	
	}


#if 0

The conditional statement below determines

if at least one of the booleans is true,

which counts as a runtime-constraint violation.

#endif
	if ( 
		S2_STRING_IS_NULL ||  N_NOT_IN_RANGE 
			
		|| M_IS_ZERO || M_SHORTER_THAN_STR2NLEN
	   
	   )
	
	{ 
		violation_present = 1; 
	}

#if 0
Bug found: Testcase r3 from C11 N1570 Draft for strncat_s fails
#endif
	if ( 	
		( violation_present == 1 ) 
		
		&& (s1 != NULL ) 

		&& (s1max > 0) 
		
		&& (s1max <= RSIZE_MAX)
	   )
	
	{
		s1[0] = '\0';

		return violation_present;

	}

	else if ( (violation_present == 1) )
	{
		return violation_present;
	}

	else // No runtime-constraint violations found
	{


		strncat(s1,s2,s1max - strnlen_s(s1,s1max) - 1);

		return violation_present;
	}	
		

}




