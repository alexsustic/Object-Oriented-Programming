#pragma once

typedef struct
{
    int serialNumber;
    char state[50];
    char specialization[50];
    int newEnergyCostToRepair;

}Bot;

Bot createBot(int serialNumber, char state[], char specialization[], int newEnergyCostToRepair);
char* getState(Bot* newBot);
char* getSpecialization(Bot* newBot);
int getSerialNumber(Bot* newBot);
int getEnergyCostToRepair(Bot* newBot);
