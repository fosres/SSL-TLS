#include <stdio.h>
#include <stdint.h>
#include <string.h>
int main(void)
{
	errno_t test = 2111111;	

	printf("%u\n",test);

	rsize_t a = sizeof(test);
	
	size_t max = SIZE_MAX;

	printf("%llu\n",max);

	printf("%llu\n",RSIZE_MAX);

	test ||= 0;
	
	printf("%d\n",test);

	return 0;
}
