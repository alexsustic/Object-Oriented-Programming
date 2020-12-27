#pragma once
///#include"DynamicVector.h"
#include "PlantCluster.h"
#include <vector>
#include <iostream>

using namespace std;
class Repository {

private:
	vector <PlantCluster> plantClusters;
	vector <PlantCluster>::iterator it = plantClusters.begin();

public:
	
	Repository();
	void addPlantCluster(const PlantCluster& p);
	int updatePlantCluster(const PlantCluster& p);
	int deletePlantCluster(const std::string& codedName);
	vector <PlantCluster> getPlantCrusts() const { return plantClusters; }
};

class RepoAssistant {
private:
	vector <PlantCluster> savedPlants;
public:
	RepoAssistant();
	int savePlant(const PlantCluster& p);
	vector <PlantCluster> getPlants() const { return savedPlants; }
};