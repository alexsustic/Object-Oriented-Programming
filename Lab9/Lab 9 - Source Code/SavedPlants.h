#pragma once
#include <string>
#include "PlantCluster.h"

using namespace std;
class SavedPlants {
protected:
	string path;
public:
	SavedPlants() { };
	void add(const PlantCluster& p);
	void setPath(const std::string path);
	virtual void save_file(vector<PlantCluster> plantClusters) {};
	virtual std::vector<PlantCluster> load_file() { return std::vector<PlantCluster>(); };


};

class CSVMyList : public SavedPlants {
public:
	void save_file(vector <PlantCluster> plantClusters)override;
	std::vector <PlantCluster> load_file() override;

};

class HTMLMyList : public SavedPlants {
public:
	void save_file(vector <PlantCluster> plantClusters)override;
	std::vector <PlantCluster> load_file() override;

};