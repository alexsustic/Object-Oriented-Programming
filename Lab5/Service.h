#pragma once
#include "Repository.h"
class Service {
private:
	Repository& repository;
public:
	Service(Repository& r) : repository{ r } {}
	Repository& getRepo() const { return repository; }
	DynamicVector getAllPlantClustersInRepo() const;
	int addPlant(const std::string& codedName, const std::string& species, const int& ageInMonths, const std::string& digitizedScan);
	int updatePlant(const std::string& codedName, const std::string& species, const int& ageInMonths, const std::string& digitizedScan);
	int deletePlant(const std::string& codedName);
	void initializePlantClusters();
};