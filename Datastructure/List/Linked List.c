#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedListNodeType
{
    int data;
    struct LinkedListNodeType *pLink;
} LinkedListNode;

typedef struct LinkedListType
{
    int currentCount;
    LinkedListNode headerNode;
} LinkedList;

LinkedList *createLinkedList()
{
    LinkedList *pReturn = (LinkedList *)malloc(sizeof(LinkedList));
    memset(pReturn, 0, sizeof(LinkedList)); // memory initialization to 0
    return pReturn;
}

int getLinkedListData(LinkedList *pList, int position)
{
    int i = 0;
    LinkedListNode *pCurrentNode = &(pList->headerNode);
    for (i = 0; i <= position; i++)
    {
        pCurrentNode = pCurrentNode->pLink;
    }

    return pCurrentNode->data;
}

int addLinkedListData(LinkedList *pList, int position, int data)
{
    int i = 0;
    LinkedListNode *pNewNode = NULL;
    LinkedListNode *pPrevNode = NULL;

    pNewNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    pNewNode->data = data;

    pPrevNode = &(pList->headerNode);
    for (i = 0; i < position; i++)
    {
        pPrevNode = pPrevNode->pLink;
    }

    pNewNode->pLink = pPrevNode->pLink;
    pPrevNode->pLink = pNewNode;
    pList->currentCount++;

    return 0;
}

int removeLinkedListData(LinkedList *pList, int position)
{
    int i = 0;
    LinkedListNode *pDelNode = NULL;
    LinkedListNode *pPrevNode = NULL;

    pPrevNode = &(pList->headerNode);
    for (i = 0; i < position; i++)
    {
        pPrevNode = pPrevNode->pLink;
    }

    pDelNode = pPrevNode->pLink;
    pPrevNode->pLink = pDelNode->pLink;
    free(pDelNode);
    pList->currentCount--;

    return 0;
}

void deleteLinkedList(LinkedList *pList)
{
    LinkedListNode *pDelNode = NULL;
    LinkedListNode *pPrevNode = pList->headerNode.pLink;
    while (pPrevNode != NULL)
    {
        pDelNode = pPrevNode;
        pPrevNode = pPrevNode->pLink;

        free(pDelNode);
    }

    free(pList);
}

int getLinkedListLength(LinkedList *pList)
{
    if (pList != NULL)
    {
        return pList->currentCount;
    }

    return 0;
}

void display(LinkedList *pList)
{
    int i = 0;
    for (i = 0; i < pList->currentCount; i++)
    {
        printf("[%d], %d\n", i, getLinkedListData(pList, i));
    }
}

int main(int argc, char *argv[])
{
    LinkedList *pList = NULL;
    int value = 0;

    pList = createLinkedList();
    addLinkedListData(pList, 0, 10);
    addLinkedListData(pList, 0, 20);
    addLinkedListData(pList, 0, 30);

    value = getLinkedListData(pList, 1);
    printf("Position: %d, Value: %d\n", 1, value);
    display(pList);

    removeLinkedListData(pList, 0);

    display(pList);
    deleteLinkedList(pList);
    return 0;
}