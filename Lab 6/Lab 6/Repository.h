#pragma once
#include"DynamicVector.h"
#include "PlantCluster.h"
class Repository {

private:
	DynamicVector<PlantCluster> plantClusters; 
	DynamicVector<PlantCluster>::iterator it= plantClusters.begin();

public:
	///default constructor
	Repository()
	{
	}

	int addPlantCluster(const PlantCluster& p);
	int updatePlantCluster(const PlantCluster& p);
	int deletePlantCluster(const std::string& codedName);
	DynamicVector<PlantCluster> getPlantCrusts() const { return plantClusters; }
	PlantCluster repo_next();
};

class RepoAssistant {
private:
	DynamicVector<PlantCluster> savedPlants;
public:
	RepoAssistant()
	{
	};
	int savePlant(const PlantCluster& p);
	DynamicVector<PlantCluster> getPlants() const { return savedPlants; }
};