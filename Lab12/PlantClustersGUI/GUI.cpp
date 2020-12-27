#include "GUI.h"
#include <qlayout.h>
#include <qformlayout.h>
#include <qgridlayout.h>
#include <qmessagebox.h>
#include "Validator.h"
#include <qlabel.h>

GUI::GUI(Service& s) : serv{ s }
{
	this->initGUI();
	this->connectsSignalsAndSlots();
}

void GUI::initGUI()
{
	this->plantClusterListWidget = new QListWidget{};

	this->codedNameLineEdit = new QLineEdit{};
	this->speciesLineEdit = new QLineEdit{};
	this->ageInMonthsLineEdit =  new QLineEdit{};
	this->digitizedScanLineEdit = new QLineEdit{};
	this->fileLocationLineEdit = new QLineEdit{};
	this->myListLocationLineEdit = new QLineEdit{};

	this->addButton = new QPushButton{"Add"};
	this->deleteButton = new QPushButton{"Delete"};
	this->updateButton = new QPushButton{ "Update" };
	this->listButton = new QPushButton{ "List" };
	this->fileLocationButton = new QPushButton{ "File Location" };
	this->modeAButton = new QPushButton{ "Mode A" };
	this->modeBButton = new QPushButton{ "Mode B" };
	this->nextButton = new QPushButton{ "Next" };
	this->saveButton = new QPushButton{ "Save" };
	this->myListButton = new QPushButton{ "MyList" };
	this->myListLocationButton = new QPushButton{ "MyListLocation" };

	this->modeALabel = new QLabel{"\n Mode A (Administrator) : \n "};
	this->modeBLabel = new QLabel{ " \n Mode B (Assistant) : \n" };
	this->spaceLabel = new QLabel{ "\n" };

	QVBoxLayout* mainLayout = new QVBoxLayout{ this };

	mainLayout->addWidget(this->plantClusterListWidget);

	QFormLayout* plantClusterDetailsLayout = new QFormLayout{};
	
	plantClusterDetailsLayout->addRow("CodedName", this->codedNameLineEdit);
	plantClusterDetailsLayout->addRow("Species", this->speciesLineEdit);
	plantClusterDetailsLayout->addRow("AgeInMonths", this->ageInMonthsLineEdit);
	plantClusterDetailsLayout->addRow("DigitizedScan", this->digitizedScanLineEdit);
	plantClusterDetailsLayout->addRow("FileLocation", this->fileLocationLineEdit);
	plantClusterDetailsLayout->addRow("MyListFileLocation", this->myListLocationLineEdit);

	mainLayout->addLayout(plantClusterDetailsLayout);

	QGridLayout* buttonsLayout = new QGridLayout{};
	buttonsLayout->addWidget(this->addButton, 0, 0);
	buttonsLayout->addWidget(this->deleteButton, 0, 1);
	buttonsLayout->addWidget(this->updateButton, 0, 2);
	buttonsLayout->addWidget(this->listButton, 1, 0);
	buttonsLayout->addWidget(this->fileLocationButton, 1, 1);


	QGridLayout* modeButtonLayout = new QGridLayout{};
	modeButtonLayout->addWidget(this->modeAButton, 0, 0);
	modeButtonLayout->addWidget(this->modeBButton, 0, 1);

	QGridLayout* assistantLayout = new QGridLayout{};
	assistantLayout->addWidget(this->nextButton, 0, 0);
	assistantLayout->addWidget(this->saveButton, 0, 1);
	assistantLayout->addWidget(this->myListButton, 0, 2);
	assistantLayout->addWidget(this->myListLocationButton, 1, 0);

	mainLayout->addWidget(spaceLabel);
	mainLayout->addLayout(modeButtonLayout);
	mainLayout->addWidget(modeALabel);
	mainLayout->addLayout(buttonsLayout);
	mainLayout->addWidget(modeBLabel);
	mainLayout->addLayout(assistantLayout);

		



}

