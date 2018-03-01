#ifndef BOUNDEDBUFFER_H               
#define BOUNDEDBUFFER_H   

typedef enum { false, true } Boolean;

typedef struct PR 
{
    long   clientID;
    char * fileName; //ptr to a dynamically alloc’d string
    int    fileSize;
} PrintRequest, *PrintRequestPTR;

int bufferInsert(PrintRequest * buffer, char * string, int fileSize);

int buffertDelete(PrintRequest * buffer, char ** resultString);

int bufferSearch(PrintRequest * buffer, const char * string);


//these two functions are implemented but not needed for this question
Boolean bufferIsFull(PrintRequest buffer);

Boolean bufferIsEmpty(PrintRequest buffer);

#endif 