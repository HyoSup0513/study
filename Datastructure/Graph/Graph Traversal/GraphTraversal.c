#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayGraph.c"
#include "LinkedQueue.c"
#include "LinkedStack.c"

// Recursive DFS
void RecursiveDFS(ArrayGraph *pGraph, int startNodeID, int *pVisit)
{
    pVisit[startNodeID] = 1;
    printf("Node-[%d] Visit\n", startNodeID);

    for (int i = 0; i < pGraph->nodeCount; i++)
    {
        if (i != startNodeID)
        {
            if (getEdgeAG(pGraph, startNodeID, i) != 0)
            {
                if (pVisit[i] == 0)
                {
                    RecursiveDFS(pGraph, i, pVisit);
                }
            }
        }
    }
}

// DFS Stack
void DFS(ArrayGraph *pGraph, int startNodeID)
{
    int i = 0;
    int nodeID = 0;
    LinkedStack *pStack = NULL;
    LinkedStackNode *pStackNode = NULL;
    int *pVisited = NULL;

    if (pGraph == NULL)
    {
        return;
    }

    pStack = createLinkedStack();
    if (pStack == NULL)
    {
        return;
    }

    pVisited = (int *)malloc(sizeof(int) * pGraph->nodeCount);
    if (pVisited == NULL)
    {
        printf("Error, malloc() in DFS() Stack\n");
        return;
    }

    for (i = 0; i < pGraph->nodeCount; i++)
    {
        pVisited[i] = 0;
    }

    pushLS(pStack, startNodeID);
    pVisited[startNodeID] = 1;

    while (isLinkedStackEmpty(pStack) == 0)
    {
        pStackNode = popLS(pStack);
        if (pStackNode != NULL)
        {
            nodeID = pStackNode->data;
            printf("[%d]-Visit\n", nodeID);

            for (i = pGraph->nodeCount - 1; i >= 0; i--)
            {
                if (i != nodeID)
                {
                    if (getEdgeAG(pGraph, nodeID, i) != 0)
                    {
                        if (pVisited[i] == 0)
                        {
                            pVisited[i] = 1;
                            pushLS(pStack, i);
                        }
                    }
                }
            }

            free(pStackNode);
        }
    }

    free(pVisited);
    deleteLinkedStack(pStack);
}

// BFS Queue
void BFS(ArrayGraph *pGraph, int startNodeID)
{
    int i = 0;
    int nodeID = 0;
    LinkedQueue *pQueue = NULL;
    LinkedQueueNode *pQueueNode = NULL;
    int *pVisit = NULL;

    if (pGraph == NULL)
    {
        return;
    }

    pQueue = createLinkedQueue();
    pVisit = (int *)malloc(sizeof(int) * pGraph->nodeCount);

    if (pQueue == NULL || pVisit == NULL)
    {
        return;
    }

    memset(pVisit, 0, sizeof(int) * pGraph->nodeCount);
    pVisit[startNodeID] = 1;
    enqueueLQ(pQueue, startNodeID);

    while (isLinkedQueueEmpty(pQueue) == 0)
    {
        pQueueNode = dequeueLQ(pQueue);
        if (pQueueNode != NULL)
        {
            nodeID = pQueueNode->data;
            printf("Node-[%d] Visit\n", nodeID);

            for (i = 0; i < pGraph->nodeCount; i++)
            {
                if (i != nodeID)
                {
                    if (0 != getEdgeAG(pGraph, nodeID, i))
                    {
                        if (0 == pVisit[i])
                        {
                            pVisit[i] = 1;
                            enqueueLQ(pQueue, i);
                        }
                    }
                }
            }
            free(pQueueNode);
        }
    }

    deleteLinkedQueue(pQueue);
    free(pVisit);
}

int main(int argc, char *argv[])
{
    int nodeCount = 9;
    ArrayGraph *pG1 = createArrayGraph(ARRAY_GRAPH_TYPE_UNDIRECT, nodeCount);
    int *pVisit = (int *)malloc(sizeof(int) * nodeCount);

    if (pG1 != NULL && pVisit != NULL)
    {
        addEdgeAG(pG1, 0, 1);
        addEdgeAG(pG1, 1, 2);
        addEdgeAG(pG1, 1, 3);
        addEdgeAG(pG1, 2, 4);
        addEdgeAG(pG1, 2, 3);
        addEdgeAG(pG1, 3, 4);
        addEdgeAG(pG1, 3, 5);
        addEdgeAG(pG1, 5, 6);
        addEdgeAG(pG1, 5, 7);
        addEdgeAG(pG1, 6, 8);

        memset(pVisit, 0, sizeof(int) * nodeCount);

        // Recursive DFS 0-1-2-4-3-5-6-8-7
        printf("G1: Recursive DFS\n");
        RecursiveDFS(pG1, 0, pVisit);
        printf("\n");

        // DFS Stack 0-1-2-4-3-5-6-8-7
        printf("G1: DFS Stack\n");
        DFS(pG1, 0);
        printf("\n");

        // BFS Queue 0-1-2-3-4-5-6-7-8
        printf("G1: BFS Queue\n");
        BFS(pG1, 0);

        deleteGraphAG(pG1);
        free(pVisit);
    }

    return 0;
}
