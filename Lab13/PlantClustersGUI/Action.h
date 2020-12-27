#pragma once
#include "FileRepository.h"
#include "PlantCluster.h"
class Action
{
public:
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;
	virtual ~Action() = default;

};

class ActionAdd : public Action {
private:
	PlantCluster addedPlant;
	FileRepo& repository;

public:
	ActionAdd(PlantCluster plant, FileRepo& repo);
	void executeUndo() override;
	void executeRedo() override;
};

class ActionRemove : public Action {
private:
	PlantCluster deletedPlant;
	FileRepo& repository;

public:
	ActionRemove(PlantCluster plant, FileRepo& repo);
	void executeUndo() override;
	void executeRedo() override;

};

class ActionUpdate : public Action {
private:
	PlantCluster oldPlant;
	PlantCluster newPlant;
	FileRepo& repository;
public:
	ActionUpdate(PlantCluster newPlant, PlantCluster oldPlant, FileRepo& repo);
	void executeUndo() override;
	void executeRedo() override;
};
