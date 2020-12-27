#include "Repository.h"
#include "Service.h"
#include "UI.h"

int main()
{

	Repository* repo = createRepository();
	Service* service = createService(repo);
	Console* console = createConsole(service);
	run(console);
	return 0;
}