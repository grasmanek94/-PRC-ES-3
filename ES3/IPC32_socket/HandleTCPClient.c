#include <stdio.h>
#include <ctype.h>      // for isupper() etc.
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()
#include <string.h>
#include <stdlib.h>		// free

#include "Auxiliary.h"
#include "HandleTCPClient.h"

#define RCVBUFSIZE 32   /* Size of receive buffer */

void HandleTCPClient (int clntSocket)
{
    // 'clntSocket' is obtained from AcceptTCPConnection()

    char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
    int  recvMsgSize;                   /* Size of received message */

    /* Receive message from client */
    recvMsgSize = recv (clntSocket, echoBuffer, RCVBUFSIZE-1, 0);
    if (recvMsgSize < 0)
    {
        DieWithError ("recv() failed");
    }
    info_d ("Recv", recvMsgSize);

    /* Send received string and receive again until end of transmission */
    while (recvMsgSize > 0)      /* zero indicates end of transmission */
    {
        // TODO: add code to print the received string; use printf()
		echoBuffer[recvMsgSize] = 0;//ensure string safety
		printf("Received string: %s\n", echoBuffer);
        // TODO: add code to convert the upper/lower chars of the received string
		for (char* c = echoBuffer; (size_t)c <= (size_t)echoBuffer + (size_t)recvMsgSize; ++c)
		{
			if (*c <= 'Z' && *c >= 'A')
			{
				*c += 'a' - 'A';
			}
			else if (*c <= 'z' && *c >= 'a')
			{
				*c -= 'a' - 'A';
			}
		}

        delaying ();
        
        /* Echo message back to client */
        if (send (clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
        {
            DieWithError ("send() failed");
        }

        // TODO: add code to display the transmitted string in verbose mode; use info_s()
		info_s("Sent string : ", echoBuffer);
		snprintf(echoBuffer, sizeof(echoBuffer), "%d", recvMsgSize);
		info_s("Size (bytes): ", echoBuffer);

        // receive next string
        recvMsgSize = recv (clntSocket, echoBuffer, RCVBUFSIZE-1, 0);
        if (recvMsgSize < 0)
        {
            DieWithError ("recv() failed");
        }
        info_d ("recv", recvMsgSize);
    }

    close (clntSocket);    /* Close client socket */
    info ("close");
}

void HandleTCPChatClient(int clntSocket)
{
	// 'clntSocket' is obtained from AcceptTCPConnection()

	char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
	int  recvMsgSize;                   /* Size of received message */
	char* line = NULL;

	while (true)
	{
		//waiting for chat message after connection is established
		recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE - 1, 0);
		if (recvMsgSize < 0)
		{
			if (recvMsgSize == 107/*ENOTCONN*/)
			{
				info("Client disconnected");
				break;
			}
			else
			{
				info("An error occured in recv()");
				break;
			}
		}

		if (recvMsgSize == 0)//we don't want empty messages
		{
			usleep(10000);
			continue;
		}

		info("received chat message");

		echoBuffer[recvMsgSize] = 0;//ensure string safety
		printf("Client: %s\nType your message:\n", echoBuffer);

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
				if (send(clntSocket, line, len, 0) != len)
				{
					DieWithError("send() failed");
				}
				else
				{
					printf("Server: %s\n", line);
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

	close(clntSocket);    /* Close client socket */
	info("close");
}
