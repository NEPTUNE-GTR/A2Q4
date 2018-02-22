#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "boundedBuffer.h"

pthread_cond_t  Empty   = PTHREAD_COND_INITIALIZER;
pthread_cond_t  Full    = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock    = PTHREAD_MUTEX_INITIALIZER;

int rc = 0;

int bufferInit(CircularBuffer * buffer)
{
    int result = -1;
    
    if(buffer != NULL)
    {
        buffer->head = 0;
        buffer->tail = 0;
        result       = 0;
    }
    return result;
}

int bufferInsert(CircularBuffer * buffer, const char * string, int fileSize)
{
    int result = -1;
    pthread_mutex_lock(&lock);

    while(buffer->size == buffer->count)
    {
        rc = pthread_cond_wait(&Full, &lock);
        if(rc){printf("Failed at waitng to insert while still full"); exit(1);} 
    }
    //the acctual adding to the buffer goes here
    if(buffer != NULL)
    {
        buffer->buffer[buffer->head].fileSize = fileSize;
        buffer->head = (buffer->head + 1) % buffer->size;

        if(buffer->head == buffer->tail)
        {
            buffer->tail = (buffer->tail + 1) % buffer->size;
        }
    }


    pthread_cond_signal(&Empty); 
    pthread_mutex_unlock(&lock);
    return 0;
}

int buffertDelete(CircularBuffer * buffer)
{
    int result = -1;
    pthread_mutex_lock(&lock);

    while(buffer->count == 0)
    {
        rc = pthread_cond_wait(&Empty, &lock);
        if(rc){printf("Failed at waitng to delete while still empty"); exit(1);} 
    }
    //the acctual deleting from the buffer goes here

    pthread_cond_signal(&Full);
    pthread_mutex_unlock(&lock);
    return 0;
}

int bufferSearch(CircularBuffer * buffer, const char * string)
{
   return 0; 
}

Boolean bufferIsFull(CircularBuffer buffer)
{
    Boolean result;
    pthread_mutex_lock(&lock);

    if(buffer.size == buffer.count)
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

Boolean bufferIsEmpty(CircularBuffer buffer)
{
    Boolean result;
    pthread_mutex_lock(&lock);

    if(buffer.count == 0)
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