#include "SavedPlants.h"
#include <fstream>
#include "Validator.h"
#include <Windows.h>


void SavedPlants::add(const PlantCluster& p) {
	
	vector <PlantCluster> plantCluster = this->load_file();
	
	plantCluster.push_back(p);
	this->save_file(plantCluster);
};

void SavedPlants::setPath(const string path) {
	this->path = path;
};


vector <PlantCluster> CSVMyList::load_file() {

	vector <PlantCluster> plants;
	PlantCluster plantCluster{};
	ifstream file(this->path);
	while (file >> plantCluster)
		plants.push_back(plantCluster);
	file.close();
	return plants;

}
void CSVMyList::save_file(vector <PlantCluster> plantClusters) {
	ofstream file{ this->path };
	for (const auto& plant : plantClusters)
		file << plant;
	file.close();
  
}

void HTMLMyList::save_file(vector <PlantCluster> plantClusters) {

	ofstream file{ this->path };
	file << "<!DOCTYPE.html>\n<html>\n<head>\n<title>PlantClusters</title>\n</head>\n";
	file << "<body>\n<table border=\"1\"\n";
	file << "<tr>\n<td>CodedName</td>\n<td>Species</td>\n<td>AgeInMonths</td>\n<td>DigitizedScan</td>\n</tr>\n";
	for (const auto& plant : plantClusters)
		file << plant.write_in_html();
	file << "</table>\n</body>\n</html>\n";
	file.close();

}
vector <PlantCluster> HTMLMyList::load_file() {

	vector <PlantCluster> plants;
	string line;
	string codedName, species, ageInMonths, digitizedScan;
	ifstream file(this->path);
	for (int i = 0; i <= 12; i++)
		getline(file, line);
	getline(file, line); //which is going to be "<tr>"
	while (line == "<tr>") {
		getline(file, line);
		codedName = line.substr(4, line.size() - 5);
		getline(file, line);
		species = line.substr(4, line.size() - 5);
		getline(file, line);
		ageInMonths = line.substr(4, line.size() - 5);
		getline(file, line);
		digitizedScan = line.substr(4, line.size() - 5);
		PlantCluster p{ codedName, species, stoi(ageInMonths), digitizedScan };
		plants.push_back(p);
		getline(file, line);
		getline(file, line); //we move to the next "<tr>"
	}
	file.close();
	return plants;
}

