#include "UI.h"
#include <stdio.h>
#include <ctype.h>
Console* createConsole(Service* service) {

	Console* console = (Console*)malloc(sizeof(Console));
	if (console == NULL)
	{
		return NULL;
	}
	console->service = service;
	return console;
}

int ui_add(Console* console, char* command) {
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
	if (service_addBot(console->service, serialNumber, state, specialization, newEnergyCostToRepair) == -1) {
		printf("No!");
		return -1;
	}
	return 0;
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
	else if (isalpha(command[0]))
	{
		command[strlen(command) - 1] = '\0';
		int number_of_specialized_bots = service_getNumberOfSpecializedBots(console->service, command);
		TElem* specialised_bots = service_getSpecializedBots(console->service, command);
		for (int i = 0; i < number_of_specialized_bots; ++i) {
			printf("Serial Number:%d , State:%s , Specialization:%s , EnergyCostToRepair:%d \n",
				getSerialNumber(&specialised_bots[i]), getState(&specialised_bots[i]), getSpecialization(&specialised_bots[i]),
				getEnergyCostToRepair(&specialised_bots[i]));
		}
		free(specialised_bots);
	}
	else if (isdigit(command[0]))
	{
		command[strlen(command) - 1] = '\0';
		int maximumEnergyCostToRepair = atoi(command);

		int lenght = service_getNumberOfBotsRespectingCriteria(console->service, maximumEnergyCostToRepair);
		TElem* selected_bots = service_getOrderedBotsRespectingCriteria(console->service, maximumEnergyCostToRepair);
		for (int i = 0; i < lenght; ++i) {
			printf("Serial Number:%d , State:%s , Specialization:%s , EnergyCostToRepair:%d \n",
				getSerialNumber(&selected_bots[i]), getState(&selected_bots[i]),
				getSpecialization(&selected_bots[i]), getEnergyCostToRepair(&selected_bots[i]));

		}
		free(selected_bots);
	}

}

int ui_delete(Console* console, char* command) {
	command = strtok(NULL, ", ");
	int serialNumber = atoi(command);
	if (service_deleteBot(console->service, serialNumber) == -1) {
		printf("No!");
		return -1;
	}
	return 0;
}


int ui_updateBot(Console* console, char* command) {
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
	if (service_updateBot(console->service, serialNumber, newState, newSpecialization, newEnergyCostToRepair) == -1) {
		printf("Inexistent bot!");
		return -1;
	}
	return 0;
}

void print_menu() {
	printf(" List of commands: \n");
	printf("-> add <serialNumber>, <state>, <specialization>, <energyCost> \n");
	printf("-> delete <serialNumber> \n");
	printf("-> update <serialNumber>, <state>, <specialization>, <energyCost> \n");
	printf("-> list \n");
	printf("-> list <specialization> \n");
	printf("-> list <energyCost> \n");
	printf("-> undo \n");
	printf("-> redo \n");
	printf(" \n ");
}

void run(Console* console) {
	char user_input[100];
	char user_command[100];
	char undo_command_list[100][100];
	char redo_command_list[100][100];
	char copy_user_input[100];
	int universal_index = -1;
	int number_of_operations = 0;
	print_menu();
	while (1) {
		fgets(user_input, sizeof(user_input), stdin);
		strcpy(copy_user_input, user_input);
		strcpy(user_command, strtok(user_input, " "));
		if (strcmp(user_command, "exit\n") == 0)
		{
			clear_dynamicVector(console->service);
			clear_repository(console->service);
			clear_service(console->service);
			free_console(console);
			return 0;
		}
		else if (strcmp(user_command, "add") == 0)
		{
			if (ui_add(console, user_input)!= -1) {
				universal_index = universal_index + 1;
				strcpy(redo_command_list[universal_index], copy_user_input);
				char undo_command[MAX_SIZE];
				char* get_specifications;
				strcpy(undo_command, "delete ");
				get_specifications = strtok(copy_user_input, " ");
				get_specifications = strtok(NULL, ", ");
				strcat(undo_command, strcat(get_specifications, "\n"));
				strcpy(undo_command_list[universal_index], undo_command);
				number_of_operations = number_of_operations + 1;
			}
		}
		else if (strcmp(user_command, "undo\n") == 0) {
			if (universal_index < 0 || universal_index >= number_of_operations)
				printf("No more undo!");
			else {
				char last_command[MAX_SIZE];
				strcpy(last_command, undo_command_list[universal_index]);
				strcpy(user_command, strtok(last_command, " "));
				if (strcmp(user_command, "delete") == 0)
					ui_delete(console, last_command);
				else if (strcmp(user_command, "add") == 0)
					ui_add(console, last_command);
				else if (strcmp(user_command, "update") == 0)
					ui_updateBot(console, last_command);
				universal_index = universal_index - 1;
			}

		}
		else if (strcmp(user_command, "redo\n") == 0) {

			if (universal_index < -1 || universal_index >= number_of_operations - 1)
				printf("No more redo!");
			else
			{

				char last_command[MAX_SIZE];
				universal_index = universal_index + 1;
				strcpy(last_command, redo_command_list[universal_index]);
				strcpy(user_command, strtok(last_command, " "));
				if (strcmp(user_command, "add") == 0)
					ui_add(console, last_command);
				else if (strcmp(user_command, "delete") == 0)
					ui_delete(console, last_command);
				else if (strcmp(user_command, "update") == 0)
					ui_updateBot(console, last_command);
			}

		}

		else if (strcmp(user_command, "list\n") == 0)
			ui_list(console, user_input);
		else if (strcmp(user_command, "list") == 0) {
			ui_list(console, user_input);
		}
		else if (strcmp(user_command, "delete") == 0)
		{
			
			char undo_command_delete[MAX_SIZE];
			strcpy(undo_command_delete, "add ");
			int serial_number = extract_number(console, copy_user_input);
			strcat(undo_command_delete, find_bot_after_serialNumber_service(console->service, serial_number));
			
			if (ui_delete(console, user_input) != -1) {
				universal_index = universal_index + 1;
				strcpy(redo_command_list[universal_index], copy_user_input);
				strcpy(undo_command_list[universal_index], undo_command_delete);
				number_of_operations = number_of_operations + 1;
			}
		}



		else if (strcmp(user_command, "update") == 0)
		{
			char undo_command_update[MAX_SIZE];
			strcpy(undo_command_update, "update ");
			int serial_number = extract_number(console, copy_user_input);
			strcat(undo_command_update, find_bot_after_serialNumber_service(console->service, serial_number));
			if (ui_updateBot(console, user_input) != -1) {
				universal_index = universal_index + 1;
				strcpy(redo_command_list[universal_index], copy_user_input);
				strcpy(undo_command_list[universal_index], undo_command_update);
				number_of_operations = number_of_operations + 1;
			}
		}

	}
}

int find_bot_after_serialNumber(Console* console, int serial_number)
{
	return find_bot_after_serialNumber(console->service, serial_number);
}

int extract_number(Console* console, char sequence[]) {
	int number = 0;
	int no_occurence = 0;
	for (int index = 0; index < strlen(sequence); index++)
	{
		if (isdigit(sequence[index]) && no_occurence < 2)
			number = number * 10 + sequence[index] - '0';
		else if (sequence[index] == 32)
			no_occurence = no_occurence + 1;
	}
	return number;
}

int free_console(Console* console) {
	free(console);
	return 0;
}


