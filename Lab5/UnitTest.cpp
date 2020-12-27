#include "Service.h"
#include "PlantCluster.h"
#include "Repository.h"
#include "DynamicVector.h"
#include "UnitTest.h"
#include <assert.h>


void testPlantCluster() {
	PlantCluster plant{ "1ab","drosophila",4,"aaabbbccc" };
	assert(plant.getCodedName()=="1ab");
	assert(plant.getSpecies() == "drosophila");
	assert(plant.getAgeInMonths() == 4);
	assert(plant.getDigitizedScan() == "aaabbbccc");
}


void testAddDynamicVector() {
	DynamicVector dynamicVector;
	TElem element;
	dynamicVector.add(element);
	assert(dynamicVector.getSize() == 1);
}


void testDeleteDynamicVector() {
	DynamicVector dynamicVector;
	TElem first_element;
	TElem second_element;
	dynamicVector.add(first_element);
	dynamicVector.add(second_element);
	dynamicVector.remove(first_element.getCodedName());
	assert(dynamicVector.getSize() == 1);
}


void testUpdateDynamicVector() {
	DynamicVector dynamicVector;
	TElem plant{ "1ab", "ddd", 3,"ha" };
	TElem updated_plant{ "1ab", "aaa", 5, "dd" };
	dynamicVector.add(plant);
	dynamicVector.update(updated_plant);
	TElem new_plant = dynamicVector.getElement(0);
	assert(new_plant.getSpecies() == "aaa");
	assert(new_plant.getAgeInMonths() == 5);
	assert(new_plant.getDigitizedScan() == "dd");
}


void testExistDynamicVector() {
	DynamicVector dynamicVector;
	TElem plant{ "1ab", "ddd", 3,"ha" };
	dynamicVector.add(plant);
	assert(dynamicVector.exist("1ab") == 1);
}


void runAllTests() {
	testPlantCluster();
	testAddDynamicVector();
	testDeleteDynamicVector();
	testUpdateDynamicVector();
	testExistDynamicVector();
}