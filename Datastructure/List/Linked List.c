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
    if (pReturn != NULL)
    {
        memset(pReturn, 0, sizeof(LinkedList)); // memory initialization to 0
    }
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
    int ret = 0;
    int i = 0;
    LinkedListNode *pNewNode = NULL;
    LinkedListNode *pPrevNode = NULL;

    if (pList != NULL)
    {
        if (position >= 0 && position <= pList->currentCount)
        {
            pNewNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
            if (pNewNode != NULL)
            {
                pNewNode->data = data;

                pPrevNode = &(pList->headerNode);
                for (i = 0; i < position; i++)
                {
                    pPrevNode = pPrevNode->pLink;
                }

                pNewNode->pLink = pPrevNode->pLink;
                pPrevNode->pLink = pNewNode;
                pList->currentCount++;
            }
            else
            {
                ret = 1;
            }
        }
        else
        {
            ret = 1;
        }
    }
    else
    {
        ret = 1;
    }
    return ret;
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

// Get length using member variable
int getLinkedListLength(LinkedList *pList)
{
    if (pList != NULL)
    {
        return pList->currentCount;
    }

    return 0;
}

// Gen length without addming member variable
int getLinkedListLength2(LinkedList *pList)
{
    int ret = 0;
    if (NULL != pList)
    {
        LinkedListNode *pPreNode = pList->headerNode.pLink;
        while (pPreNode != NULL)
        {
            ret++;
            pPreNode = pPreNode->pLink;
        }
    }
    return ret;
}

void display(LinkedList *pList)
{
    int i = 0;
    for (i = 0; i < pList->currentCount; i++)
    {
        printf("[%d], %d\n", i, getLinkedListData(pList, i));
    }
}

void iterateLL(LinkedList *pList)
{
    int count = 0;
    LinkedListNode *pNode = NULL;

    pNode = pList->headerNode.pLink;
    while (pNode != NULL)
    {
        printf("[%d] %d\n", count, pNode->data);
        count++;
        pNode = pNode->pLink;
    }
    printf("Number of nodes: %d\n\n", count);
}

void concatenation(LinkedList *pListA, LinkedList *pListB)
{
    LinkedListNode *pNodeA = NULL;
    if (pListA != NULL && pListB != NULL)
    {
        pNodeA = pListA->headerNode.pLink;

        if (pNodeA != NULL)
        {
            while (pNodeA != NULL && pNodeA->pLink != NULL)
            {
                pNodeA = pNodeA->pLink;
            }
            pNodeA->pLink = pListB->headerNode.pLink;
        }
        else
        {
            pListA->headerNode.pLink = pListB->headerNode.pLink;
        }
        pListB->headerNode.pLink = NULL;
    }
}

void reverse(LinkedList *pList)
{
    LinkedListNode *pNode = NULL, *pCurrentNode = NULL, *pPrevNode = NULL;

    if (pList != NULL)
    {
        pNode = pList->headerNode.pLink;
        while (pNode != NULL)
        {
            pPrevNode = pCurrentNode;
            pCurrentNode = pNode;
            pNode = pNode->pLink;
            pCurrentNode->pLink = pPrevNode;
        }

        pList->headerNode.pLink = pCurrentNode;
    }
}

int main(int argc, char *argv[])
{
    LinkedList *pListA = NULL;
    LinkedList *pListB = NULL;

    pListA = createLinkedList();
    pListB = createLinkedList();
    addLinkedListData(pListA, 0, 10);
    addLinkedListData(pListA, 1, 20);
    addLinkedListData(pListA, 2, 30);
    addLinkedListData(pListB, 0, 40);
    addLinkedListData(pListB, 1, 50);
    addLinkedListData(pListB, 2, 60);

    printf("Before concatenation\n");
    printf("List A\n");
    iterateLL(pListA);
    printf("List B\n");
    iterateLL(pListB);

    concatenation(pListA, pListB);
    printf("After concatenation\n");
    printf("List A\n");
    iterateLL(pListA);
    printf("List B\n");
    iterateLL(pListB);

    reverse(pListA);
    printf("Reversed List A\n");
    iterateLL(pListA);

    deleteLinkedList(pListA);
    deleteLinkedList(pListB);
    return 0;
}