#include "UI.h"
#include <string>
using namespace std;

void UI::ui_addPlantCluster(std::string command) {
	std::string codedName = command.substr(0, command.find(", "));
	command.erase(0, command.find(", ") + 1);
	std::string species = command.substr(0, command.find(", "));
	command.erase(0, command.find(", ") + 1);
	int ageInMonths = stoi(command.substr(0, command.find(", ")));
	command.erase(0, command.find(", ") + 1);
	std::string digitizedscan = command.substr(0, command.find(", "));
	command.erase(0, command.find(", ") + 1);
	if (this->service.addPlant(codedName, species, ageInMonths, digitizedscan) == -1)
		cout << "This plant cluster already exists!\n";
	
}
void UI::ui_displayPlantClusters() {
	DynamicVector plants = this->service.getAllPlantClustersInRepo();
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

void UI::printMenu() {
	cout << "Please use the commands mentioned above:\n";
	cout << "   -> mode X\n";
	cout << "   -> add codedName, species, ageInMonths, digitizedScan\n";
	cout << "   -> update codedName, newSpecies, newAgeInMonths, newDigitizedScan\n";
	cout << "   -> delete codedName\n";
	cout << "   -> list\n";
	cout << "   -> exit\n";
	cout << "!!! Make sure you first initialize the mode: mode A\n";

}

void UI::initialPlantClusters() {
	this->service.initializePlantClusters();
}
void UI::run() {
	std::string mode;
	printMenu();
	initialPlantClusters();
	while (1) {
		std::string user_command;
		getline(cin, user_command);
		std::string ui_command= user_command.substr(0,user_command.find(" "));
		std::string parameters = user_command.substr(user_command.find(" ") + 1, sizeof(user_command));
		
		if (ui_command.compare("mode") == 0)
			mode = user_command;
		else if (ui_command.compare("add") == 0 && mode.compare("mode A")==0)
			ui_addPlantCluster(parameters);
		else if (ui_command.compare("list") == 0 && mode.compare("mode A") == 0)
			ui_displayPlantClusters();
		else if (ui_command.compare("update") == 0 && mode.compare("mode A") == 0)
			ui_updatePlantCluster(parameters);
		else if (ui_command.compare("delete") == 0 && mode.compare("mode A") == 0)
			ui_deletePlantCluster(parameters);
		else if (ui_command.compare("exit" ) == 0 )
			break;
	}
	
}