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
	DynamicVector<PlantCluster> dynamicVector;
	PlantCluster element;
	dynamicVector.add(element);
	assert(dynamicVector.getSize() == 1);
}


void testDeleteDynamicVector() {
	DynamicVector<PlantCluster> dynamicVector;
	PlantCluster first_element;
	PlantCluster second_element;
	dynamicVector.add(first_element);
	dynamicVector.add(second_element);
	dynamicVector.remove(first_element.getCodedName());
	assert(dynamicVector.getSize() == 1);
}


void testUpdateDynamicVector() {
	DynamicVector<PlantCluster> dynamicVector;
	PlantCluster plant{ "1ab", "ddd", 3,"ha" };
	PlantCluster updated_plant{ "1ab", "aaa", 5, "dd" };
	dynamicVector.add(plant);
	dynamicVector.update(updated_plant);
	PlantCluster new_plant = dynamicVector.getElement(0);
	assert(new_plant.getSpecies() == "aaa");
	assert(new_plant.getAgeInMonths() == 5);
	assert(new_plant.getDigitizedScan() == "dd");
}


void testExistDynamicVector() {
	DynamicVector<PlantCluster> dynamicVector;
	PlantCluster plant{ "1ab", "ddd", 3,"ha" };
	dynamicVector.add(plant);
	assert(dynamicVector.exist("1ab") == 1);
}

void testNextRepository() {
	Repository repo{};
	PlantCluster plant{ "12a", "drosophila", 4, "aabb" };
	repo.addPlantCluster(plant);
	assert(repo.repo_next().getSpecies() == "drosophila");
	assert(repo.repo_next().getCodedName() == "12a");
	assert(repo.repo_next().getAgeInMonths()== 4);
	assert(repo.repo_next().getDigitizedScan() == "aabb");
}

void testSaveRepoAssistant() {
	RepoAssistant repo{};
	PlantCluster plant{ "11a","Gentiana pumila", 6, "bbb" };
	repo.savePlant(plant);

	DynamicVector<PlantCluster> plants = repo.getPlants();
	PlantCluster plant_to_check = plants.getElement(0);
	assert(plant_to_check.getCodedName() == "11a");
	assert(plant_to_check.getSpecies() == "Gentiana pumila");
	assert(plant_to_check.getAgeInMonths() == 6);
	assert(plant_to_check.getDigitizedScan() == "bbb");
}

void testAddService() {
	Repository repo{};
	Service service{ repo };
	service.addPlant("13c", "magnolia", 10, "aca");
	DynamicVector <PlantCluster> plants = repo.getPlantCrusts();
	PlantCluster plant_to_check = plants.getElement(0);
	assert(plant_to_check.getCodedName() == "13c");
	assert(plant_to_check.getSpecies() == "magnolia");
	assert(plant_to_check.getAgeInMonths()==10);
	assert(plant_to_check.getDigitizedScan()=="aca");


}

void testDeleteService() {

	Repository repo{};
	Service service{ repo };
	service.addPlant("13c", "magnolia", 10, "aca");
	service.deletePlant("13c");
	DynamicVector <PlantCluster> plants = repo.getPlantCrusts();
	assert(plants.getSize() == 0);

}

void testUpdateService() {
	Repository repo{};
	Service service{ repo };
	service.addPlant("12a", "plant", 7, "abb");
	service.updatePlant("12a", "drosophila", 9, "bbb");
	DynamicVector <PlantCluster> plants = repo.getPlantCrusts();
	PlantCluster plant_to_check = plants.getElement(0);
	assert(plant_to_check.getCodedName() == "12a");
	assert(plant_to_check.getSpecies() == "drosophila");
	assert(plant_to_check.getAgeInMonths() == 9);
	assert(plant_to_check.getDigitizedScan() == "bbb");



}

void runAllTests() {
	testPlantCluster();
	testAddDynamicVector();
	testDeleteDynamicVector();
	testUpdateDynamicVector();
	testExistDynamicVector();
	testNextRepository();
	testSaveRepoAssistant();
	testAddService();
	testDeleteService();
	testUpdateService();
}