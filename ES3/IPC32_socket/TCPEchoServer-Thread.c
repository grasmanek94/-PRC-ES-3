#ifdef _MSC_VER
typedef int pthread_t;
typedef int pthread_attr_t;
#define NULL (0)
#endif

#include <pthread.h>
#include <unistd.h> //close
#include <stdlib.h>     /* malloc, free */

#include "Auxiliary.h"
#include "AcceptTCPConnection.h"
#include "CreateTCPServerSocket.h"
#include "HandleTCPClient.h"

typedef struct
{
	int clntSock;
} SThreadArgs;

static void* myThread (void* arg);            /* thread that does the work */

int main (int argc, char *argv[])
{
    int         servSock;     /* Socket descriptor for server */
    int         clntSock;     /* Socket descriptor for client */
    pthread_t   threadID;     /* Thread ID from pthread_create() */
    bool        to_quit = false;

    parse_args (argc, argv);
    servSock = CreateTCPServerSocket (argv_port);
    while (to_quit == false)                /* run until someone indicates to quit... */
    {
        clntSock = AcceptTCPConnection (servSock);
		info("Client connected, creating thread...");

		SThreadArgs* args = (SThreadArgs*)malloc(sizeof(SThreadArgs));
		args->clntSock = clntSock;
		if(pthread_create(&threadID, NULL, myThread, (void*)args))
		{
			free(args);
			DieWithError("Thread creation failed");
		}
		if (pthread_detach(threadID))
		{
			DieWithError("Thread detach failed");
		}
    }

	close(servSock);
    // server stops...
	return (0);
}

static void *
myThread (void* threadArgs)
{
	int clntSock = ((SThreadArgs*)threadArgs)->clntSock;
	free(threadArgs);

	info("Thread handling socket...");
	HandleTCPClient(clntSock);
	info("... thread handled socket!");
    return (NULL);
}
