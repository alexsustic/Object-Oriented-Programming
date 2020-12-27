#include "Repository.h"
#include <stdio.h>
#include <string.h>
Repository* createRepository() {
	Repository* repo = (Repository*)malloc(sizeof(Repository));
	if (NULL == repo)
	{
		return NULL;
	}
	repo->data.lenght = 0;
	return repo;
}
int hasBot(Repository* repository, TElem b)
{
	for (int i = 0; i < repository->data.lenght; ++i) {
		if (getSerialNumber(&repository->data.bots[i])==getSerialNumber(&b)){
			return 1;
		}
	}
		return 0;
}

int addBot(Repository* repository, TElem b) {
	if (hasBot(repository, b))
	{
		return -1;
	}
	repository->data.bots[repository->data.lenght++] = b;
	return 0;
}
int getLength(Repository* repository) {
	return repository->data.lenght;
}

int deleteBot(Repository* repository, int SerialNumber) {
	Bot bot = createBot(SerialNumber, "xx", "xx", 0);
	if (!hasBot(repository,bot))
	{
		return -1;
	}
		for (int i = 0; i < repository->data.lenght; i++)
		{
			if (getSerialNumber(&repository->data.bots[i]) == SerialNumber)
			{
				for (int j = i; j < repository->data.lenght; j++)
					repository->data.bots[j] = repository->data.bots[j + 1];
				repository->data.lenght--;
			}
		}
	return 0;
}

int updateBot(Repository* repository, TElem updated_bot) {
	for (int i = 0; i < repository->data.lenght; i++) {
		if (getSerialNumber(&updated_bot) == getSerialNumber(&repository->data.bots[i])) {
			repository->data.bots[i] = updated_bot;
		}

	}

}
int getNumberOfSpecializedBots(Repository* repository, char* specialization) {
	int number_of_specialized_bots = 0;
	for (int i = 0; i < repository->data.lenght; i++) {
		if (strcmp(getSpecialization(&repository->data.bots[i]),specialization)==0) {
			number_of_specialized_bots++;
		}
	}
	return number_of_specialized_bots;
 }

TElem* getSpecializedBots(Repository * repository, char* specialization) {
	TElem *specialized_bots = malloc(sizeof(TElem) * MAX_SIZE);
	int index = 0;
	
	for (int i = 0; i < repository->data.lenght; i++) {
		
		if (strcmp(getSpecialization(&repository->data.bots[i]), specialization) == 0) {
			specialized_bots[index] = repository->data.bots[i];
			index++;
		}
	}
	return specialized_bots;
	}
TElem* getAll(Repository* repository)
{
	return repository->data.bots;
}




