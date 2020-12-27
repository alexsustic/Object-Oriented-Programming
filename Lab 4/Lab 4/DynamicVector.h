#pragma once
#include "Domain.h"
typedef Bot TElem;

typedef struct
{
	int capacity;
	int size;
	TElem* elements;
} DynamicVector;

DynamicVector* createVector(int capacity);
void addElement(DynamicVector* dynamicVector, TElem elem);
int updateElement(DynamicVector* dynamicVector, TElem elem, int index);
int search(DynamicVector* dynamicVector, TElem* elem);
int deleteElement(DynamicVector* dynamicVector, int index);
int getSize(DynamicVector* dynamicVector);
int getCapacity(DynamicVector* dynamicVector);