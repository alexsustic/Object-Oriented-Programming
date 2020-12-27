#include "Service.h"
Service* createService(Repository* repository)
{
	Service* service = (Service*)malloc(sizeof(Service));
	if (service == NULL)
		return NULL;
	service->repository = repository;
	return service;
}

int service_addBot(Service* service, int SerialNumber, char* state, char* specialization, int newEnergyCostToRepair) {
	Bot bot = createBot(SerialNumber, state, specialization, newEnergyCostToRepair);
	return addBot(service->repository, bot);
}

int service_deleteBot(Service* service, int SerialNumber) {
	return deleteBot(service->repository, SerialNumber);
}

int service_updateBot(Service* service, int SerialNumber, char* state, char* specialization, int newEnergyCostToRepair) {
	Bot updated_bot = createBot(SerialNumber, state, specialization, newEnergyCostToRepair);
	return updateBot(service->repository, updated_bot);

}

int service_getNumberOfSpecializedBots(Service* service, char* specialization) {
	return getNumberOfSpecializedBots(service->repository,specialization);
}
TElem* service_getSpecializedBots(Service* service, char* specialization) {
	return  getSpecializedBots(service->repository, specialization);
}
TElem* getBots(Service* service) {
	return getAll(service->repository);
}

int service_getLength(Service* service)
{
	return getLength(service->repository);
}
