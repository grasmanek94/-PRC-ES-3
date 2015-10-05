#include <stdio.h>
#include <string.h>     // for strlen()
#include <stdlib.h>     // for exit()
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()

#include "Auxiliary.h"
#include "CreateTCPClientSocket.h"

#define RCVBUFSIZE 32   /* Size of receive buffer */

int main (int argc, char *argv[])
{
    int         sock;                   /* Socket descriptor */
    char *      echoString;             /* String to send to echo server */
    char        echoBuffer[RCVBUFSIZE]; /* Buffer for received string */
    int         echoStringLen;          /* Length of string to echo */
    int         bytesRcvd;              /* Bytes read in single recv() */
    int         i;                      /* counter for data-arguments */

    parse_args (argc, argv);

    sock = CreateTCPClientSocket (argv_ip, argv_port);
        
    for (i = 0; i < argv_nrofdata; i++)
    {
        echoString = argv_data [i];
		echoStringLen = strlen(echoString) + 1;          /* Determine input length */

        delaying();

		// TODO: add code to send this string to the server; use send()
		if (send(sock, echoString, echoStringLen, 0) != echoStringLen)
		{
			DieWithError("send() failed");
		}
       
		// TODO: add code to display the transmitted string in verbose mode; use info_s()
		info_s("Sent string : ", echoString);
		snprintf(echoBuffer, sizeof(echoBuffer), "%d", echoStringLen);
		info_s("Size (bytes): ", echoBuffer);
		info_s("To          : ", argv_ip);
		snprintf(echoBuffer, sizeof(echoBuffer), "%d", argv_port);
		info_s("On Port     : ", echoBuffer);

        // TODO: add code to receive & display the converted string from the server
        //       use recv() & printf()
		bytesRcvd = recv(sock, echoBuffer, sizeof(echoBuffer) - sizeof(char), 0);
		if (bytesRcvd > 0)
		{
			echoBuffer[bytesRcvd] = 0;
			printf("Received: %s\n", echoBuffer);
		}
		else
		{
			printf("Received nothing...\n");
		}
    }

    delaying ();

    close (sock);
    info ("close & exit");
    exit (0);
}
