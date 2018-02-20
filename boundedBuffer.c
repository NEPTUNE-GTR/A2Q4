#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "boundedBuffer.h"

pthread_mutex_t lock      = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition = PTHREAD_COND_INITIALIZER;


int bufferInit(CircularBuffer * buffer)
{
    int result = -1;
    
    if(buffer != NULL)
    {
        result = 0;
        buffer->head = 0;
        buffer->tail = 0;
    }
    return result;
}

int bufferInsert()
{
    pthread_mutex_lock(&lock);  //tofinish this convar........................
    while(true)
    {
        
    }
    return 0;
}

int buffertDelete()
{
    return 0;
}

int bufferSearch()
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