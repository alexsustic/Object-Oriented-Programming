#include "Service.h"
#include "Validator.h"

vector <PlantCluster> Service::getAllPlantClustersInRepo() const {
	if (this->repo_type.compare("file") == 0)
		return this->repository.getPlantClusters();
	else if (this->repo_type.compare("in memory") == 0)
		return this->repo.getPlantCrusts();
}

  vector <PlantCluster> Service::getAllPlants() const {
	return this->savedPlants->load_file();
}

void Service::addPlant(const std::string& codedName, const std::string& species, const int& ageInMonths, const std::string& digitizedScan) {
	PlantCluster plant{ codedName, species, ageInMonths, digitizedScan };
	try {
		PlantClusterValidator::validateEntity(plant);
		
	}
	catch (ValidationException & ex)
	{
		throw ValidationException(ex);
	}
	if (this->repo_type.compare("file") == 0)
	{
		this->repository.addPlantCluster(plant);
		this->undoRedolist.resize(undoRedoIndex);
		undoRedolist.push_back(new ActionAdd(plant, this->repository));
		undoRedoIndex++;
	}
	else if (this->repo_type.compare("in memory") == 0)
		this->repo.addPlantCluster(plant);
}
void Service::updatePlant(const std::string & codedName, const std::string & species, const int& ageInMonths, const std::string & digitizedScan){
	PlantCluster plant{ codedName, species, ageInMonths, digitizedScan };
	try {
		PlantClusterValidator::validateEntity(plant);

	}
	catch (ValidationException & ex)
	{
		throw ValidationException(ex);
	}
	;
	if (this->repo_type.compare("file") == 0)
	{
		PlantCluster plant_to_update = this->repository.search(plant.getCodedName());
		this->repository.updatePlantCluster(plant);
		this->undoRedolist.resize(undoRedoIndex);
		this->undoRedolist.push_back(new ActionUpdate(plant, plant_to_update, this->repository));
		undoRedoIndex++;
	}
	else if (this->repo_type.compare("in memory") == 0)
		this->repo.updatePlantCluster(plant);
}
void Service::deletePlant(const std::string& codedName) {
	if (this->repo_type.compare("file") == 0)
	{   
		PlantCluster plantToDelete = this->repository.search(codedName);
		this->repository.deletePlantCluster(codedName);
		this->undoRedolist.resize(undoRedoIndex);
		this->undoRedolist.push_back(new ActionRemove(plantToDelete, this->repository));
		undoRedoIndex++;
	}
	else if (this->repo_type.compare("in memory") == 0)
		this->repo.deletePlantCluster(codedName);
}

void Service::service_save(const std::string& codedName) {
	PlantCluster found_plant;
	int existence = 0;
	vector <PlantCluster> plants = this->getAllPlantClustersInRepo();
	
	for (int index=0; index< plants.size(); index++)
		if (plants.at(index).getCodedName() == codedName)
		{
			existence = 1;
		    found_plant = plants.at(index);
			break;
		}

	if (existence == 0)
		throw ServiceException("You can't save a plant cluster that doesn't exist!");

	this->savedPlants->add(found_plant);
	
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

	if (this->repo_type.compare("file") == 0)
	{
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
	else if (this->repo_type.compare("in memory") == 0)
	{
		this->repo.addPlantCluster(plant_1);
		this->repo.addPlantCluster(plant_2);
		this->repo.addPlantCluster(plant_3);
		this->repo.addPlantCluster(plant_4);
		this->repo.addPlantCluster(plant_5);
		this->repo.addPlantCluster(plant_6);
		this->repo.addPlantCluster(plant_7);
		this->repo.addPlantCluster(plant_8);
		this->repo.addPlantCluster(plant_9);
		this->repo.addPlantCluster(plant_10);



	}
}

void Service::setFileLocation(std::string& fileLocation) {
	this->repository.setLocation(fileLocation);
}

void Service::setMyListLocation(std::string& fileLocation) {
	string extension = fileLocation.substr(fileLocation.size() - 4);
	if (extension.compare(".csv") == 0)
		this->savedPlants = new CSVMyList{};
	else if (extension.compare("html") == 0)
		this->savedPlants = new HTMLMyList{};
	this->savedPlants->setPath(fileLocation);

}

void Service::undo(bool storage)
{
	if (storage) {
		if (undoRedoIndex == 0) {
			throw ServiceException("No more undos");
		}
		undoRedolist[--undoRedoIndex]->executeUndo();
	}
}

void Service::redo(bool storage)
{
	if (storage) {
		if (undoRedoIndex == undoRedolist.size()) {
			throw ServiceException("No more redos");
		}
		undoRedolist[undoRedoIndex++]->executeRedo();
	}
}


