#include "Service.h"
#include "PlantCluster.h"
#include "Repository.h"
#include "UnitTest.h"
#include <assert.h>


void testPlantCluster() {
	PlantCluster plant{ "1ab","drosophila",4,"aaabbbccc" };
	assert(plant.getCodedName()=="1ab");
	assert(plant.getSpecies() == "drosophila");
	assert(plant.getAgeInMonths() == 4);
	assert(plant.getDigitizedScan() == "aaabbbccc");
	PlantCluster p1{ "1","1",1,"1" };
	assert(p1.toString() == "Coded Name: 1 || Species: 1 || Age in months: 1 || Digitized Scan: 1");
	PlantCluster p;
	assert(p.getAgeInMonths() == 0);
	assert(p == p);
}

void testAddService(){
	string textFile = "file.txt";
	FileRepo testRepo{};
	Repository repo{};
	Service testService{ testRepo,repo };
	testService.setFileLocation(textFile);
	PlantCluster s{ "abc", "def", 123, "ghi" };
	testService.addPlant("abc", "def", 123, "ghi");
	vector <PlantCluster> test = testService.getAllPlantClustersInRepo();
	assert(test.at(0).getCodedName()=="abc");
	testService.updatePlant("abc", "abc", 1, "abc");
	vector <PlantCluster> test1 = testService.getAllPlantClustersInRepo();
	assert(test.at(0).getCodedName() == "abc");
	assert(test.at(0).getAgeInMonths() == 1);

}
void testSave()
{
	string textFile = "file1.txt";
	FileRepo testRepo{};
	Repository repo{};
	Service testService{ testRepo, repo };
	testService.setFileLocation(textFile);
	PlantCluster s1{ "abc", "def", 123, "ghi" };
	PlantCluster s2{ "aaa", "aaa", 1, "aaa" };
	testRepo.addPlantCluster(s1);
	testRepo.addPlantCluster(s2);
	vector <PlantCluster> plants = testRepo.getPlantClusters();
	assert(plants.size() == 2);
	assert(plants.at(0).getAgeInMonths() == plants.at(0).getAgeInMonths());
	testService.service_save("abc");
	vector<PlantCluster> plants1 = testService.getAllPlants();
	assert(plants1.at(0).getAgeInMonths() == s1.getAgeInMonths());
	assert(plants1.size() == 1);
	testService.service_save("aaa");
	plants1 = testService.getAllPlants();
	assert(plants1.at(1).getAgeInMonths() == s2.getAgeInMonths());
	assert(plants1.size() == 2);
}

void testAdd()
{
	string textFile = "file2.txt";
	FileRepo testRepo{};
	Repository repo{};
	Service testService{ testRepo,repo };
	testService.setFileLocation(textFile);
	PlantCluster s{ "abc", "def", 123, "ghi" };
	testRepo.addPlantCluster(s);
	vector<PlantCluster> test = testRepo.getPlantClusters();
	assert(test.size() == 1);
}

void testDelete()
{
	string textFile = "file12.txt";
	FileRepo testRepo{};
	Repository repo{};
	Service testService{ testRepo,repo };
	testService.setFileLocation(textFile);
	PlantCluster s{ "abc", "def", 123, "ghi" };
	testRepo.addPlantCluster(s);
	vector<PlantCluster> test = testRepo.getPlantClusters();
	assert(test.size() == 1);
	testRepo.deletePlantCluster("abc");
	test = testRepo.getPlantClusters();
	assert(test.size() == 0);
	
}

void testDeleteRepo()
{
	string textFile = "file8.txt";
	FileRepo testRepo{};
	Repository repo{};
	Service testService{ testRepo,repo};
	testRepo.setLocation(textFile);
	PlantCluster d1{ "aa","bb",2,"cc" };
	PlantCluster d2{ "bb", "cc",3, "dd" };
	PlantCluster d3{ "cc", "dd", 5, "ff" };
	testRepo.addPlantCluster(d1);
	testRepo.addPlantCluster(d2);
	testRepo.addPlantCluster(d3);
	testRepo.deletePlantCluster("cc");
	vector <PlantCluster> plants = testRepo.getPlantClusters();
	assert(plants.size() == 2);

}

void testUpdate()
{
	string textFile = "file5.txt";
	FileRepo testRepo{};
	Repository repo{};
	Service testService{ testRepo,repo };
	testService.setFileLocation(textFile);
	PlantCluster d{};
	PlantCluster s{ "abc", "def", 123, "ghi" };
	testRepo.addPlantCluster(s);
	assert(s.getAgeInMonths() == 123);
	assert(s.getSpecies() == "def");
	PlantCluster s1{ "abc" , "aaa", 100, "aaa" };
	testRepo.updatePlantCluster(s1);
	assert(s1.getAgeInMonths() == 100);
	assert(s1.getSpecies() == "aaa");
	vector <PlantCluster> plants = testRepo.getPlantClusters();
	PlantCluster sTest = plants.at(0);
	assert(sTest.getAgeInMonths() == 100);
	assert(sTest.getSpecies() == "aaa");
}

void testDeleteService() {
	string textFile = "file.txt";
	FileRepo testRepo{};
	Repository repo{};
	Service testService{ testRepo,repo };
	testService.addPlant("1", "1", 1, "1");
	testService.deletePlant("1");
	vector <PlantCluster> d1 = testRepo.getPlantClusters();
	assert(d1.size() == 0);
	
}

void testInitializeService() {
	string textFile = "file6.txt";
	FileRepo testRepo{};
	Repository repo{};
	Service testService{ testRepo,repo };
	testService.initializePlantClusters();
	vector <PlantCluster> d1 = testRepo.getPlantClusters();
	assert(d1.size() == 0);
}

void runAllTests() {
	testPlantCluster();
	testAddService();
	testSave();
	testAdd();
	testDelete();
	testUpdate();
	testDeleteService();
	testInitializeService();
	testDeleteRepo();

}
