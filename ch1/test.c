#include <stdio.h>
#include <stdint.h>
#include <string.h>
int main(void)
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

	strncat_s(dst,sizeof(dest),src,sizeof(dst)/sizeof(dst[0])-strlen_s(dst,sizeof(dest)));
	
	return 0;
}
