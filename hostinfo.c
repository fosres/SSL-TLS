#if 0
	Copyright 2018-INFINITY Tanveer Salim.

	License: GNU GPL v2.0 License

Any modified forms of this file must explicitly state that it was adapted from this file and the author and must also have the exact license and copyright conditions this file has.

#endif

#if 0
	Adapted from Beejs Network Programming showip.c file

#endif

#if 0

Purpose: 

Prints the complete URL

of input argv[1]

and 

its hostname

and

its servicename (portnumber)

and

application presentation of an

IPv4/6 website.

#endif

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>



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
	
	static char ipstr[INET6_ADDRSTRLEN];
	
	int gstrerr = 0;
	
	struct addrinfo * hints = (struct addrinfo *)calloc(2,sizeof(struct addrinfo));

	struct addrinfo ** res = NULL, *p = NULL; 


	if ( argc != 2 )
	{
	
		fprintf(stderr,"usage %s <domain name or application representation>\n",argv[0]);
		
		exit(1);
	}
	
		
	hints->ai_family  = AF_UNSPEC; //getaddrinfo will correctly fill out information whether IPv4 or IPv6

	hints->ai_socktype = SOCK_STREAM; //official connection-based protocol for TCP communication

	hints->ai_flags = AI_PASSIVE;

	if ( (gstrerr = getaddrinfo(argv[1], NULL, hints, res) ) != 0 )
	{
		fprintf( stderr, "getaddrinfo: %s\n", gai_strerror(gstrerr) );

		exit(2);

	}

	printf("IP addresses for %s:\n\n",argv[1]);
	
	void * addr = NULL;

	char * ipversion = NULL;
	
	struct sockaddr_in * ipv4 = NULL;	
	
	struct sockaddr_in * ipv6 = NULL;	
	
	for ( p = *res; p != NULL; p = p->ai_next)
	{

		if ( p->ai_family == AF_INET)
		{
			ipv4 = (struct sockaddr_in *)&(p->ai_addr);
			
			addr = (struct in_addr *)&(ipv4->sin_addr);

			ipversion = "IPv4\0";
		}	
		
		else
		{
			struct sockaddr_in6 * ipv6 = (struct sockaddr_in6 *)p->ai_addr;

			addr = (struct in6_addr *)&(ipv6->sin6_addr);
			
			ipversion = "IPv6\0";

		}
		
//inet_ntop converts network byte order from struct addrinfo * to a presentation format for the respective IP version

		inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr) );
		
		printf(" %s: %s\n", ipversion, ipstr);
	}
	
	freeaddrinfo(*res);	
	
	freeaddrinfo(hints);	
	
	return 0;
}
