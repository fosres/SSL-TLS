#include <stdio.h>
static char arr[256];
int main(void)
{
	rsize_t i = 0;

	rsize_t opening = 9;
	
	char * q[] =
	{
"#include <stdio.h>",
"",
"int main(void)",
"{",
"	rsize_t i = 0;",
"",
"	rsize_t opening = 9;",
"	",
"	char * q[] =",
"	{",
"	};",
"	while ( i <= opening )",
"	{",
"		printf(q[i]);",
"		putchar(10);",
"		i++;",
"	}",
"	i = 0;",
"	while ( q[i] != NULL )",
"	{",
"		putchar(34);",
"		printf(q[i]);",
"		putchar(34);",
"		putchar(44);",
"		putchar(10);",
"		i++;",
"	}",
"	putchar(78);putchar(85);putchar(76);putchar(76);",
"	putchar(10);",
"	i = opening+1;",
"	while ( q[i] != NULL )",
"	{",
"		printf(q[i]);",
"		putchar(10);",
"		i++;",
"	}",
"	return 0;",
"}",
NULL
	};
	while ( i <= opening )
	{
		printf(q[i]);
		putchar(10);
		i++;
	}
	i = 0;
	while ( q[i] != NULL )
	{
		putchar(34);
		printf(q[i]);
		putchar(34);
		putchar(44);
		putchar(10);
		i++;
	}
	putchar(78);putchar(85);putchar(76);putchar(76);
	putchar(10);
	i = opening+1;
	while ( q[i] != NULL )
	{
		printf(q[i]);
		putchar(10);
		i++;
	}

	return 0;


}
