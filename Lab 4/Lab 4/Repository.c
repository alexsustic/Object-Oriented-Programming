#include "Repository.h"
#include <stdio.h>
#include <string.h>
Repository* createRepository(DynamicVector* dynamicVector) {
	Repository* repo = (Repository*)malloc(sizeof(Repository));
	if (NULL == repo)
	{
		return NULL;
	}
	repo->dynamicVector = dynamicVector;
	initialBots(repo);
	return repo;
}

DynamicVector* getVector(Repository* repository) {

	return repository->dynamicVector;
}

int initialBots(Repository* repository) {
	Bot b1 = createBot(100, "Perfect", "Doctor", 250);
	Bot b2 = createBot(200, "Fine", "Destroyer", 1000);
	Bot b3 = createBot(300, "Damaged", "Attacker", 500);
	Bot b4 = createBot(400, "Damaged", "Attacker", 700);
	Bot b5 = createBot(500, "Perfect", "Engineer", 900);
	addBot(repository, b1);
	addBot(repository, b2);
	addBot(repository, b3);
	addBot(repository, b4);
	addBot(repository, b5);
	return 0;
}

int addBot(Repository* repository, TElem b) {
	int index = search(repository->dynamicVector, &b);
	if (index == -1)
	{
		addElement(repository->dynamicVector, b);
		return 1;
	}
	return -1;
	
}
int find_bot_after_serialNumber_repo(Repository* repository, int SerialNumber) {
	char bot_type_char[MAX_SIZE];
	char specialization[MAX_SIZE];
	char serialNumber[MAX_SIZE];
	char state[MAX_SIZE];
	char cost[MAX_SIZE];
	DynamicVector* dynamicVector = getVector(repository);
	Bot search_bot;
	for (int index = 0; index < dynamicVector->size; index++)
		if (getSerialNumber(&dynamicVector->elements[index]) == (int)SerialNumber)
		{
			sprintf(serialNumber, "%d", SerialNumber);
			strcpy(specialization, getSpecialization(&dynamicVector->elements[index]));
			strcpy(state, getState(&dynamicVector->elements[index]));
			sprintf(cost, "%d", getEnergyCostToRepair(&dynamicVector->elements[index]));
			strcpy(bot_type_char, serialNumber);
			strcat(bot_type_char, ", ");
			strcat(bot_type_char, state);
			strcat(bot_type_char, ", ");
			strcat(bot_type_char, specialization);
			strcat(bot_type_char, ", ");
			strcat(bot_type_char, cost);
			return bot_type_char;
		}
}

int getLength(Repository* repository) {
	return repository->dynamicVector->size;
}

int deleteBot(Repository* repository, int SerialNumber) {
	TElem bot = createBot(SerialNumber, "xx", "xx", 0);
	int index = search(repository->dynamicVector, &bot);
	if (index != -1)
	{
		deleteElement(repository->dynamicVector, index);
		return 1;
	}
	return -1;
}

int updateBot(Repository* repository, TElem updated_bot) {
	int index = search(repository->dynamicVector, &updated_bot);
	if (index != -1){
		updateElement(repository->dynamicVector, updated_bot, index);
		return 1;
	}
	return -1;
}

int getNumberOfSpecializedBots(Repository* repository, char* specialization) {
	int number_of_specialized_bots = 0;
	DynamicVector* dynamicVector = getVector(repository);
	for (int i = 0; i < dynamicVector->size; i++) {
		if (strcmp(getSpecialization(&dynamicVector->elements[i]), specialization) == 0) {
			number_of_specialized_bots++;
		}
	}
	return number_of_specialized_bots;
}

TElem* getSpecializedBots(Repository* repository, char* specialization) {
	TElem* specialized_bots = malloc(sizeof(TElem) * MAX_SIZE);
	DynamicVector* dynamicVector = getVector(repository);
	int index = 0;
	for (int i = 0; i < repository->dynamicVector->size; i++) {

		if (strcmp(getSpecialization(&dynamicVector->elements[i]), specialization) == 0) {
			specialized_bots[index] = dynamicVector->elements[i];

			index++;
		}
	}
	
	return specialized_bots;
}

int sortBotsAfterSerialNumber(Repository* repository, TElem* bots, int lenght) {

	for (int i = 0; i < lenght - 1; i++)
		for (int j = i + 1; j < lenght; j++) {
			if (getSerialNumber(&bots[i]) > getSerialNumber(&bots[j]))
			{
				Bot auxiliary = bots[i];
				bots[i] = bots[j];
				bots[j] = auxiliary;
			}

		}
	return bots;
}


TElem* sortBotsAfterState(Repository* repository, TElem* bots, int lenght) {
	for (int i = 0; i < lenght - 1; i++)
		for (int j = i + 1; j < lenght; j++) {

			if (strcmp(getState(&bots[i]), getState(&bots[j])) > 0)
			{
				Bot auxiliary = bots[i];
				bots[i] = bots[j];
				bots[j] = auxiliary;
			}

		}
	return bots;
}

TElem* getOrderedBotsSmallerThanCostEnergy(Repository* repository, int maximumEnergyCost) {
	TElem* bots_respecting_criteria = malloc(sizeof(TElem) * MAX_SIZE);
	DynamicVector* dynamicVector = getVector(repository);
	int index = 0;
	for (int i = 0; i < dynamicVector->size; i++) {

		if (getEnergyCostToRepair(&dynamicVector->elements[i]) <= maximumEnergyCost) {
			bots_respecting_criteria[index] = dynamicVector->elements[i];
			index += 1;
		}
	}
	return sortBotsAfterState(repository, bots_respecting_criteria, index);

}
int getNumberOfBotsRespectingCriteria(Repository* repository, int energyCost) {
	int number_of_bots_respecting_criteria = 0;
	DynamicVector* dynamicVector = getVector(repository);
	for (int i = 0; i < dynamicVector->size; i++) {
		if (getEnergyCostToRepair(&dynamicVector->elements[i]) <= energyCost) {
			number_of_bots_respecting_criteria++;
		}
	}
	return number_of_bots_respecting_criteria;
}


TElem* getAll(Repository* repository)
{
	DynamicVector* dynamicVector = getVector(repository);
	return sortBotsAfterSerialNumber(repository, dynamicVector->elements, dynamicVector->size);
}

void deleteRepository(Repository* repository)
{
	free(repository);
}

void destroy_dynamicVector(Repository* repository) {

	destroyDynamicVector(repository->dynamicVector);
}




