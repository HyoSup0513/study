#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ArrayListNodeType {
	int data;
} ArrayListNode;

typedef struct ArrayListType {
	int maxCount; // 최대 자료 개수: 배열의 크기
	int currentCount; // 현재 자료 개수
	ArrayListNode *pData; // 자료 저장을 위한 1차원 배열
} ArrayList;

ArrayList *createList(int count) {
	if (count <= 0)
		return NULL;

	else {
		ArrayList* pReturn = (ArrayList*)malloc(sizeof(ArrayList));

		if (pReturn != NULL) {
			pReturn->maxCount = count;
			pReturn->currentCount = 0;
			pReturn->pData = (ArrayListNode*)malloc(sizeof(ArrayListNode) * count);

			// pReturn->pData 가 가리키는 메모리를 sizeof(ArrayListNode) * count 바이트만큼 0으로 설정
			memset(pReturn->pData, 0, sizeof(ArrayListNode) * count);

			return pReturn;
		}
		else
			return NULL;
		
	}
}

int addListData(ArrayList* pList, int position, int data) {
	if (pList == NULL)
		return 1;
	if (pList->currentCount < pList->maxCount) {
		if (position < 0 && position > pList->currentCount)
			return 2;
	}

	int i = 0;
	for (i = pList->currentCount - 1; i >= position; i--) {
		pList->pData[i + 1] = pList->pData[i];
	}
	
	pList->pData[position].data = data;
	pList->currentCount++;
	return 0;
}

int removeListData(ArrayList* pList, int position){
	if (pList == NULL)
		return 1;
	if (position < 0 && position > pList->currentCount - 1)
		return 2;

	int i = 0;
	for (i = position; i < pList->currentCount - 1; i++) {
		pList->pData[i] = pList->pData[i + 1];
	}

	pList->currentCount--;
	return 0;
}

int getListData(ArrayList* pList, int position) {
	if (pList == NULL)
		return 1;
	if (position < 0 && position > pList->currentCount - 1)
		return 2;

	return pList->pData[position].data;
}

void deleteList(ArrayList* pList) {
	if (pList != NULL) {
		if (pList->pData != NULL) {
			free(pList->pData);
		}
		free(pList);
	}
}
int getListLength(ArrayList* pList) {
	return pList->currentCount;
}

int main() {
	ArrayList* pList = NULL;
	int value = 0;

	pList = createList(5);
	addListData(pList, 0, 10);
	addListData(pList, 1, 20);
	addListData(pList, 0, 30);

	// value = getListData(pList, 1);
	value = getListLength(pList);
	// printf("위치: %d, 값: %d\n", 1, value);
	printf("자료의 개수: %d\n", value);

	removeListData(pList, 0);
	deleteList(pList);

	return 0;
}