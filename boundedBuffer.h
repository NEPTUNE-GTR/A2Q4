#ifndef BOUNDEDBUFFER_H               
#define BOUNDEDBUFFER_H   

typedef enum { false, true } Boolean;

typedef struct PR 
{
    long   clientID;
    char * fileName; //ptr to a dynamically alloc’d string
    int    fileSize;
} PrintRequest, *PrintRequestPTR;


typedef struct
{
    //unsigned because head, tail, and size should not be negative
    size_t head;
    size_t tail;
    size_t size;     //size of the buffer
    size_t count;    //current number of items in the buffer

    PrintRequest * buffer; 
} CircularBuffer;


// prototype definitions for the list operations
int bufferInit(CircularBuffer * buffer);

int bufferInsert();

int buffertDelete();

int bufferSearch();

Boolean bufferIsFull(CircularBuffer buffer);

Boolean bufferIsEmpty(CircularBuffer buffer);

#endif 