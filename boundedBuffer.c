#include <stdio.h>
#include <stdlib.h>
#include "boundedBuffer.h"

pthread_mutex_t lock;


int bufferInit()
{
    return 0;
}

int bufferInsert()
{
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

Boolean bufferIsFull(PrintRequest buffer)
{
    return (buffer.size == buffer.count);
}

Boolean bufferIsEmpty()
{
    return false;
}