void GUI::populateList() {
	if (this->serv.repo_type.compare("file") == 0) {

		if (this->fileOpen == 1 && this->modeA == 1) {
			this->plantClusterListWidget->clear();
			vector <PlantCluster> plants = this->serv.getAllPlantClustersInRepo();
			for (PlantCluster& p : plants)
				this->plantClusterListWidget->addItem(QString::fromStdString("CodedName: " + p.getCodedName() + " // " + " Species: " + p.getSpecies() + " // " + " AgeInMonths: " + std::to_string(p.getAgeInMonths()) + " // " + " DigitizedScan: " + p.getDigitizedScan()));
		}
		else if (this->modeA == 0)
			QMessageBox::critical(this, "Error", "For this action you need to activate mode A!");
		else
			QMessageBox::critical(this, "Error", "You must first initialize the path using FileLocation button!");
	}
	else if (this->serv.repo_type.compare("in memory") == 0) 
	{

		if (this->modeA == 1) {
			this->plantClusterListWidget->clear();
			vector <PlantCluster> plants = this->serv.getAllPlantClustersInRepo();
			for (PlantCluster& p : plants)
				this->plantClusterListWidget->addItem(QString::fromStdString("CodedName: " + p.getCodedName() + " // " + " Species: " + p.getSpecies() + " // " + " AgeInMonths: " + std::to_string(p.getAgeInMonths()) + " // " + " DigitizedScan: " + p.getDigitizedScan()));
		}
		else if (this->modeA == 0)
			QMessageBox::critical(this, "Error", "For this action you need to activate mode A!");

	}

}

void GUI::connectsSignalsAndSlots()
{
	QObject::connect(this->plantClusterListWidget, &QListWidget::itemSelectionChanged, [this]() {
		int selectedIndex = getSelectedIndex();

		if (selectedIndex < 0)
			return;
		PlantCluster p = serv.getAllPlantClustersInRepo()[selectedIndex];
		codedNameLineEdit->setText(QString::fromStdString(p.getCodedName()));
		speciesLineEdit->setText(QString::fromStdString(p.getSpecies()));
		ageInMonthsLineEdit->setText(QString::fromStdString(std::to_string(p.getAgeInMonths())));
		digitizedScanLineEdit->setText(QString::fromStdString(p.getDigitizedScan()));

		});

	QObject::connect(this->listButton, &QPushButton::clicked, this, &GUI::populateList);
	QObject::connect(this->fileLocationButton, &QPushButton::clicked, this , &GUI::fileLocation);
	QObject::connect(this->addButton, &QPushButton::clicked, this, &GUI::addPlant);
	QObject::connect(this->updateButton, &QPushButton::clicked, this, &GUI::updatePlant);
	QObject::connect(this->deleteButton, &QPushButton::clicked, this, &GUI::deletePlant);
	QObject::connect(this->modeAButton, &QPushButton::clicked, this, &GUI::setmodeA);
	QObject::connect(this->modeBButton, &QPushButton::clicked, this, &GUI::setModeB);
	QObject::connect(this->myListLocationButton, &QPushButton::clicked, this, &GUI::myListLocation);
	QObject::connect(this->nextButton, &QPushButton::clicked, this, &GUI::next);
	QObject::connect(this->saveButton, &QPushButton::clicked, this, &GUI::save);
	QObject::connect(this->myListButton, &QPushButton::clicked, this, &GUI::myList);

}

int GUI::getSelectedIndex()
{
	QModelIndexList selectedIndexes = this->plantClusterListWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.size() == 0)
	{

		this->codedNameLineEdit->clear();
		this->speciesLineEdit->clear();
		this->ageInMonthsLineEdit->clear();
		this->digitizedScanLineEdit->clear();
		return -1;
	}

	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
}

void GUI::fileLocation()
{
	if (this->serv.repo_type.compare("file") == 0) {
		if (modeA == 1) {
			string path = this->fileLocationLineEdit->text().toStdString();
			if (path == "")
			{
				QMessageBox::critical(this, "Error", "Your fileLocation tab is empty !");
				return;
			}
			this->serv.setFileLocation(path);
			this->serv.initializePlantClusters();
			this->fileLocationLineEdit->clear();
			this->fileOpen = 1;
		}
		else
		{
			QMessageBox::critical(this, "Error", "For this action you need to activate mode A !");
		}
	}
	else if (this->serv.repo_type.compare("in memory") == 0)
	{

		this->fileLocationLineEdit->clear();
		QMessageBox::critical(this, "Error", "You are using in memory version and you no longer need this function!");

	}
}

