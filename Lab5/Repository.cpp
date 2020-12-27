#include "Repository.h"
#include<string>
using namespace std;

int Repository::addPlantCluster(const PlantCluster& p) {
    if (this->plantClusters.exist(p.getCodedName()) == -1)
        this->plantClusters.add(p);
    else
        return -1;
}

int Repository::updatePlantCluster(const PlantCluster& p) {
    if (this->plantClusters.exist(p.getCodedName()) == 1)
        this->plantClusters.update(p);
    else
        return -1;
}

int Repository::deletePlantCluster(const std::string& codedName) {
    if (this->plantClusters.exist(codedName) == 1)
        this->plantClusters.remove(codedName);
    else
        return -1;
}