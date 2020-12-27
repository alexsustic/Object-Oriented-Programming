#pragma once
#include "FileRepository.h"
#include "Repository.h"
#include "SavedPlants.h"
#include <vector>
#include <iostream>
class Service {
private:
	FileRepo& repository;
	Repository& repo;
	RepoAssistant repoAssistant;
	SavedPlants* savedPlants;
	

public:
	string repo_type;
	Service(FileRepo& r, Repository& re) : repository{ r }, repo{ re }{ 
	this->savedPlants = nullptr;
	ifstream f("Configuration.txt");
	getline(f, repo_type);
	if (repo_type.compare("in memory") == 0)
		initializePlantClusters();
	f.close();
	}

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