#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "boundedBuffer.h"

#define MAX_BUFFERSIZE 4

pthread_cond_t  Empty   = PTHREAD_COND_INITIALIZER;
pthread_cond_t  Full    = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock    = PTHREAD_MUTEX_INITIALIZER;

static int    rc        = 0;
static size_t head      = 0;
static size_t tail      = 0;
static size_t buffCount = 0;//current number of items in the buffer
static size_t buffSize  = MAX_BUFFERSIZE;//size of the buffer
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
int bufferInsert(PrintRequest buffer[], char * string, int size)
{
    int result = -1;
    pthread_mutex_lock(&lock);
    
    printf("Size:%lu  Count:%lu  \n", buffSize, buffCount);
    while(buffSize == buffCount)
    {
        rc = pthread_cond_wait(&Full, &lock);
        if(rc){printf("Failed waitng to insert... while still full"); exit(1);} 
    }
    //the acctual adding to the buffer goes here
    if(buffer != NULL)
    {
        buffer[head].fileSize = size;
        buffer[head].fileName = string;

        head      = (head + 1) % buffSize;
        buffCount = buffCount + 1;


        //if head and tail 'pointers' are equal after incremenitng the head, need to increment the tail also by one
        if(head == tail)
        {
            tail = (tail + 1) % size;
        }
        result = 0;
    }
    else
    {
        printf("Error with the buffer, @ inserting");
        exit(1);
    }


    pthread_cond_signal(&Empty); 
    pthread_mutex_unlock(&lock);
    return result;
}
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
int buffertDelete(PrintRequest * buffer, char ** resultString)
{
    int result = -1;
    pthread_mutex_lock(&lock);

    while(buffCount == 0)
    {
        rc = pthread_cond_wait(&Empty, &lock);
        if(rc){printf("Failed waitng to delete... while still empty"); exit(1);} 
    }
    //the acctual deleting from the buffer goes here
    if(buffer != NULL && buffCount != 0)
    {
        *resultString = buffer[tail].fileName;
        
        tail = (tail + 1) % buffSize;

        buffCount--;
        result = 0;
    }
    else
    {
        printf("Error with the buffer, @ deleting");
        exit(1);
    }


    pthread_cond_signal(&Full);
    pthread_mutex_unlock(&lock);
    return result;
}
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
int bufferSearch(PrintRequest * buffer, const char * string)
{
   return 0; 
}
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
Boolean bufferIsFull(PrintRequest buffer)
{
    Boolean result;
    pthread_mutex_lock(&lock);

    if(buffSize == buffCount)
    {
        result = true;
    }
    else
    {
        result = false;
    }
    pthread_mutex_unlock(&lock);
    return result;
}
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

Boolean bufferIsEmpty(PrintRequest buffer)
{
    Boolean result;
    pthread_mutex_lock(&lock);

    if(buffCount == 0)
    {
        result = true;
    }
    else
    {
        result = false;
    }
    pthread_mutex_unlock(&lock);
    return result;
}
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------