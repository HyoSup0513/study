#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CircularQueueNodeType
{
    char data;
} CircularQueueNode;

typedef struct CircularQueueType
{
    int maxCount;     // Maximum Number of node
    int currentCount; // Current Number of node
    int front;        // Position of front
    int rear;         // position of rear
    CircularQueueNode *pData;
} CircularQueue;

CircularQueue *createCircularQueue(int size)
{

    CircularQueue *pReturn = NULL;
    // Memory allocation, initialize memory to 0.
    pReturn = (CircularQueue *)malloc(sizeof(CircularQueue));
    memset(pReturn, 0, sizeof(CircularQueue));

    // Set the size of queue, initialize the position of front and rear
    pReturn->maxCount = size;
    pReturn->front = -1;
    pReturn->rear = -1;

    // Allocate memory for the arrary storing the data, initialize memory to 0
    pReturn->pData = (CircularQueueNode *)malloc(sizeof(CircularQueueNode) * size);
    memset(pReturn->pData, 0, sizeof(CircularQueueNode) * size);

    return pReturn;
}

int isCircularQueueFull(CircularQueue *pQueue)
{
    int ret = 0;
    if (pQueue != NULL)
    {
        if (pQueue->currentCount == pQueue->maxCount)
        {
            ret = 1;
        }
    }

    return ret;
}

int isCircularQueueEmpty(CircularQueue *pQueue)
{
    int ret = 0;

    if (pQueue != NULL)
    {
        if (pQueue->currentCount == 0)
        {
            ret = 1;
        }
    }

    return ret;
}

int enqueueCQ(CircularQueue *pQueue, char data)
{
    int ret = 0;

    if (pQueue != NULL)
    {
        if (isCircularQueueFull(pQueue) == 0)
        {
            pQueue->rear = (pQueue->rear + 1) % pQueue->maxCount; // Change the position of rear
            pQueue->pData[pQueue->rear].data = data;              // Add new data
            pQueue->currentCount++;                               // +1 number of node
            ret = 1;
        }
        else
        {
            printf("Error, Queue is full!, enqueueCQ()\n");
        }
    }

    return ret;
}

CircularQueueNode *dequeueCQ(CircularQueue *pQueue)
{

    CircularQueueNode *pReturn = NULL;

    if (pQueue != NULL)
    {
        if (isCircularQueueEmpty(pQueue) == 0)
        {
            pReturn = (CircularQueueNode *)malloc(sizeof(CircularQueueNode));
            if (pReturn != NULL)
            {
                pQueue->front = (pQueue->front + 1) % pQueue->maxCount;
                pReturn->data = pQueue->pData[pQueue->front].data;
                pQueue->currentCount--;
            }
            else
            {
                printf("Error, memory allocation,dequeueCQ()\n");
            }
        }
    }

    return pReturn;
}

CircularQueueNode *peekCQ(CircularQueue *pQueue)
{
    CircularQueueNode *pReturn = NULL;
    if (pQueue != NULL)
    {
        if (isCircularQueueEmpty(pQueue) == 0)
        {
            pReturn = &(pQueue->pData[pQueue->front + 1]);
        }
    }

    return pReturn;
}

void displayCQ(CircularQueue *pQueue)
{
    int i = 0;
    int position = 0;

    if (pQueue != NULL)
    {
        printf("Size of queue: %d, Current number of nodes: %d\n",
               pQueue->maxCount, pQueue->currentCount);

        for (i = pQueue->front + 1; i <= pQueue->front + pQueue->currentCount; i++)
        {
            position = i % pQueue->maxCount;
            printf("[%d]-[%c]\n", position, pQueue->pData[position].data);
        }
    }
}

int main(int argc, char *argv[])
{
    CircularQueue *pQueue = NULL;
    CircularQueueNode *pNode = NULL;

    pQueue = createCircularQueue(4);

    if (pQueue != NULL)
    {
        enqueueCQ(pQueue, 'A');
        enqueueCQ(pQueue, 'B');
        enqueueCQ(pQueue, 'C');
        enqueueCQ(pQueue, 'D');
        displayCQ(pQueue);

        pNode = dequeueCQ(pQueue);
        if (pNode != NULL)
        {
            printf("Dequeue value-[%c]\n", pNode->data);
            free(pNode);
        }

        displayCQ(pQueue);

        pNode = peekCQ(pQueue);
        if (pNode != NULL)
        {
            printf("Peek Value-[%c]\n", pNode->data);
        }
        displayCQ(pQueue);

        enqueueCQ(pQueue, 'E');
        displayCQ(pQueue);
    }
    return 0;
}