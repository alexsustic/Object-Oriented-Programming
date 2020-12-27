#pragma once
#include "Repository.h"

typedef struct
{
	Repository* repository;
}Service;

Service* createService(Repository* repository);

int service_addBot(Service* service, int SerialNumber, char* state, char* specialization, int newEnergyCostToRepair);
TElem* getBots(Service* service);
int service_getLength(Service* service);
int service_deleteBot(Service* service, int SerialNumber);
int service_updateBot(Service* service, int SerialNumber, char* state, char* specialization, int newEnergyCostToRepair);
int service_getNumberOfSpecializedBots(Service* service, char* specialization);
TElem* service_getSpecializedBots(Service* service, char* specialization);