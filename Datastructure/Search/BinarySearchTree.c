#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// BST Node
typedef struct BSTNodeType
{
    int key;
    char value;

    struct BSTNodeType *leftchild;
    struct BSTNodeType *rightchild;
} Node;

// BST Tree
typedef struct BSTType
{
    Node *root;
} BST;

// Create BST
BST *createBST()
{
    BST *pReturn = NULL;
    pReturn = (BST *)malloc(sizeof(BST));
    if (pReturn != NULL)
    {
        pReturn->root = NULL;
    }
    else
    {
        printf("Error, memory allocation, createBST()\n");
    }

    return pReturn;
}

Node *searchBST(BST *pBST, int key)
{
    Node *pReturn = NULL;

    // Check BST is NULL
    if (pBST == NULL)
    {
        return NULL;
    }
    // Start node is root node.
    pReturn = pBST->root;

    // If there is no remaining node, exit the loop.
    while (pReturn != NULL)
    {
        if (key == pReturn->key)
        {
            break;
        }
        else if (key < pReturn->key)
        {
            pReturn = pReturn->leftchild;
        }
        else
        {
            pReturn = pReturn->rightchild;
        }
    }

    return pReturn;
}

int getParentNode(Node *pCurrentNode, int key, Node **ppResult)
{
    int ret = 1;
    Node *pParentNode = NULL;

    while (pCurrentNode != NULL)
    {
        if (key == pCurrentNode->key)
        {
            printf("Error, duplicate Key-[%d],getParentNode()\n", key);
            ret = 0;
            return ret;
        }
        else if (key < pCurrentNode->key)
        {
            pParentNode = pCurrentNode;
            pCurrentNode = pCurrentNode->leftchild;
        }
        else
        {
            pParentNode = pCurrentNode;
            pCurrentNode = pCurrentNode->rightchild;
        }
    }
    if (1 == ret)
    {
        *ppResult = pParentNode;
    }

    return ret;
}

Node *createNewNode(int key, char value)
{
    Node *pNewNode = NULL;

    pNewNode = (Node *)malloc(sizeof(Node));
    if (pNewNode != NULL)
    {
        pNewNode->key = key;
        pNewNode->value = value;
        pNewNode->leftchild = NULL;
        pNewNode->rightchild = NULL;
    }

    return pNewNode;
}

void insert(BST *pBST, Node *pParentNode, Node *pNewNode)
{
    if (pParentNode == NULL)
    {
        pBST->root = pNewNode;
    }
    else
    {
        if (pNewNode->key < pParentNode->key)
        {
            pParentNode->leftchild = pNewNode;
        }
        else
        {
            pParentNode->rightchild = pNewNode;
        }
    }
}

int insertData(BST *pBST, int key, char value)
{
    int ret = 1;
    Node *pParentNode = NULL;
    Node *pNewNode = NULL;

    if (pBST == NULL)
    {
        ret = 0;
        return ret;
    }

    ret = getParentNode(pBST->root, key, &pParentNode);
    if (0 == ret)
    {
        return ret;
    }

    pNewNode = createNewNode(key, value);
    if (NULL == pNewNode)
    {
        return 0;
    }

    insert(pBST, pParentNode, pNewNode);

    return ret;
}

Node *searchWithParentNodeBST(BST *pBST, int key, Node **ppParentNode)
{
    Node *pReturn = NULL;
    Node *pParentNode = NULL;

    if (pBST == NULL)
    {
        return NULL;
    }
    pReturn = pBST->root;
    while (pReturn != NULL)
    {
        if (key == pReturn->key)
        {
            break;
        }
        pParentNode = pReturn;

        if (key < pReturn->key)
        {
            pReturn = pReturn->leftchild;
        }
        else
        {
            pReturn = pReturn->rightchild;
        }
    }

    if (NULL != ppParentNode)
    {
        *ppParentNode = pParentNode;
    }

    return pReturn;
}

void deleteNodeNoChild(BST *pBST, Node *pParentNode, Node *pDelNode)
{
    if (pParentNode != NULL)
    {
        if (pParentNode->leftchild == pDelNode)
        {
            pParentNode->rightchild = NULL;
        }
        else
        {
            pParentNode->rightchild = NULL;
        }
    }
    else
    {
        pBST->root = NULL;
    }
}

