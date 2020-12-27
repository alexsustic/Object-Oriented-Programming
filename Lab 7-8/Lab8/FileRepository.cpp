#include "FileRepository.h"


FileRepo::FileRepo() {}

vector<PlantCluster>FileRepo::loadFromFile() {

	ifstream f(this->Path);
	vector <PlantCluster> plantClusters;
	PlantCluster p{};
	while (f >> p) {
		plantClusters.push_back(p);
	}
	f.close();
	return plantClusters;
}

void FileRepo::savePlantClusters(vector<PlantCluster> p) {
	ofstream g{ this->Path };
	for (const auto& plantCluster : p)
		g << plantCluster;
	g.close();

}

int FileRepo::addPlantCluster(PlantCluster& p) {
	vector <PlantCluster> plants = this->loadFromFile();
	for (const auto& plantCluster : plants)
		if (plantCluster.getCodedName() == p.getCodedName())
			return -1;
	plants.push_back(p);
	this->savePlantClusters(plants);
	return 0;

}

int FileRepo::updatePlantCluster(PlantCluster& p) {
	vector <PlantCluster> plants = this->loadFromFile();
	for ( auto& plantCluster : plants)
		if (plantCluster.getCodedName() == p.getCodedName())
		{
			plantCluster = p;
			this->savePlantClusters(plants);
			return 0;
		}
	return -1;

}

int FileRepo::deletePlantCluster(const string& codedName) {
	vector <PlantCluster> plants = this->loadFromFile();
	int position = 0;
	for (const auto& plantCluster : plants) {

		if (plantCluster.getCodedName() == codedName)
		{
			plants.erase(plants.begin()+ position);
			this->savePlantClusters(plants);
			return 0;
		}
		position += 1;
	}
	return -1;
}

void FileRepo::setLocation(string& path) {
	this->Path = path;
}

vector <PlantCluster> FileRepo::getPlantClusters() {
	vector <PlantCluster> plants = this->loadFromFile();
	return plants;
}