#include "PlantClustersGUI.h"
#include <QtWidgets/QApplication>
#include "FileRepository.h"
#include "Service.h"
#include "GUI.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	FileRepo repo{};
	Service service{ repo };

	GUI gui{service};
	gui.show();
    return a.exec();
}
