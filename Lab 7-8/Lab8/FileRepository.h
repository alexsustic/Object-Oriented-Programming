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
	int addPlantCluster(PlantCluster& p);
	int updatePlantCluster(PlantCluster& p);
	int deletePlantCluster(const string& codedName);
	vector <PlantCluster> getPlantClusters();
	void setLocation(string& path);
	
};