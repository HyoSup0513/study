#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HeapNodeType
{
    int data;
} HeapNode;

typedef struct ArrayHeapType
{
    int maxCount;     // Max number of data
    int currentCount; // Current number of data
    HeapNode *pData;  // array to store node
} MaxHeap, MinHeap;

MaxHeap *createMaxHeap(int maxCount)
{
    MaxHeap *pReturn = NULL;
    if (maxCount > 0)
    {
        pReturn = (MaxHeap *)malloc(sizeof(MaxHeap));
        pReturn->maxCount = maxCount;
        pReturn->currentCount = 0;
        pReturn->pData = (HeapNode *)malloc(sizeof(HeapNode) * (maxCount + 1));
        memset(pReturn->pData, 0, sizeof(HeapNode *) * (maxCount + 1));
    }

    else
    {
        printf("Maximum number of nodes must be greather than zero\n");
    }

    return pReturn;
}

int insertMaxHeap(MaxHeap *pHeap, int value)
{
    int i = 0;

    if (pHeap != NULL)
    {
        if (pHeap->currentCount == pHeap->maxCount)
        {
            printf("Error, heap is full![%d],insertMaxHeap()\n", pHeap->maxCount);
            return 0;
        }
        pHeap->currentCount++;
        i = pHeap->currentCount;
        while ((i != 1) && (value > pHeap->pData[i / 2].data))
        {
            pHeap->pData[i] = pHeap->pData[i / 2];
            i /= 2;
        }
        pHeap->pData[i].data = value;
    }
    return i;
}

HeapNode *removeMaxHeap(MaxHeap *pHeap)
{
    HeapNode *pReturn = NULL;
    HeapNode *pTemp = NULL;
    int parent = 1, child = 2;

    if (pHeap != NULL && pHeap->currentCount > 0)
    {
        pReturn = (HeapNode *)malloc(sizeof(HeapNode));

        if (pReturn == NULL)
        {
            printf("Error, memory allcation, removeMaxHeap()\n");
            return NULL;
        }
        pReturn->data = pHeap->pData[1].data;

        pTemp = &(pHeap->pData[pHeap->currentCount]);
        pHeap->currentCount--;

        while (child <= pHeap->currentCount)
        {
            if ((child < pHeap->currentCount) && pHeap->pData[child].data < pHeap->pData[child + 1].data)
            {
                child++;
            }

            if (pTemp->data >= pHeap->pData[child].data)
            {
                break;
            }

            pHeap->pData[parent] = pHeap->pData[child];
            parent = child;
            child *= 2;
        }
        pHeap->pData[parent] = *pTemp;
    }
    return pReturn;
}

void deleteMaxHeap(MaxHeap *pHeap)
{
    if (pHeap != NULL)
    {
        if (pHeap->pData != NULL)
        {
            free(pHeap->pData);
        }
        free(pHeap);
    }
}

void display(MaxHeap *pHeap)
{
    int i = 0;
    if (pHeap != NULL)
    {
        for (i = 1; i <= pHeap->currentCount; i++)
        {
            printf("[%d],%d\n", i, pHeap->pData[i].data);
        }
    }
}

int main(int argc, char *argv[])
{
    int maxHeapSize = 20;
    MaxHeap *pHeap1 = NULL;
    HeapNode *pNode = NULL;

    pHeap1 = createMaxHeap(maxHeapSize);
    if (pHeap1 != NULL)
    {
        insertMaxHeap(pHeap1, 90);
        insertMaxHeap(pHeap1, 85);
        insertMaxHeap(pHeap1, 80);
        insertMaxHeap(pHeap1, 75);
        insertMaxHeap(pHeap1, 70);
        insertMaxHeap(pHeap1, 65);
        insertMaxHeap(pHeap1, 60);
        insertMaxHeap(pHeap1, 55);
        insertMaxHeap(pHeap1, 50);
        insertMaxHeap(pHeap1, 45);
        insertMaxHeap(pHeap1, 40);
        insertMaxHeap(pHeap1, 35);
        insertMaxHeap(pHeap1, 30);

        printf("Max Heap:\n");
        display(pHeap1);

        insertMaxHeap(pHeap1, 100);
        printf("After insertMaxHeap()-[%d]\nMax Heap:\n", 100);
        display(pHeap1);

        pNode = removeMaxHeap(pHeap1);
        if (pNode != NULL)
        {
            printf("removeMaxHeap()-[%d]\n", pNode->data);
            free(pNode);
        }
        printf("Max Heap:\n");
        display(pHeap1);

        deleteMaxHeap(pHeap1);
    }
    return 0;
}