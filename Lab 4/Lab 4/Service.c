#include "Service.h"
Service* createService(Repository* repository)
{
	Service* service = (Service*)malloc(sizeof(Service));
	if (service == NULL)
		return NULL;
	service->repository = repository;
	return service;
}

void clear_dynamicVector(Service* service) {
	destroy_dynamicVector(service->repository);

}
int service_addBot(Service* service, int SerialNumber, char* state, char* specialization, int newEnergyCostToRepair) {
	Bot bot = createBot(SerialNumber, state, specialization, newEnergyCostToRepair);
	return addBot(service->repository, bot);
}

int find_bot_after_serialNumber_service(Service* service, int SerialNumber) {
	return find_bot_after_serialNumber_repo(service->repository, SerialNumber);
}

int service_deleteBot(Service* service, int SerialNumber) {
	return deleteBot(service->repository, SerialNumber);
}

int service_updateBot(Service* service, int SerialNumber, char* state, char* specialization, int newEnergyCostToRepair) {
	Bot updated_bot = createBot(SerialNumber, state, specialization, newEnergyCostToRepair);
	return updateBot(service->repository, updated_bot);

}
int service_getNumberOfSpecializedBots(Service* service, char* specialization) {
	return getNumberOfSpecializedBots(service->repository, specialization);
}
TElem* service_getSpecializedBots(Service* service, char* specialization) {
	
	return  getSpecializedBots(service->repository, specialization);
}
TElem* getBots(Service* service) {
	return getAll(service->repository);
}

int service_getNumberOfBotsRespectingCriteria(Service* service, int maximumEnergyCost) {
	return getNumberOfBotsRespectingCriteria(service->repository, maximumEnergyCost);
}
TElem* service_getOrderedBotsRespectingCriteria(Service* service, int maximumEnergyCost) {
	return getOrderedBotsSmallerThanCostEnergy(service->repository, maximumEnergyCost);

}

int clear_repository(Service* service) {
	return deleteRepository(service->repository);
}

void clear_service(Service* service) {
	free(service);
}
int service_getLength(Service* service)
{
	return getLength(service->repository);
}
