#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DLLNodeType
{
    int data;
    struct DLLNodeType *next;
    struct DLLNodeTpye *prev;
} DLLNode;

typedef struct DLListType
{
    int currentCount;
    DLLNode headerNode;
} DLList;

DLList *create()
{
    DLList *dlist = (DLList *)malloc(sizeof(DLList));
    if (dlist != NULL)
    {
        memset(dlist, 0, sizeof(dlist));
        dlist->headerNode.next = &(dlist->headerNode);
        dlist->headerNode.prev = &(dlist->headerNode);
    }
    return dlist;
}

int getData(DLList *dlist, int position)
{
    DLLNode *curNode = &(dlist->headerNode);
    for (int i = 0; i <= position; i++)
    {
        curNode = curNode->next;
    }
    return curNode->data;
}

void addNode(DLList *dlist, int position, int data)
{
    DLLNode *newNode = NULL;
    DLLNode *prevNode = NULL;
    newNode = (DLLNode *)malloc(sizeof(DLLNode));
    if (newNode != NULL)
    {
        memset(newNode, 0, sizeof(DLLNode));
        newNode->data = data;
        prevNode = &(dlist->headerNode);
        for (int i = 0; i < position; i++)
        {
            prevNode = prevNode->next;
        }

        newNode->next = prevNode->next;
        newNode->prev = prevNode;

        prevNode->next = newNode;
        newNode->next->prev = newNode;
        dlist->currentCount++;
    }
}

void removeNode(DLList *dlist, int position)
{
    DLLNode *delNode = NULL;
    DLLNode *prevNode = NULL;
    prevNode = &(dlist->headerNode);
    for (int i = 0; i < position; i++)
    {
        prevNode = prevNode->next;
    }

    delNode = prevNode->next;
    prevNode->next = delNode->next;
    delNode->next->prev = prevNode;
    free(delNode);
    dlist->currentCount--;
}

int getLength(DLList *dlist)
{
    if (dlist != NULL)
    {
        return dlist->currentCount;
    }
    return 0;
}

void display(DLList *dlist)
{
    for (int i = 0; i < dlist->currentCount; i++)
    {
        printf("[%d], %d\n", i, getData(dlist, i));
    }
    printf("\n");
}

void deleteList(DLList *dlist)
{
    if (dlist != NULL)
    {
        while (dlist->currentCount > 0)
        {
            removeNode(dlist, 0);
        }
        free(dlist);
    }
}

int main(int argc, char *argv[])
{
    DLList *dlist = NULL;

    dlist = create();
    addNode(dlist, 0, 10);
    addNode(dlist, 1, 20);
    addNode(dlist, 2, 30);
    addNode(dlist, 0, 40);
    addNode(dlist, 3, 50);
    printf("Doubly Linked List: \n");
    display(dlist);

    removeNode(dlist, 30);
    printf("Doubly Linked List: \n");
    display(dlist);

    deleteList(dlist);
}