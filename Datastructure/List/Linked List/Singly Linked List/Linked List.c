#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedListNodeType
{
    int data;
    struct LinkedListNodeType *link;
} LinkedListNode;

typedef struct LinkedListType
{
    int currentCount;
    LinkedListNode headerNode;
} LinkedList;

LinkedList *createLinkedList()
{
    LinkedList *llist = (LinkedList *)malloc(sizeof(LinkedList));
    if (llist != NULL)
    {
        memset(llist, 0, sizeof(LinkedList)); // memory initialization to 0
    }
    return llist;
}

int getLinkedListData(LinkedList *llist, int position)
{
    int i = 0;
    LinkedListNode *curNode = &(llist->headerNode);
    for (i = 0; i <= position; i++)
    {
        curNode = curNode->link;
    }

    return curNode->data;
}

void addLinkedListData(LinkedList *llist, int position, int data)
{
    int i = 0;
    LinkedListNode *pNewNode = NULL;
    LinkedListNode *pPrevNode = NULL;

    if (llist != NULL)
    {
        if (position >= 0 && position <= llist->currentCount)
        {
            pNewNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
            if (pNewNode != NULL)
            {
                pNewNode->data = data;

                pPrevNode = &(llist->headerNode);
                for (i = 0; i < position; i++)
                {
                    pPrevNode = pPrevNode->link;
                }

                pNewNode->link = pPrevNode->link;
                pPrevNode->link = pNewNode;
                llist->currentCount++;
            }
        }
    }
}

int removeLinkedListData(LinkedList *llist, int position)
{
    int i = 0;
    LinkedListNode *pDelNode = NULL;
    LinkedListNode *pPrevNode = NULL;

    pPrevNode = &(llist->headerNode);
    for (i = 0; i < position; i++)
    {
        pPrevNode = pPrevNode->link;
    }

    pDelNode = pPrevNode->link;
    pPrevNode->link = pDelNode->link;
    free(pDelNode);
    llist->currentCount--;

    return 0;
}

void deleteLinkedList(LinkedList *llist)
{
    LinkedListNode *pDelNode = NULL;
    LinkedListNode *pPrevNode = llist->headerNode.link;
    while (pPrevNode != NULL)
    {
        pDelNode = pPrevNode;
        pPrevNode = pPrevNode->link;

        free(pDelNode);
    }

    free(llist);
}

// Get length using member variable
int getLinkedListLength(LinkedList *llist)
{
    if (llist != NULL)
    {
        return llist->currentCount;
    }

    return 0;
}

// Gen length without addming member variable
int getLinkedListLength2(LinkedList *llist)
{
    int ret = 0;
    if (NULL != llist)
    {
        LinkedListNode *pPreNode = llist->headerNode.link;
        while (pPreNode != NULL)
        {
            ret++;
            pPreNode = pPreNode->link;
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

void iterateLL(LinkedList *llist)
{
    int count = 0;
    LinkedListNode *pNode = NULL;

    pNode = llist->headerNode.link;
    while (pNode != NULL)
    {
        printf("[%d] %d\n", count, pNode->data);
        count++;
        pNode = pNode->link;
    }
    printf("Number of nodes: %d\n\n", count);
}

void concatenation(LinkedList *pListA, LinkedList *pListB)
{
    LinkedListNode *pNodeA = NULL;
    if (pListA != NULL && pListB != NULL)
    {
        pNodeA = pListA->headerNode.link;

        if (pNodeA != NULL)
        {
            while (pNodeA != NULL && pNodeA->link != NULL)
            {
                pNodeA = pNodeA->link;
            }
            pNodeA->link = pListB->headerNode.link;
        }
        else
        {
            pListA->headerNode.link = pListB->headerNode.link;
        }
        pListB->headerNode.link = NULL;
    }
}

void reverse(LinkedList *llist)
{
    LinkedListNode *pNode = NULL, *pCurrentNode = NULL, *pPrevNode = NULL;

    if (llist != NULL)
    {
        pNode = llist->headerNode.link;
        while (pNode != NULL)
        {
            pPrevNode = pCurrentNode;
            pCurrentNode = pNode;
            pNode = pNode->link;
            pCurrentNode->link = pPrevNode;
        }

        llist->headerNode.link = pCurrentNode;
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