void GUI::addPlant()
{
	if (this->serv.repo_type.compare("file") == 0)
	{
		if (this->fileOpen == 1 && modeA == 1) {
			string codedName = this->codedNameLineEdit->text().toStdString();
			string species = this->speciesLineEdit->text().toStdString();
			string digitizedScan = this->digitizedScanLineEdit->text().toStdString();
			if (codedName == "" || species == "" || digitizedScan == "" || this->ageInMonthsLineEdit->text().toStdString().size() == 0)
			{
				QMessageBox::critical(this, "Error", "Your tabs are empty !");
				return;
			}

			int ageInMonths = stoi(this->ageInMonthsLineEdit->text().toStdString());
			try {
				this->serv.addPlant(codedName, species, ageInMonths, digitizedScan);
			}
			catch (Exceptions & ex)
			{
				QMessageBox::critical(this, "Error", QString::fromStdString(ex.getExceptionMessage()));

			}
			this->codedNameLineEdit->clear();
			this->speciesLineEdit->clear();
			this->ageInMonthsLineEdit->clear();
			this->digitizedScanLineEdit->clear();
		}
		else if (modeA == 0)
			QMessageBox::critical(this, "Error", "For this action you need to activate mode A !");

		else
			QMessageBox::critical(this, "Error", " You must first initialize the path using fileLocation button! ");
	}
	else if (this->serv.repo_type.compare("in memory") == 0)
	{
		if (modeA == 1) {
			string codedName = this->codedNameLineEdit->text().toStdString();
			string species = this->speciesLineEdit->text().toStdString();
			string digitizedScan = this->digitizedScanLineEdit->text().toStdString();
			if (codedName == "" || species == "" || digitizedScan == "" || this->ageInMonthsLineEdit->text().toStdString().size() == 0)
			{
				QMessageBox::critical(this, "Error", "Your tabs are empty !");
				return;
			}

			int ageInMonths = stoi(this->ageInMonthsLineEdit->text().toStdString());
			try {
				this->serv.addPlant(codedName, species, ageInMonths, digitizedScan);
			}
			catch (Exceptions & ex)
			{
				QMessageBox::critical(this, "Error", QString::fromStdString(ex.getExceptionMessage()));

			}
			this->codedNameLineEdit->clear();
			this->speciesLineEdit->clear();
			this->ageInMonthsLineEdit->clear();
			this->digitizedScanLineEdit->clear();
		}
		else if (modeA == 0)
			QMessageBox::critical(this, "Error", "For this action you need to activate mode A !");
	}
}

