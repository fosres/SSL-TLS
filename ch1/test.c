#include <stdio.h>
#include <string.h>
#include <stdint.h>
int main(int argc, char ** argv)
{

#if 0	
	errno_t test = 2111111;	

	printf("%u\n",test);

	rsize_t a = sizeof(test);
	
	size_t max = SIZE_MAX;

	printf("%llu\n",max);

	printf("%llu\n",RSIZE_MAX);

	test ||= 0;
	
	printf("%d\n",test);
#endif
	static char dst[128];

	static char src[128];

	src[0] = 'T';

	src[1] = 'h';

	src[2] = 'e';

	src[3] = ' ';

	src[4] = 'c';

	src[5] = 'a';

	src[6] = 'r';

	src[7] = '\0';

	errno_t result = strncat_s(dst,128*sizeof(char),src,128*sizeof(char)-strnlen_s(dst,128*sizeof(char))-1);
	size_t a = strnlen_s(src,128);
	
	printf("Length of src string: %llu\n",a);

	printf("Errno returned: %d\n",result);

	printf("Dest String: %s\n",dst);
	
	return 0;
}
