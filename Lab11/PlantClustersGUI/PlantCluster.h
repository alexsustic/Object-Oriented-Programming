#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class PlantCluster {
private:
	std::string codedName;
	std::string species;
    int ageInMonths;
	std::string digitizedScan;
public:
	///default constructor
	PlantCluster();
	///constructor
	PlantCluster(const std::string& codedName, const std::string& species, const int& ageInMonths, const std::string& digitizedScan);
	///getters
	std::string getCodedName() const { return codedName; };
	std::string getSpecies() const { return species; };
	int getAgeInMonths()const { return ageInMonths; };
	std::string getDigitizedScan() const { return digitizedScan; };
	std::string toString();
	std::string write_in_html() const;
	vector <string> getParameters(const string& str, char separator);
	friend bool operator ==(const PlantCluster& p1, const PlantCluster& p2);
	friend ostream& operator <<(ostream& os, const PlantCluster& p);
	friend istream& operator >>(istream& is, PlantCluster& p);




};