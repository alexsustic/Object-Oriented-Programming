#include "UI.h"
#include <stdio.h>

Console* createConsole(Service* service) {

	Console* console = (Console*)malloc(sizeof(Console));
	if (console == NULL)
	{
		return NULL;
	}
	console->service = service;
	return console;
}

void ui_add(Console* console, char* command) {
	int serialNumber, newEnergyCostToRepair;
	char state[MAX_SIZE], specialization[MAX_SIZE];
	command = strtok(NULL, ", ");
	serialNumber = atoi(command);
	command = strtok(NULL, ", ");
	strcpy(state, command);
	command = strtok(NULL, ", ");
	strcpy(specialization, command);
	command = strtok(NULL, ", ");
	newEnergyCostToRepair = atoi(command);
	if (service_addBot(console->service, serialNumber, state, specialization, newEnergyCostToRepair) == -1){
        printf("No!");
	}
}
void ui_list(Console* console, char* command) {
	command = strtok(NULL, " ");
	
	if (command == NULL)
	{   
		int length = service_getLength(console->service);
		for (int i = 0; i < length; ++i) {
			printf("Serial Number:%d , State:%s , Specialization:%s , EnergyCostToRepair:%d \n",
				getSerialNumber(&getBots(console->service)[i]), getState(&getBots(console->service)[i]),
				getSpecialization(&getBots(console->service)[i]), getEnergyCostToRepair(&getBots(console->service)[i]));

		}
	}
	else
	{
		command[strlen(command) - 1] = '\0';
		int number_of_specialized_bots = service_getNumberOfSpecializedBots(console->service,command);
		for (int i = 0; i < number_of_specialized_bots; ++i) {
			printf("Serial Number:%d , State:%s , Specialization:%s , EnergyCostToRepair:%d \n",
				getSerialNumber(&service_getSpecializedBots(console->service,command)[i]), getState(&service_getSpecializedBots(console->service,command)[i]),
				getSpecialization(&service_getSpecializedBots(console->service,command)[i]), getEnergyCostToRepair(&service_getSpecializedBots(console->service,command)[i]));

		}
	}

}

void ui_delete(Console* console, char* command){
	command = strtok(NULL, ", ");
	int serialNumber = atoi(command);
	if (service_deleteBot(console->service, serialNumber) == -1) {
		printf("No!");
	}
}

void ui_updateBot(Console* console, char* command) {
	int serialNumber, newEnergyCostToRepair;
	char newState[MAX_SIZE], newSpecialization[MAX_SIZE];
	command = strtok(NULL, ", ");
	serialNumber = atoi(command);
	command = strtok(NULL, ", ");
	strcpy(newState, command);
	command = strtok(NULL, ", ");
	strcpy(newSpecialization, command);
	command = strtok(NULL, ", ");
	newEnergyCostToRepair = atoi(command);
	service_updateBot(console->service, serialNumber, newState, newSpecialization, newEnergyCostToRepair);
}
void run(Console* console) {
	char user_input[MAX_SIZE];
	char user_command[MAX_SIZE];
	while (1) {
		fgets(user_input, sizeof(user_input), stdin);
		strcpy(user_command, strtok(user_input, " "));
		//printf("%s \n", user_command);
		//printf("%s \n", user_input);
		if (strcmp(user_command, "exit\n") == 0)
			return 0;
		else if (strcmp(user_command, "add") == 0)
			ui_add(console, user_input);
		else if (strcmp(user_command, "list\n") == 0)
			ui_list(console,user_input);
		else if (strcmp(user_command, "list") == 0) {
			ui_list(console, user_input);
		}
		else if (strcmp(user_command, "delete") == 0)
			ui_delete(console, user_input);
		else if (strcmp(user_command, "update") == 0)
			ui_updateBot(console, user_input);
	}
}

