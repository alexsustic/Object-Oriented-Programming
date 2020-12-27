#pragma once
#define MAX_SIZE 128
#include "Domain.h"
#include <stdlib.h>

typedef Bot TElem;

typedef struct {
	TElem bots[MAX_SIZE];
	int lenght;
}Container;

typedef struct {
	Container data;
}Repository;

Repository* createRepository();
int hasBot(Repository* repository, TElem bot_to_search);
int addBot(Repository* repository, TElem bot_to_add);
int getLength(Repository* repository);
int deleteBot(Repository* repository, int SerialNumber);
int updateBot(Repository* repository, TElem updated_bot);
TElem* getAll(Repository* repository);
int getNumberOfSpecializedBots(Repository* repository, char* specialization);
TElem* getSpecializedBots(Repository* repository, char* specialization);
///void destroyRepository(Repository* repository);
