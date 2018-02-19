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

PrintRequest BoundedBuffer[MAX_BUFFERSIZE];

//global variables to keep the address of the front and rear nodes of the buffer
PrintRequestPTR	front;
PrintRequestPTR	rear;
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

    assert(argc == 3);
    assert(argv != NULL);

    if(argc == 3 && argv != NULL)
    {
        numPrintClients = atoi(argv[1]);
        numPrinters     = atoi(argv[2]);
    }

    //playing the role of the OS code that is managing each printer
    pthread_t printServers[numPrinters];

    //applications requesting printing
    pthread_t printClients[numPrintClients];

    for(int i = 0; i < numPrinters; i ++)
    {
        rc = pthread_create(&printServers[i], NULL, printClientCode, (void *)i);

        if(rc) 
        {
            printf("ERROR with threading"); 
            exit(-1);
        } 
    }

    for(int j = 0; j < numPrintClients; j++)
    {
        rc = pthread_create(&printClients[i], NULL, printClientCode, (void *)i);

        if(rc) 
        {
            printf("ERROR with threading"); 
            exit(-1);
        } 

    }



    pthread_exit(NULL);
    return EXIT_SUCCESS;
}
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
