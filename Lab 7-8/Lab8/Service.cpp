#include "Service.h"

  vector <PlantCluster> Service::getAllPlantClustersInRepo() const {
	  return this->repository.getPlantClusters();
}

  vector <PlantCluster> Service::getAllPlants() const {
	return repoAssistant.getPlants();
}

int Service::addPlant(const std::string& codedName, const std::string& species, const int& ageInMonths, const std::string& digitizedScan) {
	PlantCluster plant{ codedName, species, ageInMonths, digitizedScan };
	return this->repository.addPlantCluster(plant);
}
int Service::updatePlant(const std::string & codedName, const std::string & species, const int& ageInMonths, const std::string & digitizedScan){
	PlantCluster plant {codedName, species, ageInMonths, digitizedScan};
	return this->repository.updatePlantCluster(plant);
}
int Service::deletePlant(const std::string& codedName) {
	return this->repository.deletePlantCluster(codedName);
}

int Service::service_save(const std::string& codedName) {
	PlantCluster found_plant;
	vector <PlantCluster> plants = this->getAllPlantClustersInRepo();
	for (int index=0; index< plants.size(); index++)
		if (plants.at(index).getCodedName() == codedName)
		{
		    found_plant = plants.at(index);
			break;
		}
	return this->repoAssistant.savePlant(found_plant);
}

void Service::initializePlantClusters() {
	PlantCluster plant_1{"1ab", "Gentiana pumila", 1, "aaabbb"};
	PlantCluster plant_2{"D2c", "Drosera anglica", 5, "bbbccc"};
	PlantCluster plant_3{"11c", "Gerenium molle", 6, "dddfbb"};
	PlantCluster plant_4{"22a", "Allium Ursinum", 18, "aaaggg"};
	PlantCluster plant_5{"3rf", "Gentiana pumila", 10, "mmmnnn"};
	PlantCluster plant_6{"ac5", "Bellis perennis", 2, "hhhiii"};
	PlantCluster plant_7{"lt1", "Calluna vulgaris", 8, "eeeccc"};
	PlantCluster plant_8{"ca1", "Gentiana pumila", 3, "xrtxrt"};
	PlantCluster plant_9{"cv4", "Clematis vitalba", 4, "dddlll"};
	PlantCluster plant_10{"d4c", "Daphne cneorum", 11, "pppooo"};
	this->repository.addPlantCluster(plant_1);
	this->repository.addPlantCluster(plant_2);
	this->repository.addPlantCluster(plant_3);
	this->repository.addPlantCluster(plant_4);
	this->repository.addPlantCluster(plant_5);
	this->repository.addPlantCluster(plant_6);
	this->repository.addPlantCluster(plant_7);
	this->repository.addPlantCluster(plant_8);
	this->repository.addPlantCluster(plant_9);
	this->repository.addPlantCluster(plant_10);
}

void Service::setFileLocation(std::string& fileLocation) {
	this->repository.setLocation(fileLocation);
}

