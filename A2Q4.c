#include <assert.h>
#include <stdio.h>
#include <unistd.h>
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
#define MIN_FILESIZE 500
#define MAX_FILESIZE 40000
#define checking(string, val){if (val) { printf("Failed with %ld @ %s", val, string); exit(1);} }

//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------
void * printClientCode (void * tid);
void * printServerCode (void * tid);
char * concatenateTwo  (const char *a, const char *b);
char * concatenateThree(const char *a, const char *b, const char *c);

//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------
int main(int argc, const char * const argv[]) 
{
    int  numPrintClients;
    int  numPrinters;
    long rc;

    CircularBuffer buffer;
    PrintRequest   BoundedBuffer[MAX_BUFFERSIZE];

    assert(argc == 3);
    assert(argv != NULL);


    if(argc == 3 && argv != NULL)
    {
        numPrintClients = atoi(argv[1]);
        numPrinters     = atoi(argv[2]);
    }
    else
    {
        exit(1);
    }

    buffer.size   = MAX_BUFFERSIZE;
    buffer.buffer = BoundedBuffer;
    buffer.count  = 0;

    if(bufferInit(&buffer) == -1)
    {
        printf("Error initalizing the buffer");
        exit(1);
    }   


    //playing the role of the OS code that is managing each printer
    pthread_t printServers[numPrinters];
    //applications requesting printing
    pthread_t printClients[numPrintClients];


    for(int i = 0; i < numPrinters; i ++)
    {
        rc = pthread_create(&printServers[i], NULL, printServerCode, NULL);
        checking("Failed at creating print server with value: ", rc);
    }

    for(int j = 0; j < numPrintClients; j++)
    {
        rc = pthread_create(&printClients[j], NULL, printClientCode, NULL);
        checking("Failed at creating print client with value: ", rc);

    }
    pthread_exit(NULL);
    return EXIT_SUCCESS;
}
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
void * printClientCode(void * tid)
{
    char * string;
    char * string2;
    int    fileSize  = 0;
    long   pthreadId = (long)pthread_self();
    char   buffer  [sizeof(unsigned long)*8+1];
    char   buffer2 [sizeof(unsigned long)*8+1];

    //long to char and storing in buffer
    sprintf(buffer, "%lu", pthreadId); 

    for(int i = 0; i < 6; i ++)
    {
        sprintf(buffer2, "%lu", (long)i);

        //"random" size(in bytes) of the file between min and max
        fileSize = (rand() % (MIN_FILESIZE - MAX_FILESIZE)) + MAX_FILESIZE;

        string2  = concatenateTwo("-", buffer2);
        string   = concatenateThree("File-", buffer,  string2);

        printf("%s\n",string);

        if(bufferInsert(string, fileSize) == 0)
        {
            printf("File size: %d\n", fileSize);
            printf("%d: Hi, I am thread:'%ld'\n", i, (long)pthread_self());

            sleep((rand() % (0 - 3)) + 3);
        }
        else
        {
            printf("Error, could not insert: '%s'", string);
        }
        free(string);
        free(string2);
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
char * concatenateThree(const char * a, const char * b, const char * c) 
{
    size_t one   = strlen(a);
    size_t two   = strlen(b);
    size_t three = strlen(c);
    char * res   = malloc(one + two + three + 1);

    memcpy(res, a, one);
    memcpy(res + one, b, two);
    memcpy(res + one + two, c, three + 1);
    return res;
}

char * concatenateTwo(const char * a, const char * b)
{
    size_t one   = strlen(a);
    size_t two   = strlen(b);
    char * res   = malloc(one + two + 1);

    memcpy(res, a, one);
    memcpy(res + one, b, two + 1);
    return res;
}