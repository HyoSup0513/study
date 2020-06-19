#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AdjGraphType
{
    int nodeCount; // Number of nodes
    int **ppEdge;  // two dimensional array to store edge
} AdjGraph;

AdjGraph *createAdjGraph(int nodeCount)
{
    int i = 0;
    AdjGraph *pReturn = NULL;

    pReturn = (AdjGraph *)malloc(sizeof(AdjGraph));
    if (pReturn == NULL)
    {
        return NULL;
    }

    pReturn->nodeCount = nodeCount;
    pReturn->ppEdge = (int **)malloc(sizeof(int *) * nodeCount);
    if (pReturn->ppEdge == NULL)
    {
        return NULL;
    }

    for (i = 0; i < nodeCount; i++)
    {
        pReturn->ppEdge[i] = (int *)malloc(sizeof(int) * nodeCount);
        if (pReturn->ppEdge[i] == NULL)
        {
            return NULL;
        }

        memset(pReturn->ppEdge[i], 0, sizeof(int) * nodeCount);
    }
    return pReturn;
}

int checkVertexValid(AdjGraph *pGraph, int node)
{
    if (pGraph != NULL && node < pGraph->nodeCount && node >= 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int addEdge(AdjGraph *pGraph, int fromNode, int toNode)
{
    int ret = 0;

    if (pGraph != NULL && checkVertexValid(pGraph, fromNode) && checkVertexValid(pGraph, toNode))
    {
        pGraph->ppEdge[fromNode][toNode] = 1;
    }
    else
    {
        ret = -1;
    }
    return ret;
}

int removeEdge(AdjGraph *pGraph, int fromNode, int toNode)
{
    int ret = 0;

    if (pGraph != NULL && checkVertexValid(pGraph, fromNode) && checkVertexValid(pGraph, toNode))
    {
        pGraph->ppEdge[fromNode][toNode] = 0;
    }
    else
    {
        ret = -1;
    }
    return ret;
}

int getEdge(AdjGraph *pGraph, int fromNode, int toNode)
{
    int ret = 0;
    if (pGraph != NULL && checkVertexValid(pGraph, fromNode) && checkVertexValid(pGraph, toNode))
    {
        ret = pGraph->ppEdge[fromNode][toNode];
    }

    return ret;
}

void display(AdjGraph *pGraph)
{
    int i = 0, j = 0;
    int count = 0;

    if (pGraph != NULL)
    {
        count = pGraph->nodeCount;
        for (i = 0; i < count; i++)
        {
            for (j = 0; j < count; j++)
            {
                printf("%d", getEdge(pGraph, i, j));
            }
            printf("\n");
        }
    }
}

void deleteGraph(AdjGraph *pGraph)
{
    int i = 0;

    if (pGraph != NULL)
    {
        for (i = 0; i < pGraph->nodeCount; i++)
        {
            free(pGraph->ppEdge[i]);
        }
        free(pGraph->ppEdge);
        free(pGraph);
    }
}
int main(int argc, char *argv[])
{
    int nodeCount = 4;
    AdjGraph *graph1 = createAdjGraph(nodeCount);
    if (graph1 != NULL)
    {
        addEdge(graph1, 0, 1);
        addEdge(graph1, 0, 2);
        addEdge(graph1, 1, 3);
        addEdge(graph1, 2, 3);
        addEdge(graph1, 3, 1);

        printf("Graph1: Directed Graph\n");
        display(graph1);
        deleteGraph(graph1);
    }

    return 0;
}