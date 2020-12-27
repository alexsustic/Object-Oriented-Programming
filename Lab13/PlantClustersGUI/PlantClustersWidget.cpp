#include "PlantClustersWidget.h"

PlantClustersWidget::PlantClustersWidget(PlantClusterTableModel* model, QWidget *parent)
	: QWidget(parent)
{
	this->model = model;
	ui.setupUi(this);
	ui.plantClusterTableView->setModel(this->model);
}

PlantClustersWidget::~PlantClustersWidget()
{
}
