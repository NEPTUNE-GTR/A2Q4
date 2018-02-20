#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include "boundedBuffer.h"
//-------------------------------------------------------------------------------------
// Course:     COMP3430
// Section:    A01
// Assignment: 2, question 4
// Name:       Eddie Torres
// UM-ID:      umtorre8
// Semester:   Winter, 2018
// Description- 
//              
//              
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES
//-------------------------------------------------------------------------------------
#define MAX_PRINTREQUESTS 6
#define MAX_BUFFERSIZE 4
#define checking(string, val){if (val) { printf("Failed with %ld @ %s", val, string); exit(1);} }

Boolean isEmpty;


PrintRequest BoundedBuffer[MAX_BUFFERSIZE];
//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------
void * printClientCode(void * tid);
void * printServerCode(void * tid);

//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------
int main(int argc, const char * const argv[]) 
{
    int  numPrintClients;
    int  numPrinters;
    long rc;
    //playing the role of the OS code that is managing each printer
    pthread_t printServers[numPrinters];

    //applications requesting printing
    pthread_t printClients[numPrintClients];

    assert(argc == 3);
    assert(argv != NULL);

    if(argc == 3 && argv != NULL)
    {
        numPrintClients = atoi(argv[1]);
        numPrinters     = atoi(argv[2]);
    }

    for(int i = 0; i < numPrinters; i ++)
    {
        rc = pthread_create(&printServers[i], NULL, printServerCode, NULL);
        checking("Faile at creating print server with value: ", rc);
    }

    for(int j = 0; j < numPrintClients; j++)
    {
        rc = pthread_create(&printClients[j], NULL, printClientCode, NULL);
        checking("Faile at creating print client with value: ", rc);

    }
    pthread_exit(NULL);
    return EXIT_SUCCESS;
}
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
void * printClientCode(void * tid)
{
    long   pthreadId = (long)pthread_self();
    char * fileName  = "File";

    for(int i = 0; i < 6; i ++)
    {
        bufferInsert();
        
    }

    pthread_exit(NULL);
}
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
void * printServerCode(void * tid)
{

    pthread_exit(NULL);
}
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------