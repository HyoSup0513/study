#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CircularListNodeType
{
    int data;
    struct CircularListNodeType *link;
} CircularListNode;

typedef struct CircularListNode
{
    int currentCount;
    CircularListNode headerNode;
} CircularList;

CircularList *create()
{
    CircularList *clist = (CircularList *)malloc(sizeof(CircularList));
    memset(clist, 0, sizeof(CircularList));
    return clist;
}

int getData(CircularList *clist, int position)
{
    CircularListNode *curNode = &(clist->headerNode);
    for (int i = 0; i <= position; i++)
    {
        curNode = curNode->link;
    }
    return curNode->data;
}

void addNode(CircularList *clist, int position, int data)
{
    CircularListNode *newNode = NULL;
    CircularListNode *prevNode = NULL;

    newNode = (CircularListNode *)malloc(sizeof(CircularListNode));
    newNode->data = data;

    prevNode = &(clist->headerNode);
    for (int i = 0; i < position; i++)
    {
        prevNode = prevNode->link;
    }

    newNode->link = prevNode->link;
    prevNode->link = newNode;

    if (newNode->link == NULL)
    {
        newNode->link = newNode;
    }
    clist->currentCount++;
}

void removeNode(CircularList *clist, int position)
{
    CircularListNode *delNode = NULL;
    CircularListNode *prevNode = NULL;

    prevNode = &(clist->headerNode);
    for (int i = 0; i < position; i++)
    {
        prevNode = prevNode->link;
    }

    delNode = prevNode->link;
    prevNode->link = delNode->link;
    free(delNode);
    clist->currentCount--;
}

void deleteList(CircularList *clist)
{
    CircularListNode *delNode = NULL;
    CircularListNode *prevNode = NULL;
    while (prevNode != NULL)
    {
        delNode = prevNode;
        prevNode = prevNode->link;

        free(delNode);
    }
    free(clist);
}

int getLength(CircularList *clist)
{
    if (clist != NULL)
    {
        return clist->currentCount;
    }
    return 0;
}

void display(CircularList *pList)
{
    for (int i = 0; i < pList->currentCount; i++)
    {
        printf("[%d], %d\n", i, getData(pList, i));
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    CircularList *clist = NULL;

    clist = create();
    addNode(clist, 0, 10);
    addNode(clist, 1, 20);
    addNode(clist, 2, 30);
    addNode(clist, 0, 40);
    addNode(clist, 3, 50);
    display(clist);

    removeNode(clist, 30);
    display(clist);

    deleteList(clist);
}