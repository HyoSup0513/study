#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ArrayQueueNodeType
{
    int data;
} Node;

typedef struct ArrayQueueType
{
    int maxCount;
    int currentCount;
    int front;
    int rear;
    Node *pData;
} ArrayQueue;

ArrayQueue *create(int size)
{
    ArrayQueue *queue = NULL;
    // Memory allocation for queue, initialize to 0.
    queue = (ArrayQueue *)malloc(sizeof(ArrayQueue));
    memset(queue, 0, sizeof(ArrayQueue));

    // Set the size of queue, position of front and rear.
    queue->maxCount = size;
    queue->currentCount = 0;
    queue->front = -1;
    queue->rear = -1;

    // Memory allocation for array, initialize to 0.
    queue->pData = (Node *)malloc(sizeof(Node) * size);
    memset(queue->pData, 0, sizeof(Node) * size);

    return queue;
}

int isQueueFull(ArrayQueue *queue)
{
    if (queue != NULL)
    {
        // Maximum number of nodes or "Rear" is at the end of the array.
        if (queue->currentCount == queue->maxCount || queue->rear == queue->maxCount - 1)
        {
            return 1;
        }
    }
    return 0;
}

int enqueue(ArrayQueue *queue, int data)
{
    if (queue != NULL)
    {
        if (isQueueFull(queue) == 0)
        {
            queue->rear++;                         // Change the position of rear
            queue->pData[queue->rear].data = data; // Add new data
            queue->currentCount++;
            return 1;
        }
    }
    return 0;
}

int isQueueEmpty(ArrayQueue *queue)
{
    if (queue != NULL && queue->currentCount == 0)
    {
        return 1;
    }
    return 0;
}

Node *dequeue(ArrayQueue *queue)
{
    Node *pReturn = NULL;
    if (queue != NULL && isQueueEmpty(queue) == 0)
    {
        pReturn = (Node *)malloc(sizeof(Node *));
        queue->front++;                                  // Change the position of front
        pReturn->data = queue->pData[queue->front].data; // Copy return node's value
        queue->currentCount--;
    }
    return pReturn;
}

Node *peek(ArrayQueue *queue)
{
    Node *pReturn = NULL;
    if (queue != NULL && isQueueEmpty(queue) == 0)
    {
        // Front points to the previous position of the front node.
        // So, "front + 1", to point to the current front node itself
        pReturn = &(queue->pData[queue->front + 1]);
    }
    return pReturn;
}

void deleteQueue(ArrayQueue *queue)
{
    if (queue != NULL && queue->pData != NULL)
    {
        free(queue->pData);
    }
    free(queue);
}

void display(ArrayQueue *queue)
{
    if (queue != NULL)
    {
        printf("Size of Queue:%d, Current number of nodes: %d\n", queue->maxCount, queue->currentCount);

        for (int i = queue->front + 1; i <= queue->rear; i++)
        {
            printf("[%d]-[%d]\n", i, queue->pData[i].data);
        }
    }
}

int main(int argc, char *argv[])
{
    ArrayQueue *queue = NULL;
    Node *testNode = NULL;

    queue = create(5);
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    enqueue(queue, 4);
    enqueue(queue, 5);
    display(queue);

    testNode = dequeue(queue);
    if (testNode != NULL)
    {
        printf("Dequeue Value-[%d]\n",
               testNode->data);
        free(testNode);
    }
    display(queue);

    testNode = peek(queue);
    if (testNode != NULL)
    {
        printf("Peek Value-[%d]\n",
               testNode->data);
    }

    deleteQueue(queue);

    return 0;
}