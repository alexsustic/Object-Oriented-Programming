#include "Action.h"

ActionAdd::ActionAdd(PlantCluster plant, FileRepo& repo) : addedPlant(std::move(plant)), repository(repo) {}

void ActionAdd::executeUndo()
{
	this->repository.deletePlantCluster(addedPlant.getCodedName());
}

void ActionAdd::executeRedo()
{
	this->repository.addPlantCluster(addedPlant);
}

ActionRemove::ActionRemove(PlantCluster plant, FileRepo& repo) : deletedPlant(plant), repository(repo) {}

void ActionRemove::executeUndo()
{
	this->repository.addPlantCluster(deletedPlant);
}

void ActionRemove::executeRedo()
{
	this->repository.deletePlantCluster(deletedPlant.getCodedName());
}

ActionUpdate::ActionUpdate(PlantCluster newPlant, PlantCluster oldPlant, FileRepo& repo) : newPlant(newPlant), oldPlant(oldPlant), repository(repo) {}

void ActionUpdate::executeUndo()
{
	this->repository.updatePlantCluster(oldPlant);
}

void ActionUpdate::executeRedo()
{
	this->repository.updatePlantCluster(newPlant);
}
