#if 0
	Copyright 2018-INFINITY Tanveer Salim.

	License: GNU GPL v2.0 License

Any modified forms of this file must explicitly state that it was adapted from this file and the author and must also have the exact license and copyright conditions this file has.

#endif

#if 0

Purpose: 

Prints the complete URL

of input argv[1]

and 

it's hostname

and

it's servicename (portnumber)

and

application presentation of an

IPv4/6 website.

#endif

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>



#if 0
	DO NOT USE gethostbyaddr nor

	gethostbyname. Just use

	getaddrinfo() and getnameinfo()

	Do NOT use inet_aton nor

	inet_ntoa, USE inet_ntop()

	nor inet_pton()
#endif	

#if 0

Hostname will be converted into correct

application presentation

#endif

int main(int argc, char ** argv)
{
	char ** p = NULL;
	
	static char ipv6[INET6_ADDRSTRLEN];
	
	int gstrerr = 0;

	static char * hostname[1024];

	static char * servname[32]; 
	

	printf("IPv6 address: %s\n",ipv6);

	if ( argc != 2 )
	{
	
		fprintf(stderr,"usage %s <domain name or application representation>\n",argv[0]);
		
		exit(0);
	}
	

	return 0;
}
