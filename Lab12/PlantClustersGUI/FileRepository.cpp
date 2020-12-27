#include "FileRepository.h"
#include "Validator.h"

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

void FileRepo::addPlantCluster(PlantCluster& p) {
	vector <PlantCluster> plants = this->loadFromFile();
	for (const auto& plantCluster : plants)
		if (plantCluster.getCodedName() == p.getCodedName())
			throw RepoException("This plant cluster already exists!");
	plants.push_back(p);
	this->savePlantClusters(plants);


}

void FileRepo::updatePlantCluster(PlantCluster& p) {
	int existence = 0;
	vector <PlantCluster> plants = this->loadFromFile();
	for ( auto& plantCluster : plants)
		if (plantCluster.getCodedName() == p.getCodedName())
		{
			existence = 1;
			plantCluster = p;
			this->savePlantClusters(plants);
			
		}
	if (existence == 0) {
		throw RepoException("We can't find any plant cluster with this coded name!\n");
	}

}

void FileRepo::deletePlantCluster(const string& codedName) {
	vector <PlantCluster> plants = this->loadFromFile();
	int existence = 0;
	int position = 0;
	for (const auto& plantCluster : plants) {

		if (plantCluster.getCodedName() == codedName)
		{
			existence = 1;
			plants.erase(plants.begin()+ position);
			this->savePlantClusters(plants);
			
		}
		position += 1;
	}
	if (existence == 0)
		throw RepoException("We can't find any plant cluster with this coded name!\n");
}

void FileRepo::setLocation(string& path) {
	this->Path = path;
}

vector <PlantCluster> FileRepo::getPlantClusters() {
	vector <PlantCluster> plants = this->loadFromFile();
	return plants;
}