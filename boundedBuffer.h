#ifndef BOUNDEDBUFFER_H               
#define BOUNDEDBUFFER_H   

typedef struct PR {
    long   clientID;
    char * fileName; //ptr to a dynamically alloc’d string
    int    fileSize;
 } PrintRequest, *PrintRequestPTR;


// prototype definitions for the list operations
void bufferInsert();

void buffertDelete();

long bufferSearch();



 #endif 