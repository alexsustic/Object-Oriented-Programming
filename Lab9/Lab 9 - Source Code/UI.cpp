#include "UI.h"
#include <string>
#include "Validator.h"
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
	this->service.addPlant(codedName, species, ageInMonths, digitizedscan);
		
	
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
	this->service.updatePlant(codedName, species, ageInMonths, digitizedscan);
		
}

void UI::ui_deletePlantCluster(std::string command) {
	this->service.deletePlant(command) ;
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
	cout << "Don't forget first to initialize the path before using any other commands !!!\n";
	cout << "For this, use the command <fullPath>\n";
	cout << "Please use the commands mentioned above:\n";
	cout << "   -> next\n";
	cout << "   -> save codedName(e.g.save I129)\n";
	cout << "   -> list species, age (e.g.list Solanum tuberosum, 2)\n";
	cout << "   -> mylist\n";
	cout << "   -> mylistLocation <fullPath>\n";
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
	this->service.service_save(codedName);
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

void UI::ui_mylistLocation(std::string file_location) {
	this->service.setMyListLocation(file_location);
	ofstream file;
	file.open(file_location);
	

}
void UI::administrator() {
	int file_open = 0;
	printMenu_administrator();
	std::string mode;
	while (1) {
		std::string user_command;
		getline(cin, user_command);
		std::string ui_command = user_command.substr(0, user_command.find(" "));
		std::string parameters = user_command.substr(user_command.find(" ") + 1, size(user_command));
		try {
			if (ui_command.compare("mode") == 0)
			{
				mode = user_command;
				if (mode.compare("mode B") == 0)
				{
					this->location_established = file_open;
					assistant();
					break;

				}
			}
			else if (ui_command.compare("fileLocation") == 0)
			{
				ui_fileLocation(parameters);
				initialPlantClusters();
				file_open = 1;
			}

			else if (ui_command.compare("add") == 0 && file_open == 1)
				ui_addPlantCluster(parameters);
			else if (ui_command.compare("list") == 0 && file_open == 1)
				ui_displayPlantClusters();
			else if (ui_command.compare("update") == 0 && file_open == 1)
				ui_updatePlantCluster(parameters);
			else if (ui_command.compare("delete") == 0 && file_open == 1)
				ui_deletePlantCluster(parameters);
			else if (ui_command.compare("exit") == 0)
				break;
			else if (ui_command.compare("add") != 0 && ui_command.compare("list") != 0 && ui_command.compare("update") != 0 && ui_command.compare("delete") != 0 && ui_command.compare("exit") != 0 && ui_command.compare("fileLocation") != 0 && ui_command.compare("mode") != 0 && ui_command.compare("") != 0)  {

				cout << "There is no such command !\n";
			}
			else if (ui_command.compare("") == 0)
				cout << "";
			else 
				cout << "Initialize the path first !\n";
		}
		catch (ValidationException & ex)
		{
			cout << ex.getMessage();
		}
		catch (Exceptions & ex)
		{
			cout << ex.getExceptionMessage();
		}
	}

}

void UI::assistant() {
	std::string mode;
	int file_open = 0;
	vector <PlantCluster> plantClusters = this->service.getAllPlantClustersInRepo();
	vector <PlantCluster>::iterator it = plantClusters.begin();
	printMenu_assistant();
	while (1) {
		std::string user_command;
		getline(cin, user_command);
		std::string parameters = user_command.substr(user_command.find(" ") + 1);
		std::string ui_command = user_command.substr(0, user_command.find(" "));
		
		try {
			if (ui_command.compare("mode") == 0)
			{
				mode = user_command;
				if (mode.compare("mode A") == 0)
				{
					administrator();
					break;
				}
			}
			if (ui_command.compare("next") == 0 && this->location_established == 1)
				ui_next(plantClusters, it);
			else if (ui_command.compare("mylistLocation") == 0)
			{
				ui_mylistLocation(parameters);
				file_open = 1;

			}
			else if (ui_command.compare("save") == 0 && file_open == 1)
				ui_save(parameters);
			else if (ui_command.compare("list") == 0 && this->location_established == 1)
				ui_list(parameters);
			else if (ui_command.compare("mylist") == 0 && file_open == 1)
				ui_mylist();
			else if (ui_command.compare("exit") == 0)
				break;
			else if (ui_command.compare("mode") != 0 && ui_command.compare("next") != 0 && ui_command.compare("mylistLocation") != 0 && ui_command.compare("save") != 0 && ui_command.compare("list") != 0 && ui_command.compare("mylist") != 0 && ui_command.compare("exit") != 0 && ui_command.compare("") != 0) {

				cout << "There is no such command !\n";
			}
			else if (ui_command.compare("") == 0)
				cout << "";
			else
			{
				cout << "Initialize the path first !\n";
				cout << "For next/list --> initialize the path from mode A\n";
				cout << "For save/mylist --> initialize the path from mode A and B\n";
			}
			
		}
		catch (Exceptions & ex)
		{
			cout << ex.getExceptionMessage();
		}
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