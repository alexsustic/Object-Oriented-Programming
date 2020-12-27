#include "PlantClustersGUI.h"
#include <QtWidgets/QApplication>
#include "FileRepository.h"
#include "Service.h"
#include "GUI.h"
#include "Repository.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FileRepo repo_file{};
	Repository repo_memory{};
	Service service{ repo_file, repo_memory };
	GUI gui{ service };
	gui.show();
    return a.exec();
}
