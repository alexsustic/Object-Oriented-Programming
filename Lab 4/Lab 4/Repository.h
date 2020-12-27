#pragma once
#define MAX_SIZE 1000
#include "Domain.h"
#include "DynamicVector.h"
#include <stdlib.h>

typedef Bot TElem;

typedef struct {
	DynamicVector* dynamicVector;
}Repository;

Repository* createRepository(DynamicVector* dynamicVector);
DynamicVector* getVector(Repository* repository);
int addBot(Repository* repository, TElem bot_to_add);
int getLength(Repository* repository);
int deleteBot(Repository* repository, int SerialNumber);
int updateBot(Repository* repository, TElem updated_bot);
TElem* getAll(Repository* repository);
int getNumberOfSpecializedBots(Repository* repository, char* specialization);
TElem* getSpecializedBots(Repository* repository, char* specialization);

