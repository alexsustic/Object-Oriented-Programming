#pragma once
#include "PlantCluster.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class FileRepo {
private:
	string Path;
	vector<PlantCluster> loadFromFile();
	void savePlantClusters(vector<PlantCluster> p);
	

public:
	FileRepo();
	void addPlantCluster(PlantCluster& p);
	void updatePlantCluster(PlantCluster& p);
	void deletePlantCluster(const string& codedName);
	vector <PlantCluster> getPlantClusters();
	void setLocation(string& path);
	PlantCluster FileRepo::search(std::string const codedName);
	
};