void deleteNodeOneChild(BST *pBST, Node *pParentNode, Node *pDelNode)
{
    Node *pChildNode = NULL;

    if (pDelNode->leftchild != NULL)
    {
        pChildNode = pDelNode->leftchild;
    }
    else
    {
        pChildNode = pDelNode->rightchild;
    }

    if (pParentNode != NULL)
    {
        if (pParentNode->rightchild == pDelNode)
        {
            pParentNode->leftchild = pChildNode;
        }
        else
        {
            pParentNode->rightchild = pChildNode;
        }
    }
    else
    {
        pBST->root = pChildNode;
    }
}

void deleteNodeTwoChildren(BST *pBST, Node *pParentNode, Node *pDelNode)
{
    Node *pPredecessor = NULL, *pSuccessor = NULL;

    pPredecessor = pDelNode;
    pSuccessor = pDelNode->leftchild;

    while (pSuccessor->rightchild != NULL)
    {
        pPredecessor = pSuccessor;
        pSuccessor = pSuccessor->rightchild;
    }

    pPredecessor->rightchild = pSuccessor->leftchild;
    pSuccessor->leftchild = pDelNode->leftchild;
    pSuccessor->rightchild = pDelNode->rightchild;

    if (pParentNode != NULL)
    {
        if (pParentNode->leftchild == pDelNode)
        {
            pParentNode->leftchild = pSuccessor;
        }
        else
        {
            pParentNode->rightchild = pSuccessor;
        }
    }
    else
    {
        pBST->root = pSuccessor;
    }
}

int deleteDataBST(BST *pBST, int key)
{
    int ret = 1;
    Node *pDelNode = NULL, *pParentNode = NULL;

    if (pBST == NULL)
    {
        ret = 0;
        return ret;
    }
    pDelNode = searchWithParentNodeBST(pBST, key, &pParentNode);
    if (pDelNode == NULL)
    {
        printf("Error, Key does not exist-[%d],deleteDataBST()\n", key);
        ret = 0;
        return ret;
    }

    if (pDelNode->leftchild == NULL && pDelNode->rightchild == NULL)
    {
        deleteNodeNoChild(pBST, pParentNode, pDelNode);
    }
    else if (pDelNode->leftchild != NULL && pDelNode->rightchild != NULL)
    {
        deleteNodeTwoChildren(pBST, pParentNode, pDelNode);
    }
    else
    {
        deleteNodeOneChild(pBST, pParentNode, pDelNode);
    }

    free(pDelNode);
    return ret;
}

void deleteBSTInternal(Node *pTreeNode)
{
    if (pTreeNode != NULL)
    {
        deleteBSTInternal(pTreeNode->leftchild);
        deleteBSTInternal(pTreeNode->rightchild);
        free(pTreeNode);
    }
}

void deleteBST(BST *pBST)
{
    if (pBST != NULL)
    {
        deleteBSTInternal(pBST->root);
        free(pBST);
    }
}

void display(Node *pTreeNode, int level, char type)
{
    int i = 0;

    if (pTreeNode != NULL)
    {
        for (i = 0; i < level; i++)
        {
            printf("    ");
        }

        printf("-(%c)-key: %i,value-%c\n", type,
               pTreeNode->key, pTreeNode->value);

        display(pTreeNode->leftchild, level + 1, 'L');
        display(pTreeNode->rightchild, level + 1, 'R');
    }
}

int main(int argc, char *argv[])
{
    BST *pTree = NULL;
    Node *pSearchNode = NULL;
    int key = 0;

    pTree = createBST();
    if (pTree != NULL)
    {
        insertData(pTree, 70, 'A');
        insertData(pTree, 40, 'B');
        insertData(pTree, 90, 'C');
        insertData(pTree, 20, 'D');
        insertData(pTree, 60, 'E');
        insertData(pTree, 80, 'F');
        insertData(pTree, 100, 'G');
        insertData(pTree, 10, 'H');
        insertData(pTree, 30, 'I');
        insertData(pTree, 50, 'J');
        display(pTree->root, 0, '-');

        key = 30;
        pSearchNode = searchBST(pTree, key);
        if (pSearchNode != NULL)
        {
            printf("Search: Key-[%d], Data-[%c] found\n", key, pSearchNode->value);
        }
        else
        {
            printf("Search: Key-[%d], Data not found\n", key);
        }

        key = 70;
        printf("Delete data: Key-[%d]\n", key);
        deleteDataBST(pTree, key);
        display(pTree->root, 0, '-');

        key = 35;
        pSearchNode = searchBST(pTree, key);
        if (pSearchNode != NULL)
        {
            printf("Search: Key-[%d], Data-[%c] found\n", key, pSearchNode->value);
        }
        else
        {
            printf("Search: Key-[%d], Data not found\n", key);
        }

        deleteBST(pTree);
    }

    return 0;
}
