#include "PlantCluster.h"
#include <string>

PlantCluster::PlantCluster() :codedName(""), species(""), ageInMonths(0), digitizedScan("") {}

PlantCluster::PlantCluster(const std::string& codedName, const std::string& species,const int& ageInMonths, const std::string& digitizedScan){
    this->codedName = codedName;
    this->species = species;
    this->ageInMonths = ageInMonths;
    this->digitizedScan = digitizedScan;
}
 

std::string PlantCluster::toString() {

    return "Coded Name: " + this->codedName + " || " + "Species: " + this->species + " || " + "Age in months: " + std::to_string(this->ageInMonths) + " || " + "Digitized Scan: " + this->digitizedScan;
}
