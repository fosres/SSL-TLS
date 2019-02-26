#if 0
	Copyright 2018-INFINITY Tanveer Salim.

	LICENSE: GNU GPL v2.0

	This document may be viewed, copied, and modified provided it has the same

	copyright and licensing status as this file.
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char ** argv)
{

	if ( argc != 2)
	{
		printf("Error: Only two arguments should be inputted into stdin\n");

		exit(1);
	}	
	
	char * msg = "Testing.\0";

	int connect_status = 0;

	int socketd = 0;

	int sent_bytes = 0;

	int gstrerr = 0;

	static struct addrinfo hints, *res;	

	memset(&hints,0,sizeof(hints));

	hints.ai_family = AF_UNSPEC;

	hints.ai_socktype = SOCK_STREAM;

	if ( (gstrerr = getaddrinfo(argv[1],"https",&hints,&res)) != 0)
	{
		fprintf(stderr,"%d: getaddrinfo: %s\n",__LINE__,gai_strerror(gstrerr));

		exit(1);

	}

	if ( (socketd = socket(res->ai_family,res->ai_socktype,res->ai_protocol)) == -1)
	{
		fprintf(stderr,"%d: ",__LINE__);

		perror("socket()");

	}

	if ( (connect_status = connect(socketd,res->ai_addr,res->ai_addrlen)) == -1)
	{
		fprintf(stderr,"%d: ",__LINE__);

		perror("connect()");

		exit(1);

	}

	if ( (sent_bytes = send(socketd,msg,strlen(msg)+1,0)) == -1)
	{
		fprintf(stderr,"%d: ",__LINE__);

		perror("send()");

		exit(1);

	}	
	
	printf("String sent to %s: %s\n",argv[1],msg);	
	
	printf("Number of bytes sent to %s: %d\n",argv[1],sent_bytes);	
	
	printf("Now freeing struct addrinfos *res\n");

	freeaddrinfo(res);

	
	return 0;
}
