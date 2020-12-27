#pragma once
#include"Service.h"

class UI {
private:
	int location_established = 0;
	Service service;
public:
	UI(const Service& s) : service(s) {}

	///run administrator mode
	void administrator();

	///run the application and set the mode
	void run();
	///add a plant cluster
	void ui_addPlantCluster(std::string command);

	///display all the plant clusters from dynamic vector
	void ui_displayPlantClusters();

	///update a plant cluster
	void ui_updatePlantCluster(std::string command);

	///delete a plant cluster
	void ui_deletePlantCluster(std::string command);

	///the assistant sees the next iterated entity
	void ui_next(vector <PlantCluster>& plantCluster, vector <PlantCluster>::iterator& it);

	///print the commands' menu for administrator mode
	void printMenu_administrator();

	///run assistant mode
	void assistant();

	///print the commands' menu for assistant mode
	void printMenu_assistant();

	///provides 10 entities in the dynamicVector
	void initialPlantClusters();

	///save the current iterated element in another repository for the assistant
	void ui_save(std::string command);

	///print the list of plant clusters selected by the assistant
	void ui_mylist();

	///display all the plant clusters of a given species, having an age less than a given number
	void ui_list(std::string command);
	void ui_fileLocation(std::string file_location);
	void ui_mylistLocation(std::string file_location);
	
};