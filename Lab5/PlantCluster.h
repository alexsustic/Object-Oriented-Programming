#pragma once
#include <iostream>
#include<stdio.h>
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




};