

#include <stdio.h>
#include <string.h>
#include <malloc.h>
 
/*!
 * Circular Buffer Example
 * Compile: gcc cbuf.c -o cbuf.exe
 */
 
/**< Buffer Size */
#define BUFFER_SIZE  16 
 
/**< Circular Buffer Types */
typedef unsigned char INT8U;
typedef INT8U KeyType;
typedef struct
{
   INT8U writePointer; /**< write pointer */
   INT8U readPointer;  /**< read pointer */
   INT8U size;         /**< size of circular buffer */
   KeyType keys[0];    /**< Element of ciruclar buffer */
} CircularBuffer;
 
/**< Init Ciruclar Buffer */
CircularBuffer* CircularBufferInit(CircularBuffer** pQue, int size)
{
	int sz = size*sizeof(KeyType)+sizeof(CircularBuffer);
        *pQue = (CircularBuffer*) malloc(sz);
        if(*pQue)
        {
            printf("Init CircularBuffer: keys[%d] (%d)\n", size, sz);
            (*pQue)->size=size;
            (*pQue)->writePointer = 0;
            (*pQue)->readPointer  = 0;
        }
        return *pQue;
}
 
inline int CircularBufferIsFull(CircularBuffer* que)
{
     return ((que->writePointer + 1) % que->size == que->readPointer); 
}
 
inline int CircularBufferIsEmpty(CircularBuffer* que)
{
     return ((que->readPointer + 1) % que->size == que->writePointer); 
}
 
inline int CircularBufferEnque(CircularBuffer* que, KeyType k)
{
        int isFull = CircularBufferIsFull(que);
        que->keys[que->writePointer] = k;
        que->writePointer++;
        que->writePointer %= que->size;
        return isFull;
}
 
inline int CircularBufferDeque(CircularBuffer* que, KeyType* pK)
{
        int isEmpty =  CircularBufferIsEmpty(que);
        *pK = que->keys[que->readPointer];
        que->readPointer++;
        que->readPointer %= que->size;
        return(isEmpty);
}
 
int main(int argc, char *argv[])
{
        CircularBuffer* que;
        KeyType a = 0;
        int isEmpty;
        CircularBufferInit(&que, BUFFER_SIZE);
 
        while(! CircularBufferEnque(que, a++));
 
        do {
            isEmpty = CircularBufferDeque(que, &a); 
            printf("%02d ", a);
        } while (!isEmpty);
        printf("\n");
        free(que);
        return 0;
}

