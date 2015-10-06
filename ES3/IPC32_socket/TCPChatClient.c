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
    char        echoBuffer[RCVBUFSIZE]; /* Buffer for received string */
    int         bytesRcvd;              /* Bytes read in single recv() */
	char*		line = NULL;

    parse_args (argc, argv);

    sock = CreateTCPClientSocket (argv_ip, argv_port);
        
	while (true)
	{
		printf("Type your message:\n");

		line = ANSIC_getline();

		if (line)
		{
			int len = strlen(line) + 1;
			if (!strcmp(line, ":Q\n"))
			{
				break;
			}
			else
			{
				if (send(sock, line, len, 0) != len)
				{
					DieWithError("send() failed");
				}										 
				else								  ///////////////////////////////////////////////////
				{									   /////										  ///
					printf("Client: %s\n", line);		//											  ///
					inner_loop://this is justified because we are in an inner loop, goto/labels are made FOR this!
					{																				  ///
						bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0);						 /////
						if (bytesRcvd < 0)															///////
						{																			  ///
							DieWithError("recv() failed");											  ///
						}																			  ///
						else																		  ///
						{																			  ///
							if (bytesRcvd == 0)//we don't want empty messages						  ///
							{																		  ///
								usleep(10000);														  ///
								goto inner_loop;/////////////////////////////////////////////////////////
							}

							echoBuffer[bytesRcvd] = 0;
							printf("Server: %s\n", echoBuffer);
						}
					}
				}
			}
			free(line);
			line = NULL;
		}
		else
		{
			DieWithError("Cannot read stdin");
		}
	}

	if (line)
	{
		free(line);
		line = NULL;
	}

    close (sock);
    info ("close & exit");
    exit (0);
}
