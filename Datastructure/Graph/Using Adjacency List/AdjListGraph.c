#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.c"

typedef struct AdjListGraphType
{
    int nodeCount;          // Number of nodes
    LinkedList **ppAdjEdge; // LinkedList array to store edge
} AdjListGraph;

AdjListGraph *createAdjListGraph(int nodeCount)
{
    int i = 0;
    AdjListGraph *pReturn = NULL;

    if (nodeCount > 0)
    {
        pReturn = (AdjListGraph *)malloc(sizeof(AdjListGraph));
        if (pReturn == NULL)
        {
            printf("Error, memory allocation(1), in createAdjListGraph()\n");
            return NULL;
        }
        pReturn->nodeCount = nodeCount;
    }
    else
    {
        printf("Error, Maximum number of nodes must be greater than 0\n");
        return NULL;
    }

    pReturn->ppAdjEdge = (LinkedList **)malloc(sizeof(LinkedList *) * nodeCount);
    if (pReturn->ppAdjEdge == NULL)
    {
        printf("Error, memory allocation(3), in createAdjListGraph()\n");
        if (pReturn != NULL)
            free(pReturn);
        return NULL;
    }
    for (i = 0; i < nodeCount; i++)
    {
        pReturn->ppAdjEdge[i] = createLinkedList();
        if (pReturn->ppAdjEdge[i] == NULL)
        {
            printf("Error, memory allocation(4), in createAdjListGraph()\n");
            if (pReturn->ppAdjEdge != NULL)
                free(pReturn->ppAdjEdge);
            if (pReturn != NULL)
                free(pReturn);
            return NULL;
        }
    }

    return pReturn;
}

int checkVertexValid(AdjListGraph *pGraph, int node)
{
    if (pGraph != NULL && node >= 0 && node < pGraph->nodeCount)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int addEdgeDLG(AdjListGraph *pGraph, int fromNode, int toNode)
{
    int ret = 0;

    if (pGraph != NULL && checkVertexValid(pGraph, fromNode) && checkVertexValid(pGraph, toNode))
    {
        addLinkedListData(pGraph->ppAdjEdge[fromNode], 0, toNode);
    }
    else
    {
        ret = -1;
    }

    return ret;
}

int removeEdgeDLG(AdjListGraph *pGraph, int fromNode, int toNode)
{
    int ret = -1;
    LinkedList *pList = NULL;
    int i = 0, count = 0;

    if (pGraph != NULL && checkVertexValid(pGraph, fromNode) && checkVertexValid(pGraph, toNode))
    {
        pList = pGraph->ppAdjEdge[fromNode];
        count = getLinkedListLength(pList);
        for (i = 0; i < count; i++)
        {
            if (getLinkedListData(pList, i) == toNode)
            {
                removeLinkedListData(pList, i);
                ret = 0;
                break;
            }
        }
    }
    else
    {
        // If there is no corresponding edge (Deletion failure)
        ret = -1;
    }

    return ret;
}

int getEdgeDLG(AdjListGraph *pGraph, int fromNode, int toNode)
{
    int ret = 0;
    LinkedList *pList = NULL;
    int i = 0, count = 0;

    if (pGraph != NULL && checkVertexValid(pGraph, fromNode) && checkVertexValid(pGraph, toNode))
    {
        pList = pGraph->ppAdjEdge[fromNode];
        count = getLinkedListLength(pList);
        for (i = 0; i < count; i++)
        {
            if (getLinkedListData(pList, i) == toNode)
            {
                ret = 1;
                break;
            }
        }
    }

    return ret;
}

void displayGraphDLG(AdjListGraph *pGraph)
{
    int i = 0, j = 0, count = 0;

    if (pGraph != NULL)
    {
        count = pGraph->nodeCount;
        for (i = 0; i < count; i++)
        {
            for (j = 0; j < count; j++)
            {
                if (getEdgeDLG(pGraph, i, j))
                {
                    printf("1 ");
                }
                else
                {
                    printf("0 ");
                }
            }
            printf("\n");
        }
    }
}

void deleteGraphDLG(AdjListGraph *pGraph)
{
    int i = 0;

    if (pGraph != NULL)
    {
        for (i = 0; i < pGraph->nodeCount; i++)
        {
            deleteLinkedList(pGraph->ppAdjEdge[i]);
        }
        if (pGraph->ppAdjEdge != NULL)
            free(pGraph->ppAdjEdge);
        free(pGraph);
    }
}

int main(int argc, char *argv[])
{
    int nodeCount = 4;
    AdjListGraph *Graph1 = createAdjListGraph(nodeCount);
    if (Graph1 != NULL)
    {
        addEdgeDLG(Graph1, 0, 1);
        addEdgeDLG(Graph1, 0, 2);
        addEdgeDLG(Graph1, 1, 3);
        addEdgeDLG(Graph1, 2, 3);
        addEdgeDLG(Graph1, 3, 1);
        addEdgeDLG(Graph1, 3, 2);

        printf("Graph1: Directed Graph\n");
        displayGraphDLG(Graph1);

        deleteGraphDLG(Graph1);
    }

    return 0;
}