#pragma once

#include <QAbstractTableModel>

#include "PlantCluster.h"

class PlantClusterTableModel : public QAbstractTableModel {
private:
	std::vector<PlantCluster> plants;
public:
	PlantClusterTableModel(std::vector<PlantCluster> plants) : plants{ plants } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

};