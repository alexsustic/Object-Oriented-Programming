#include <string.h>
#include <stdio.h>
#include "Domain.h"

Bot createBot(int serialNumber, char state[], char specialization[], int newEnergyCostToRepair)
{
	Bot newBot;
	newBot.serialNumber = serialNumber;
	strcpy(newBot.state, state);
	strcpy(newBot.specialization, specialization);
	newBot.newEnergyCostToRepair = newEnergyCostToRepair;

	return newBot;

}

int getSerialNumber(Bot* newBot)
{
	return newBot->serialNumber;
}

int getEnergyCostToRepair(Bot* newBot)
{
	return newBot->newEnergyCostToRepair;
}

char* getState(Bot* newBot)
{
	return newBot->state;
}

char* getSpecialization(Bot* newBot)
{
	return newBot->specialization;
}