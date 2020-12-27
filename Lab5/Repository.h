#pragma once
#include"DynamicVector.h"
class Repository {

private:
	DynamicVector plantClusters;
public:
	///default constructor
	Repository() {}

	int addPlantCluster(const PlantCluster& p);
	int updatePlantCluster(const PlantCluster& p);
	int deletePlantCluster(const std::string& codedName);
	DynamicVector getPlantCrusts() const { return plantClusters; }
};