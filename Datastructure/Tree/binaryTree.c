#include <stdio.h>
#include <stdlib.h>

typedef struct BinTreeNodeType
{
    char data;
    struct BinTreeNodeType *leftChild;
    struct BinTreeNodeType *rightChild;
} BinTreeNode;

typedef struct BinTreeType
{
    struct BinTreeNodeType *root;
} BinTree;

BinTreeNode *createNewNode(char data)
{
    BinTreeNode *pReturn = (BinTreeNode *)malloc(sizeof(BinTreeNode));
    if (pReturn != NULL)
    {
        pReturn->data = data;
        pReturn->leftChild = NULL;
        pReturn->rightChild = NULL;
    }

    return pReturn;
}

BinTree *createBinTree(char rootNode)
{
    BinTree *pReturn = NULL;

    pReturn = (BinTree *)malloc(sizeof(BinTree));
    if (pReturn != NULL)
    {
        pReturn->root = createNewNode(rootNode);
        if (pReturn->root == NULL)
        {
            free(pReturn);
            pReturn = NULL;
            printf("Error, memory allocation(1), createBinTree()\n");
        }
    }

    else
    {
        printf("Error, memory allocation(2), createBinTree()\n");
    }
    return pReturn;
}

BinTreeNode *addLeftChild(BinTreeNode *parent, char data)
{
    BinTreeNode *pReturn = NULL;
    if (parent != NULL)
    {
        if (parent->leftChild == NULL)
        {
            parent->leftChild = createNewNode(data);
            pReturn = parent->leftChild;
        }
        else
        {
            printf("Error, already exists, addLeftChild()\n");
        }
    }
    return pReturn;
}

BinTreeNode *addRightChild(BinTreeNode *parent, char data)
{
    BinTreeNode *pReturn = NULL;
    if (parent != NULL)
    {
        if (parent->rightChild == NULL)
        {
            parent->rightChild = createNewNode(data);
            pReturn = parent->rightChild;
        }
        else
        {
            printf("Error, already exists, addRightChild()\n");
        }
    }
    return pReturn;
}

BinTreeNode *getRoot(BinTree *BinTree)
{
    BinTreeNode *pReturn = NULL;

    if (BinTree != NULL)
    {
        pReturn = BinTree->root;
    }

    return pReturn;
}

void deleteBinTreeNode(BinTreeNode *pNode)
{
    if (pNode != NULL)
    {
        deleteBinTreeNode(pNode->leftChild);
        deleteBinTreeNode(pNode->rightChild);
        free(pNode);
    }
}

void deleteBinTree(BinTree *BinTree)
{
    if (BinTree != NULL)
    {
        deleteBinTreeNode(BinTree->root);
        free(BinTree);
    }
}

void preorderRecursiveNode(BinTreeNode *pNode)
{
    if (pNode != NULL)
    {
        printf("%c", pNode->data);
        preorderRecursiveNode(pNode->leftChild);
        preorderRecursiveNode(pNode->rightChild);
    }
}

void preorderRecursive(BinTree *BinTree)
{
    if (BinTree != NULL)
    {
        preorderRecursiveNode(BinTree->root);
        printf("\n");
    }
}

void inorderRecursiveNode(BinTreeNode *pNode)
{
    if (pNode != NULL)
    {
        inorderRecursiveNode(pNode->leftChild);
        printf("%c", pNode->data);
        inorderRecursiveNode(pNode->rightChild);
    }
}

void inorderRecursive(BinTree *BinTree)
{
    if (BinTree != NULL)
    {
        inorderRecursiveNode(BinTree->root);
        printf("\n");
    }
}

void postorderRecursiveNode(BinTreeNode *pNode)
{
    if (pNode != NULL)
    {
        postorderRecursiveNode(pNode->leftChild);
        postorderRecursiveNode(pNode->rightChild);
        printf("%c", pNode->data);
    }
}

void postorderRecursive(BinTree *BinTree)
{
    if (BinTree != NULL)
    {
        postorderRecursiveNode(BinTree->root);
        printf("\n");
    }
}

BinTree *createExampleTree()
{
    BinTree *pBinTree = NULL;
    BinTreeNode *NodeA = NULL, *NodeB = NULL, *NodeC = NULL;
    BinTreeNode *NodeD = NULL, *NodeE = NULL, *NodeF = NULL, *NodeG;

    pBinTree = createBinTree('A');
    if (pBinTree != NULL)
    {
        NodeA = getRoot(pBinTree);
        NodeB = addLeftChild(NodeA, 'B');
        NodeC = addRightChild(NodeA, 'C');

        if (NodeB != NULL)
        {
            addLeftChild(NodeB, 'D');
            addRightChild(NodeB, 'E');
        }
        if (NodeC != NULL)
        {

            addLeftChild(NodeC, 'F');
            addRightChild(NodeC, 'G');
        }
    }

    return pBinTree;
}

int main(int argc, char *argv[])
{

    BinTree *BinTree = createExampleTree();
    if (BinTree != NULL)
    {
        printf("Pre-order Traversal Result: ");
        preorderRecursive(BinTree);
        printf("In-order Traversal Result: ");
        inorderRecursive(BinTree);
        printf("Post-order Traversal Result: ");
        postorderRecursive(BinTree);

        deleteBinTree(BinTree);
    }

    return 0;
}