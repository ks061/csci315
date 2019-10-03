/*
 * CSCI 315 Operating Systems Design
 * Author: L. Felipe Perrone
 * Date: 2014-09-21
 * Copyright (c) 2014 Bucknell University
 *
 * Permission is hereby granted, free of charge, to any individual
 * or institution obtaining a copy of this software and associated
 * documentation files (the "Software"), to use, copy, modify, and
 * distribute without restriction, provided that this copyright
 * and permission notice is maintained, intact, in all copies and
 * supporting documentation.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL BUCKNELL UNIVERSITY BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "wrappers.h"

#define BUFFER_SIZE 512
#define TRUE 1
#define FALSE 0

/*------------------------------------------------------------------------
 * Program:   echoreq
 *
 * Purpose:  allocate a socket, connect to a server, transfer requested
 *            file to local host, and print file contents to stdout
 *
 * Usage:    echoreq [ host ] [ port ] [ string ] 
 *
 *		 host  - name of a computer on which server is executing
 *		 port  - protocol port number server is using
 *     string - a string in double quotes
 *     
 *------------------------------------------------------------------------
 */

int
main(int argc, char* argv[]) {
	char* host;      // pointer to the host
        char* port;      // pointer to port number
        char  in_msg[BUFFER_SIZE]; // buffer for incoming message

        struct addrinfo hints;
        struct addrinfo* res;
        
        int sd; // socket descriptor 

	// verify usage

	if (argc < 4) {
		printf("Usage: %s [ host ] [ port ] [ string ]\n", argv[0]);
		exit(-1);
	}

	host = argv[1];		
	port = argv[2];

        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;

	if (port > 0) {
                // test for legal value		
		getaddrinfo(host, port, &hints, &res);
	} else {				
		// print error message and exit	
		printf("ECHOREQ: bad port number %s\n", argv[2]);
		exit(-1);
	}


	// create socket 
	sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (sd < 0) {
		printf("ECHOREQ: socket creation failed\n");
		exit(-1);
	}
        printf("Update: Creation of socket (number: %d) successful.\n", sd);

	// struct sockaddr_in* sad_in = (struct sockaddr_in*)(res->ai_addr);
        // sad_in->sin_port = atoi(port);

        // connect the socket to the specified server 
        
        Connect(sd, res->ai_addr, res->ai_addrlen);  
        printf("Update: Connection on socket successful.\n");

        char* buf_to_server = argv[3];

	// send message to server
        send(sd, buf_to_server, BUFFER_SIZE, 0);
        printf("ECHOREQ: send = %s\n", buf_to_server);

	// receive message echoed back by server
        recv(sd, in_msg, BUFFER_SIZE, 0);
	printf("ECHOREQ: from server= %s\n", in_msg);

	// close the socket   
	close(sd);

	// terminate the client program gracefully 
	return(0);
}
