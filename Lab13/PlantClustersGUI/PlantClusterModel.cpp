#include "PlantClusterModel.h"

int PlantClusterTableModel::rowCount(const QModelIndex& parent) const
{
	return this->plants.size();
}

int PlantClusterTableModel::columnCount(const QModelIndex& parent) const
{
	return 4; // plantClusters have 4 attributes
}

QVariant PlantClusterTableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int col = index.column();
	PlantCluster current_plant = this->plants.at(row);

	if (role == Qt::DisplayRole) {

		switch (col) {
		case 0:
			return QString::fromStdString(current_plant.getCodedName());
		case 1:
			return QString::fromStdString(current_plant.getSpecies());
		case 2:
			return QString::number(current_plant.getAgeInMonths());
		case 3:
			return QString::fromStdString(current_plant.getDigitizedScan());
		default:
			break;
		}
	}



	return QVariant();
}

QVariant PlantClusterTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {

			switch (section)
			{
			case 0:
				return QString("Coded name");
			case 1:
				return QString("Species");
			case 2:
				return QString("Age in months");
			case 3:
				return QString("Digitized scan");
			default:
				break;
			}

		}
	}

	return QVariant();
}