#include "UI.h"
#include <string>
using namespace std;

void UI::ui_addPlantCluster(std::string command) {
	std::string codedName = command.substr(0, command.find(", "));
	command.erase(0, command.find(" ") + 1);
	std::string species = command.substr(0, command.find(", "));
	command.erase(0, command.find(" ") + 1);
	int ageInMonths = stoi(command.substr(0, command.find(", ")));
	command.erase(0, command.find(" ") + 1);
	std::string digitizedscan = command.substr(0, command.find(", "));
	command.erase(0, command.find(" ") + 1);
	if (this->service.addPlant(codedName, species, ageInMonths, digitizedscan) == -1)
		cout << "This plant cluster already exists!\n";
	
}
void UI::ui_displayPlantClusters() {
	DynamicVector<PlantCluster> plants = this->service.getAllPlantClustersInRepo();
	for (int index = 0; index < plants.getSize(); index++) {
		PlantCluster plantCluster = plants.getElement(index);
		cout << plantCluster.toString() << "\n";
	}
}

void UI::ui_updatePlantCluster(std::string command) {
	std::string codedName = command.substr(0, command.find(", "));
	command.erase(0, command.find(", ") + 1);
	std::string species = command.substr(0, command.find(", "));
	command.erase(0, command.find(", ") + 1);
	int ageInMonths = stoi(command.substr(0, command.find(", ")));
	command.erase(0, command.find(", ") + 1);
	std::string digitizedscan = command.substr(0, command.find(", "));
	command.erase(0, command.find(", ") + 1);
	if (this->service.updatePlant(codedName, species, ageInMonths, digitizedscan) == -1) {
		cout << "Inexisting plant cluster!\n";
	}
}

void UI::ui_deletePlantCluster(std::string command) {
	if (this->service.deletePlant(command) == -1) {
		cout << "Inexisting plant cluster!\n";
	}
}

void UI::printMenu_administrator() {
	cout << "\n";
	cout << "Please use the commands mentioned above:\n";
	cout << "   -> add codedName, species, ageInMonths, digitizedScan\n";
	cout << "   -> update codedName, newSpecies, newAgeInMonths, newDigitizedScan\n";
	cout << "   -> delete codedName\n";
	cout << "   -> list\n";
	cout << "   -> mode B (access assistant mode)\n";
	cout << "   -> exit\n";

}

void UI::printMenu_assistant() {
	cout << "\n";
	cout << "Please use the commands mentioned above:\n";
	cout << "   -> next\n";
	cout << "   -> save codedName(e.g.save I129)\n";
	cout << "   -> list species, age (e.g.list Solanum tuberosum, 2)\n";
	cout << "   -> mylist\n";
	cout << "   -> mode A (access administrator mode)\n";
	cout << "   -> exit\n";
}

void UI::initialPlantClusters() {
	this->service.initializePlantClusters();
}

void UI::ui_next() {
	PlantCluster plant = service.service_next();
	cout<<plant.toString()<<endl;

}

void UI::ui_save(std::string command) {
	std::string codedName = command.substr(0, command.find(", "));
	if (this->service.service_save(codedName) == -1)
		cout << "Inexisting plant cluster!";
}

void UI::ui_mylist() {
	DynamicVector <PlantCluster>plants = this->service.getAllPlants();
	for (int index = 0; index < plants.getSize(); index++)
	{
		PlantCluster plant = plants.getElement(index);
		cout << plant.toString() << endl;
	}
}

void UI::ui_list(std::string command) {
	int ageInMonths;
	std::string first_parameter = command.substr(0, command.find(", "));
	command.erase(0, command.find(", ") + 1);
	char* p;
	DynamicVector<PlantCluster> plants = this->service.getAllPlantClustersInRepo();

	strtol(first_parameter.c_str(), &p, 10);
	if (*p == 0) {
		ageInMonths = stoi(first_parameter);
		for (int i = 0; i < plants.getSize(); i++)
			if (plants.getElement(i).getAgeInMonths() < ageInMonths)
				cout << plants.getElement(i).toString() << endl;
	}
	else
	{
		ageInMonths= stoi(command.substr(0, command.find(", ")));
		for (int i = 0; i < plants.getSize(); i++)
			if (plants.getElement(i).getAgeInMonths() < ageInMonths && plants.getElement(i).getSpecies()==first_parameter)
				cout << plants.getElement(i).toString() << endl;
	}
	   
}
void UI::administrator() {
	printMenu_administrator();
	std::string mode;
	while (1) {
		std::string user_command;
		getline(cin, user_command);
		std::string ui_command = user_command.substr(0, user_command.find(" "));
		std::string parameters = user_command.substr(user_command.find(" ") + 1, sizeof(user_command));
		if (ui_command.compare("mode") == 0)
		{
			mode = user_command;
			if (mode.compare("mode B") == 0)
			{
				assistant();
				break;
			}
		}
		else if (ui_command.compare("add") == 0)
			ui_addPlantCluster(parameters);
		else if (ui_command.compare("list") == 0)
			ui_displayPlantClusters();
		else if (ui_command.compare("update") == 0 )
			ui_updatePlantCluster(parameters);
		else if (ui_command.compare("delete") == 0 )
			ui_deletePlantCluster(parameters);
		else if (ui_command.compare("exit") == 0)
			break;
	}

}

void UI::assistant() {
	std::string mode;
	printMenu_assistant();
	while (1) {
		std::string user_command;
		getline(cin, user_command);
		std::string ui_command = user_command.substr(0, user_command.find(" "));
		std::string parameters = user_command.substr(user_command.find(" ") + 1, sizeof(user_command));
		if (ui_command.compare("mode") == 0)
		{
			mode = user_command;
			if (mode.compare("mode A") == 0)
			{
				administrator();
				break;
			}
		}
		if (ui_command.compare("next") == 0)
			ui_next();
		else if (ui_command.compare("save") == 0)
			ui_save(parameters);
		else if (ui_command.compare("list") == 0)
			ui_list(parameters);
		else if (ui_command.compare("mylist") == 0)
			ui_mylist();
		else if (ui_command.compare("exit") == 0)
			break;
	}
}
void UI::run() {
	std::string mode;
	std::string user_command;
	std::string ui_command;
	cout << "Which mode would you like to choose?\n";
	cout << "<mode A> - administrator mode\n";
	cout << "<mode B> - assistant mode\n";
	initialPlantClusters();
	while (1) {
		
		cout << "Type the command: ";
		getline(cin, user_command);
		ui_command = user_command.substr(0, user_command.find(" "));
		if (ui_command.compare("mode") == 0)
			mode = user_command;

		if (mode.compare("mode A") == 0)
		{
			administrator();
			break;
		}
		else if (mode.compare("mode B") == 0)
		{
			assistant();
			break;
		}
		else if (user_command.compare("exit") == 0)
			break;
		else
		{
			cout << " Inexisting command! ";
			cout << "\n";
		}
	}
	
}