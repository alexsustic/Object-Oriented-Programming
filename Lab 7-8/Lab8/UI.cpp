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
	vector <PlantCluster> plants = this->service.getAllPlantClustersInRepo();
	for (int index = 0; index < plants.size(); index++) {
		PlantCluster plantCluster = plants.at(index);
		cout << plantCluster.toString() << "\n";
	}
}

void UI::ui_updatePlantCluster(std::string command) {
	std::string codedName = command.substr(0, command.find(", "));
	command.erase(0, command.find(", ") + 1);
	std::string species = command.substr(0, command.find(", "));
	command.erase(0, command.find(", ") + 1);
	species = species.erase(0, 1);
	int ageInMonths = stoi(command.substr(0, command.find(", ")));
	command.erase(0, command.find(", ") + 1);
	std::string digitizedscan = command.substr(0, command.find(", "));
	command.erase(0, command.find(", ") + 1);
	digitizedscan.erase(0, 1);
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
	cout << "   -> fileLocation <fullPath>\n";
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

void UI::ui_next( vector <PlantCluster> &plantCluster, vector <PlantCluster>::iterator &it) {
	
	if (plantCluster.begin() == plantCluster.end())
		cout << "No plant cluster found! \n";

	if (it == plantCluster.end())
	{
		it = plantCluster.begin();
		cout << (*it).toString()<<"\n";
		++it;
	}
	else if (it != plantCluster.end())
	{
		cout << (*it).toString()<<"\n";
		++it;
		
	}

}

void UI::ui_save(std::string command) {
	std::string codedName = command.substr(0, command.find(", "));
	if (this->service.service_save(codedName) == -1)
		cout << "Inexisting plant cluster!";
}

void UI::ui_mylist() {
	vector <PlantCluster>plants = this->service.getAllPlants();
	for (int index = 0; index < plants.size(); index++)
	{
		PlantCluster plant = plants.at(index);
		cout << plant.toString() << endl;
	}
}

void UI::ui_list(std::string command) {
	int ageInMonths;
	std::string first_parameter = command.substr(0, command.find(", "));
	command.erase(0, command.find(", ") + 1);
	char* p;
	vector<PlantCluster> plants = this->service.getAllPlantClustersInRepo();

	strtol(first_parameter.c_str(), &p, 10);
	if (*p == 0) {
		ageInMonths = stoi(first_parameter);
		for (int i = 0; i < plants.size(); i++)
			if (plants.at(i).getAgeInMonths() < ageInMonths)
				cout << plants.at(i).toString() << endl;
	}
	else
	{
		ageInMonths= stoi(command.substr(0, command.find(", ")));
		for (int i = 0; i < plants.size(); i++)
			if (plants.at(i).getAgeInMonths() < ageInMonths && plants.at(i).getSpecies()==first_parameter)
				cout << plants.at(i).toString() << endl;
	}
	   
}

void UI::ui_fileLocation(std::string file_location) {
	this->service.setFileLocation(file_location);
	ofstream file;
	file.open(file_location);
}
void UI::administrator() {
	printMenu_administrator();
	std::string mode;
	while (1) {
		std::string user_command;
		getline(cin, user_command);
		std::string ui_command = user_command.substr(0, user_command.find(" "));
		std::string parameters = user_command.substr(user_command.find(" ") + 1);
		if (ui_command.compare("mode") == 0)
		{
			mode = user_command;
			if (mode.compare("mode B") == 0)
			{
				assistant();
				break;
			}
		}
		else if (ui_command.compare("fileLocation") == 0)
		{
			ui_fileLocation(parameters);
			initialPlantClusters();
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
	vector <PlantCluster> plantClusters = this->service.getAllPlantClustersInRepo();
	vector <PlantCluster>::iterator it = plantClusters.begin();
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
			ui_next(plantClusters, it);
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
	cout << "!!! Do not forget to use first <fileLocation> function from mode A \n";
	cout << "Which mode would you like to choose?\n";
	cout << "<mode A> - administrator mode\n";
	cout << "<mode B> - assistant mode\n";
	///initialPlantClusters();
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