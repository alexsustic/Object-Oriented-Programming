#include "Repository.h"
#include<string>
using namespace std;

RepoAssistant::RepoAssistant() {
    this->savedPlants = savedPlants;
}

/*Repository::Repository() {
    this->plantClusters = plantClusters;
}

int Repository::addPlantCluster(const PlantCluster& p)
{
    for (int i = 0; i < plantClusters.size(); i++)
        if (this->plantClusters.at(i).getCodedName() == p.getCodedName())
            return -1;
    this->plantClusters.push_back(p);
    return 0;
}

int Repository::updatePlantCluster(const PlantCluster& p) {

    for (int i=0 ; i< plantClusters.size(); i++)
        if (this->plantClusters.at(i).getCodedName() == p.getCodedName())
        { 
            this->plantClusters.at(i) = p;
            return 0;

        }
    return -1;
}

int Repository::deletePlantCluster(const std::string& codedName) {
    
    for (int i = 0; i < plantClusters.size(); i++)
        if (this->plantClusters.at(i).getCodedName() == codedName)
        {
           
            this->plantClusters.erase(this->plantClusters.begin() + i);
            return 0;

        }
    return -1;
}
*/
int RepoAssistant::savePlant(const PlantCluster& p) {

  for (int i = 0; i < this->savedPlants.size(); i++)
      if (this->savedPlants.at(i).getCodedName() == p.getCodedName())
          return -1;
  this->savedPlants.push_back(p);
  return 0;

}