void GUI::updatePlant()
{
	if (this->serv.repo_type.compare("file") == 0) {

		if (this->fileOpen == 1 && modeA == 1) {
			string codedName = this->codedNameLineEdit->text().toStdString();
			string species = this->speciesLineEdit->text().toStdString();
			string digitizedScan = this->digitizedScanLineEdit->text().toStdString();
			if (codedName == "" || species == "" || digitizedScan == "" || this->ageInMonthsLineEdit->text().toStdString().size() == 0)
			{
				QMessageBox::critical(this, "Error", "Your tabs are empty !");
				return;
			}

			int ageInMonths = stoi(this->ageInMonthsLineEdit->text().toStdString());

			try {
				this->serv.updatePlant(codedName, species, ageInMonths, digitizedScan);
			}
			catch (Exceptions & ex)
			{
				QMessageBox::critical(this, "Error", QString::fromStdString(ex.getExceptionMessage()));

			}
			this->codedNameLineEdit->clear();
			this->speciesLineEdit->clear();
			this->ageInMonthsLineEdit->clear();
			this->digitizedScanLineEdit->clear();
		}
		else if (modeA == 0)
			QMessageBox::critical(this, "Error", "For this action you need to activate mode A !");

		else
			QMessageBox::critical(this, "Error", " You must first initialize the path using fileLocation button! ");
	}
	else if (this->serv.repo_type.compare("in memory") == 0) {

		if (modeA == 1) {
			string codedName = this->codedNameLineEdit->text().toStdString();
			string species = this->speciesLineEdit->text().toStdString();
			string digitizedScan = this->digitizedScanLineEdit->text().toStdString();
			if (codedName == "" || species == "" || digitizedScan == "" || this->ageInMonthsLineEdit->text().toStdString().size() == 0)
			{
				QMessageBox::critical(this, "Error", "Your tabs are empty !");
				return;
			}

			int ageInMonths = stoi(this->ageInMonthsLineEdit->text().toStdString());

			try {
				this->serv.updatePlant(codedName, species, ageInMonths, digitizedScan);
			}
			catch (Exceptions & ex)
			{
				QMessageBox::critical(this, "Error", QString::fromStdString(ex.getExceptionMessage()));

			}
			this->codedNameLineEdit->clear();
			this->speciesLineEdit->clear();
			this->ageInMonthsLineEdit->clear();
			this->digitizedScanLineEdit->clear();
		}
		else if (modeA == 0)
			QMessageBox::critical(this, "Error", "For this action you need to activate mode A !");
	}

}

void GUI::deletePlant()
{
	if (this->serv.repo_type.compare("file") == 0) {

		if (this->fileOpen == 1 && this->modeA == 1) {
			string codedName = this->codedNameLineEdit->text().toStdString();
			if (codedName == "")
			{
				QMessageBox::critical(this, "Error", "Your codedName tab is empty !");
				return;
			}

			try {
				this->serv.deletePlant(codedName);
			}
			catch (Exceptions & ex) {
				QMessageBox::critical(this, "Error", QString::fromStdString(ex.getExceptionMessage()));
			}
			this->codedNameLineEdit->clear();
		}
		else if (modeA == 0)
			QMessageBox::critical(this, "Error", "For this action you need to activate mode A !");

		else
			QMessageBox::critical(this, "Error", " You must first initialize the path using fileLocation button! ");
	}
	else if (this->serv.repo_type.compare("in memory") == 0) {

		if (this->modeA == 1) {
			string codedName = this->codedNameLineEdit->text().toStdString();
			if (codedName == "")
			{
				QMessageBox::critical(this, "Error", "Your codedName tab is empty !");
				return;
			}

			try {
				this->serv.deletePlant(codedName);
			}
			catch (Exceptions & ex) {
				QMessageBox::critical(this, "Error", QString::fromStdString(ex.getExceptionMessage()));
			}
			this->codedNameLineEdit->clear();
		}
		else if (modeA == 0)
			QMessageBox::critical(this, "Error", "For this action you need to activate mode A !");
	}
}

void GUI::setmodeA()
{
	this->modeA = 1;
	this->modeB = 0;
}

void GUI::setModeB()
{
	this->modeA = 0;
	this->modeB = 1;
	this->currentIndex = 0;
}

