#include "Repository.h"
#include "Service.h"
#include "UI.h"
#include "DynamicVector.h"
#include <crtdbg.h>

int main()
{
	DynamicVector* dynamicVector = createVector(10);
	Repository* repo = createRepository(dynamicVector);
	Service* service = createService(repo);
	Console* console = createConsole(service);
	run(console);
	_CrtDumpMemoryLeaks();
	return 0;
}