#pragma once

#include <QWidget>
#include "ui_PlantClustersWidget.h"
#include "PlantClusterModel.h"
class PlantClustersWidget : public QWidget
{
	Q_OBJECT
private:
	PlantClusterTableModel* model;
public:
	PlantClustersWidget(PlantClusterTableModel* model, QWidget *parent = Q_NULLPTR);
	~PlantClustersWidget();

private:
	Ui::PlantClustersWidget ui;
};
