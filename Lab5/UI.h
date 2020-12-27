#pragma once
#include"Service.h"

class UI {
private:
	Service service;
public:
	UI(const Service& s) : service(s) {}

	void run();
	///add a plant cluster
	void ui_addPlantCluster(std::string command);

	///display all the plant clusters from dynamic vector
	void ui_displayPlantClusters();

	///update a plant cluster
	void ui_updatePlantCluster(std::string command);

	///delete a plant cluster
	void ui_deletePlantCluster(std::string command);

	///print the commands' menu
	void printMenu();

	void initialPlantClusters();

};