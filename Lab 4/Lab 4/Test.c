#include "Service.h"
#include "Repository.h"
#include "Domain.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

void test_getSerialNumber_correctInput_serialNumberFound() {
	Bot bot;
	bot = createBot(100, "first_data", "second_data", 500);
	assert(getSerialNumber(&bot) == 100);
}

void test_getEnergyCostToRepair_correctInput_energyCostFound() {
	Bot bot;
	bot = createBot(200, "first_data", "second_data", 750);
	assert(getEnergyCostToRepair(&bot) == 750);
}

void test_addBot_validBot_botSuccesfullyAdded() {
	Repository* repo;
	Service* serv;
	DynamicVector* dynamicVector = createVector(15);
	repo = createRepository(dynamicVector);
	serv = createService(repo);
	service_addBot(serv, 200, "first_data", "second_data", 500);
	assert(repo->dynamicVector->size==1);
	free(repo);
	free(serv);
}

void runAllTests() {
	void test_getSerialNumber_correctInput_serialNumberFound();
	test_getEnergyCostToRepair_correctInput_energyCostFound();
	test_addBot_validBot_botSuccesfullyAdded();
}