void GUI::next()
{
	if (this->serv.repo_type.compare("file") == 0) {
		if (this->modeB == 1 && this->fileOpen == 1) {
			vector <PlantCluster> plants = this->serv.getAllPlantClustersInRepo();
			if (plants.size() != 0)
			{
				PlantCluster p = plants[this->currentIndex];
				if (this->currentIndex == plants.size() - 1)
				{
					this->plantClusterListWidget->clear();
					this->plantClusterListWidget->addItem(QString::fromStdString("CodedName: " + p.getCodedName() + " // " + " Species: " + p.getSpecies() + " // " + " AgeInMonths: " + std::to_string(p.getAgeInMonths()) + " // " + " DigitizedScan: " + p.getDigitizedScan()));
					this->currentIndex = 0;
				}
				else {

					this->plantClusterListWidget->clear();
					this->plantClusterListWidget->addItem(QString::fromStdString("CodedName: " + p.getCodedName() + " // " + " Species: " + p.getSpecies() + " // " + " AgeInMonths: " + std::to_string(p.getAgeInMonths()) + " // " + " DigitizedScan: " + p.getDigitizedScan()));
					this->currentIndex += 1;
				}

			}
			else
				QMessageBox::critical(this, "Error", "There are no plantClusters to iterate !");

		}
		else if (this->fileOpen == 0)
			QMessageBox::critical(this, "Error", "For this action you need to first set the fileLocation from mode A !");

		else
			QMessageBox::critical(this, "Error", "For this action you need to activate mode B !");

	}
	else if (this->serv.repo_type.compare("in memory") == 0) {
		if (this->modeB == 1) {
			vector <PlantCluster> plants = this->serv.getAllPlantClustersInRepo();
			if (plants.size() != 0)
			{
				PlantCluster p = plants[this->currentIndex];
				if (this->currentIndex == plants.size() - 1)
				{
					this->plantClusterListWidget->clear();
					this->plantClusterListWidget->addItem(QString::fromStdString("CodedName: " + p.getCodedName() + " // " + " Species: " + p.getSpecies() + " // " + " AgeInMonths: " + std::to_string(p.getAgeInMonths()) + " // " + " DigitizedScan: " + p.getDigitizedScan()));
					this->currentIndex = 0;
				}
				else {

					this->plantClusterListWidget->clear();
					this->plantClusterListWidget->addItem(QString::fromStdString("CodedName: " + p.getCodedName() + " // " + " Species: " + p.getSpecies() + " // " + " AgeInMonths: " + std::to_string(p.getAgeInMonths()) + " // " + " DigitizedScan: " + p.getDigitizedScan()));
					this->currentIndex += 1;
				}

			}
			else
				QMessageBox::critical(this, "Error", "There are no plantClusters to iterate !");

		}
		else
			QMessageBox::critical(this, "Error", "For this action you need to activate mode B !");

	}
}

void GUI::myListLocation()
{
	if (modeB == 1) {
		string path = this->myListLocationLineEdit->text().toStdString();
		if (path == "")
		{
			QMessageBox::critical(this, "Error", "Your MyListFileLocation tab is empty !");
			return;
		}
		this->serv.setMyListLocation(path);
		this->myListLocationLineEdit->clear();
		this->fileOpenAssistant = 1;
	}
	else
	{
		QMessageBox::critical(this, "Error", "For this action you need to activate mode B !");
	}
}

void GUI::save()
{
	if (this->modeB == 1 && this->fileOpenAssistant == 1) {
		int existence = 0;
		vector <PlantCluster> plants = this->serv.getAllPlantClustersInRepo();
		string codedName = this->codedNameLineEdit->text().toStdString();
		if (codedName == "")
		{
			QMessageBox::critical(this, "Error", "The codedName tab is empty!");
			return;
		}
		for (PlantCluster& p : plants)
			if (p.getCodedName() == codedName)
				existence = 1;
		if (existence == 0)
		{
			QMessageBox::critical(this, "Error", "This plant cluster doesn't exist !");
			return;
		}

		this->serv.service_save(codedName);
		this->codedNameLineEdit->clear();
	}
	else if (this->fileOpenAssistant == 0)
		QMessageBox::critical(this, "Error", "You must initalize the path using MyListLocation button !");
	else
		QMessageBox::critical(this, "Error", "You must activate mode B!");

}

void GUI::myList()
{
	if (this->modeB == 1 && this->fileOpenAssistant == 1)
	{
		vector <PlantCluster> plants = this->serv.getAllPlants();
		this->plantClusterListWidget->clear();
		for (PlantCluster& p : plants)
			this->plantClusterListWidget->addItem(QString::fromStdString("CodedName: " + p.getCodedName() + " // " + " Species: " + p.getSpecies() + " // " + " AgeInMonths: " + std::to_string(p.getAgeInMonths()) + " // " + " DigitizedScan: " + p.getDigitizedScan()));
	}
	else if(this->fileOpenAssistant == 0)
		QMessageBox::critical(this, "Error", "You must initalize the path using MyListLocation button !");
	else
		QMessageBox::critical(this, "Error", "You must activate mode B!");


}


