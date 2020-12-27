#pragma once
#include "FileRepository.h"
#include "Repository.h"
#include "SavedPlants.h"
#include <vector>
#include <iostream>
class Service {
private:
	FileRepo& repository;
	RepoAssistant repoAssistant;
	SavedPlants* savedPlants;

public:
	
	Service(FileRepo& r) : repository{ r } { this->savedPlants = nullptr; } 
	FileRepo& getRepo() const { return repository; }
    vector <PlantCluster> getAllPlantClustersInRepo() const;
	vector <PlantCluster> getAllPlants() const;
	void addPlant(const std::string& codedName, const std::string& species, const int& ageInMonths, const std::string& digitizedScan);
	void updatePlant(const std::string& codedName, const std::string& species, const int& ageInMonths, const std::string& digitizedScan);
	void deletePlant(const std::string& codedName);
	void initializePlantClusters();
	void service_save(const std::string& codedName);
	void setFileLocation(std::string& fileLocation);
	void setMyListLocation(std::string& fileLocation);
};