#include "DynamicVector.h"
#include <stdlib.h>

DynamicVector * createVector(int capacity)
{
	DynamicVector* dynamicVector = (DynamicVector*)malloc(sizeof(DynamicVector));
	if (dynamicVector == NULL)
		return NULL;
	dynamicVector->capacity = capacity;
	dynamicVector->size = 0;
	dynamicVector->elements = (TElem*)malloc(capacity * sizeof(TElem));
	return dynamicVector;
}


void resize(DynamicVector* dynamicVector) {
	if (dynamicVector == NULL)
		return;
	if (dynamicVector->capacity == 0)
		dynamicVector->capacity = 1;

	dynamicVector->capacity *= 2;
	TElem* auxiliary = (TElem*)malloc(dynamicVector->capacity * sizeof(TElem));
	if (auxiliary == NULL)
		return;
	for (int i = 0; i < dynamicVector->size; i++)
		auxiliary[i] = dynamicVector->elements[i];
	free(dynamicVector->elements);
	dynamicVector->elements = auxiliary;
	free(auxiliary);


}

void addElement(DynamicVector* dynamicVector, TElem elem)
{
	if (dynamicVector == NULL)
		return;
	if (dynamicVector->size == dynamicVector->capacity)
		resize(dynamicVector);
	dynamicVector->elements[dynamicVector->size] = elem;
	dynamicVector->size += 1;
}

int updateElement(DynamicVector* dynamicVector, TElem elem, int index)
{

	dynamicVector->elements[index] = elem;
	
}

int search(DynamicVector* dynamicVector, TElem* elem)
{
	for (int i = 0; i < dynamicVector->size; i++)
		if (getSerialNumber(&dynamicVector->elements[i]) == getSerialNumber(elem))
			return i;
	return -1;

}

int deleteElement(DynamicVector* dynamicVector, int index)
{
	for (int i = index; i < dynamicVector->size - 1; i++)
		dynamicVector->elements[i] = dynamicVector->elements[i + 1];
	dynamicVector->size -= 1;
}


int destroyDynamicVector(DynamicVector* dynamicVector) {

	free(dynamicVector->elements);
	free(dynamicVector);
}

int getSize(DynamicVector* dynamicVector)
{
	if (dynamicVector == NULL)
		return 0;
	return dynamicVector->size;
}

int getCapacity(DynamicVector* dynamicVector)
{
	if (dynamicVector == NULL)
		return 0;
	return dynamicVector->capacity;
}
