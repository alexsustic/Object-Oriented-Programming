#pragma once
#include "FileRepository.h"
#include "Repository.h"
#include <vector>
#include <iostream>
class Service {
private:
	FileRepo& repository;
	RepoAssistant repoAssistant;
public:
	
	Service(FileRepo& r) : repository{ r } {}
	FileRepo& getRepo() const { return repository; }
    vector <PlantCluster> getAllPlantClustersInRepo() const;
	vector <PlantCluster> getAllPlants() const;
	int addPlant(const std::string& codedName, const std::string& species, const int& ageInMonths, const std::string& digitizedScan);
	int updatePlant(const std::string& codedName, const std::string& species, const int& ageInMonths, const std::string& digitizedScan);
	int deletePlant(const std::string& codedName);
	void initializePlantClusters();
	int service_save(const std::string& codedName);
	void setFileLocation(std::string& fileLocation);
};