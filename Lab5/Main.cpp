#include "PlantCluster.h"
#include "UI.h"
#include "UnitTest.h"
using namespace std;
int main()
{
	    runAllTests();
		Repository repo{};
		Service service{ repo };
		UI console{ service };
		console.run();
	
}
