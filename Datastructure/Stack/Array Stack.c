#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ArrayStackNodeType {
	char data;
}ArrayStackNode;

typedef struct ArrayStackType {
	int maxcount; // Maxium number of data.
	int currentcount; // Currnet number of stored data.
	ArrayStackNode* pData; // 1 dimensional array to store data.
}ArrayStack;

ArrayStack* createArrayStack(int size) {
	ArrayStack* pReturn = NULL;
	pReturn = (ArrayStack*)malloc(sizeof(ArrayStack)); // Memory allocation.
	memset(pReturn, 0, sizeof(ArrayStack)); // Memory initialization.
	pReturn->maxcount = size; // Set Maximum number of data.

	// Creating and initializing arrays with elements as many as the max number of data.
	pReturn->pData = (ArrayStackNode*)malloc(sizeof(ArrayStackNode) * size);
	memset(pReturn->pData, 0, sizeof(ArrayStackNode) * size);

	return pReturn;
}

// Check if the array stack is full.
int isArrayStackFull(ArrayStack* pStack) {

	int ret = 0;
	if (pStack != NULL) {
		if (pStack->currentcount == pStack->maxcount) {
			ret = 1;
		}
	}

	return ret;
}

// push, AS: ArrayStack
int pushAS(ArrayStack* pStack, char data) {

	int ret = 0;
	// determine if the array stack is full.
	if (isArrayStackFull(pStack) == 0) {
		// push data to TOP.
		pStack->pData[pStack->currentcount].data = data;

		// Change the position of TOP.
		pStack->currentcount++;
		ret = 1;
	}
	else {
		printf("Error, stack is full !, pushAS()\n");
	}
	return ret;
}

int isArrayStackEmpty(ArrayStack* pStack) {
	int ret = 0;
	if (pStack != NULL) {
		if (pStack->currentcount == 0) {
			ret = 1;
		}
	}

	return ret;
}

ArrayStackNode* popAS(ArrayStack* pStack) {
	ArrayStackNode* pReturn = NULL;

	// Check if the array stack if empty.
	if (0 == isArrayStackEmpty(pStack)) {
		// Memory allocation and memory check for nodes to return.
		pReturn = (ArrayStackNode*)malloc(sizeof(ArrayStackNode));

		if (pReturn != NULL) {
			// Enter the data to be returned to the node.
			pReturn->data = pStack->pData[pStack->currentcount - 1].data;
			// Change the position of TOP, to left.
			pStack->currentcount--;
		}

		else {
			printf("Error, memory allocation, popAS()\n");
		}
	}

	return pReturn;
}


ArrayStackNode* peekAS(ArrayStack* pStack) {
	ArrayStackNode* pReturn = NULL;
	if (pStack != NULL) {
		// Check if the array stack is empty.
		if (isArrayStackEmpty(pStack) == 0) {
			// Speicfy a return value, return a pointer that points the top node of the array stack.
			pReturn = &(pStack->pData[pStack->currentcount - 1]);
		}
	}

	return pReturn;
}

void deleteArrayStack(ArrayStack* pStack) {
	if (pStack != NULL) {
		if (pStack->pData != NULL) {
			free(pStack->pData);
		}
		free(pStack);
	}
}

void displayArrayStack(ArrayStack* pStack) {
	int i = 0;
	if (pStack != NULL) {
		int size = pStack->maxcount;
		int top = pStack->currentcount;

		printf("Stack Size: %d, Number of nodes: %d\n", pStack->maxcount, pStack->currentcount);

		for (i = size - 1; i >= top; i--) {
			printf("[%d]-[Empty]\n", i);
		}

		for (i = top-1; i >= 0; i--) {
			printf("[%d]-[%c]\n", i, pStack->pData[i].data);
		}
	}
}

int main(int argc, char* argv[]) {
	ArrayStack* pStack = NULL;
	ArrayStackNode* pNode = NULL;

	pStack = createArrayStack(6);
	if (pStack != NULL) {
		pushAS(pStack, 'A');
		pushAS(pStack, 'B');
		pushAS(pStack, 'C');
		pushAS(pStack, 'D');
		displayArrayStack(pStack);

		pNode = popAS(pStack);
		if (pNode != NULL) {
			printf("Pop value-[%c]\n", pNode->data);
			free(pNode);
		}

		displayArrayStack(pStack);

		pNode = peekAS(pStack);
		if (pNode != NULL) {
			printf("Peek value-[%c]\n", pNode->data);
		}
		displayArrayStack(pStack);

		deleteArrayStack(pStack);
	}
	return 0;
}