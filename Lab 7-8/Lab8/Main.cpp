#include "UI.h"
#include "UnitTest.h"
using namespace std;

int main()
{
	    runAllTests();
		FileRepo repo{};
		Service service{ repo};
		UI console{ service };
		console.run();
		return 0;
}
