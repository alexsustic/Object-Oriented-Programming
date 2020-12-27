#pragma once
#include "Repository.h"
class Service {
private:
	Repository& repository;
	RepoAssistant repoAssistant;
public:
	
	Service(Repository& r) : repository{ r } {}
	Repository& getRepo() const { return repository; }
    DynamicVector<PlantCluster> getAllPlantClustersInRepo() const;
	DynamicVector<PlantCluster> getAllPlants() const;
	int addPlant(const std::string& codedName, const std::string& species, const int& ageInMonths, const std::string& digitizedScan);
	int updatePlant(const std::string& codedName, const std::string& species, const int& ageInMonths, const std::string& digitizedScan);
	int deletePlant(const std::string& codedName);
	void initializePlantClusters();
	PlantCluster service_next();
	int service_save(const std::string& codedName);
};