#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedStackNodeType {
	char data;
	struct LinkedStackNodeType* pLink;
}LinkedStackNode;

typedef struct LinkedStackType {
	int currentCount; // Current Number of node
	LinkedStackNode* pTop; // Pointer of top node
}LinkedStack;

LinkedStack* createLinkedStack() {
	LinkedStack* pReturn = NULL;
	pReturn = (LinkedStack*)malloc(sizeof(LinkedStack));
	memset(pReturn, 0, sizeof(LinkedStack));
	return pReturn;
}

int pushLS(LinkedStack* pStack, char data) {
	int ret = 0;
	LinkedStackNode* pNode = NULL;

	// Make new node, set data
	if (pStack != NULL) {
		pNode = (LinkedStackNode*)malloc(sizeof(LinkedStackNode));
		if (pNode != NULL) {
			pNode->data = data;
			// Specifies an existing top node as the old node of the newly added node.
			pNode->pLink = pStack->pTop;
			// Change the top node to a newly added node.
			pStack->pTop = pNode;

			pStack->currentCount++;
			ret = 1;
		}
	}
	else {
		printf("Error, memory allocation, pushLS()\n");
	}

	return ret;
}

int isLinkedStackEmpty(LinkedStack* pStack) {
	int ret = 0;

	if (pStack != NULL) {
		if (pStack->currentCount == 0) {
			ret = 1;
		}
	}

	return ret;
}

LinkedStackNode* popLS(LinkedStack* pStack) {
	LinkedStackNode* pReturn = NULL;

	if (pStack != NULL) {
		// Check Validation
		if (isLinkedStackEmpty(pStack) == 0) {
			// Specify existing top node as return node
			pReturn = pStack->pTop;
			// Designates a new top node as the previous node of an existing top node.
			pStack->pTop = pReturn->pLink;
			// Initialize the previous node's data on the return node.
			pReturn->pLink = NULL;
			
			pStack->currentCount--;
		}
	}

	return pReturn;
}

LinkedStackNode* peekLS(LinkedStack* pStack) {
	LinkedStackNode* pReturn = NULL;
	if (pStack != NULL) {
		// Check Validation
		if (isLinkedStackEmpty(pStack) == 0) {
			// Specify a return value, return the pointer pointing to the top node of the stack.
			pReturn = pStack->pTop;
		}
	}

	return pReturn;
}

void deleteLinkedStack(LinkedStack* pStack) {
	LinkedStackNode* pNode = NULL;
	LinkedStackNode* pDelNode = NULL;

	if (pStack != NULL) {
		pNode = pStack->pTop;
		while (pNode != NULL) {
			pDelNode = pNode;
			pNode = pNode->pLink;
			free(pDelNode);
		}
		free(pStack);
	}
}

void displayLinkedStack(LinkedStack* pStack) {
	LinkedStackNode* pNode = NULL;
	int i = 1;
	if (pStack != NULL) {
		printf("Current number of nodes: %d\n", pStack->currentCount);
		pNode = pStack->pTop;
		while (pNode != NULL) {
			printf("[%d]-[%c]\n", pStack->currentCount - 1, pNode->data);
			i++;
			pNode = pNode->pLink;
		}
	}
}

int main(int argc, char* argv[]) {
	LinkedStack* pStack = NULL;
	LinkedStackNode* pNode = NULL;

	pStack = createLinkedStack();
	if (pStack != NULL) {
		pushLS(pStack, 'A');
		pushLS(pStack, 'B');
		pushLS(pStack, 'C');
		pushLS(pStack, 'D');
		displayLinkedStack(pStack);

		pNode = popLS(pStack);
		if (pNode != NULL) {
			printf("Pop-[%c]\n", pNode->data);
			free(pNode);
		}

		displayLinkedStack(pStack);
		pNode = peekLS(pStack);
		if (pNode != NULL) {
			printf("Peek-[%c]\n", pNode->data);
		}

		displayLinkedStack(pStack);

		deleteLinkedStack(pStack);
	}

	return 0;
}