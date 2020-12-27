#include "Repository.h"
#include "Validator.h"
#include<string>
using namespace std;

RepoAssistant::RepoAssistant() {
    this->savedPlants = savedPlants;
}

Repository::Repository() {
    this->plantClusters = plantClusters;
}

void Repository::addPlantCluster(const PlantCluster& p)
{
    for (int i = 0; i < plantClusters.size(); i++)
        if (this->plantClusters.at(i).getCodedName() == p.getCodedName())
            throw RepoException("This plant cluster already exists!");
    this->plantClusters.push_back(p);
}

int Repository::updatePlantCluster(const PlantCluster& p) {

    int existence = 0;
    for (int i=0 ; i< plantClusters.size(); i++)
        if (this->plantClusters.at(i).getCodedName() == p.getCodedName())
        { 
            this->plantClusters.at(i) = p;
            existence = 1;

        }
    if (existence == 0)
        throw RepoException("This plant cluster doesn't exist !");
}

int Repository::deletePlantCluster(const std::string& codedName) {
    
    int existence = 0;
    for (int i = 0; i < plantClusters.size(); i++)
        if (this->plantClusters.at(i).getCodedName() == codedName)
        {
           
            this->plantClusters.erase(this->plantClusters.begin() + i);
            existence = 1;

        }
    if (existence == 0)
        throw RepoException("This plant cluster doesn't exist!");
}

int RepoAssistant::savePlant(const PlantCluster& p) {

  for (int i = 0; i < this->savedPlants.size(); i++)
      if (this->savedPlants.at(i).getCodedName() == p.getCodedName())
          return -1;
  this->savedPlants.push_back(p);
  return 0;

}