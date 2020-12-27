#include "PlantCluster.h"


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

vector <string> PlantCluster::getParameters(const string& str, char separator) {
    vector <string> parameters;
    stringstream ss(str);
    string token;
    while (getline(ss, token, separator))
        parameters.push_back(token);
    return parameters;

}

bool operator ==(const PlantCluster& p1, const PlantCluster& p2) {
    return
    {
      p1.getAgeInMonths() == p2.getAgeInMonths() &&
      p1.getCodedName() == p2.getCodedName() &&
      p1.getDigitizedScan() == p2.getDigitizedScan() &&
      p1.getSpecies() == p2.getSpecies()


    };
}

ostream& operator <<(ostream & os, const PlantCluster & p) {

    os << p.getCodedName() << "," << p.getSpecies() << "," << p.getAgeInMonths() << "," << p.getDigitizedScan()<<"\n";
    return os;
}

istream& operator >>(istream& is,  PlantCluster& p) {

    string read_line;
    getline(is, read_line);
    vector <string> parameters = p.getParameters(read_line, ',');
    if (parameters.size() != 4)
        return is;
    p.codedName = parameters[0];
    p.species = parameters[1];
    p.ageInMonths = stoi(parameters[2]);
    p.digitizedScan = parameters[3];
    return is;
    
}



