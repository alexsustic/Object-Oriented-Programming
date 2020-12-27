#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include "Service.h"

class GUI : public QWidget
{
private:
	int fileOpen = 0;
	int fileOpenAssistant = 0;
	int modeA = 0;
	int modeB = 0;
	int currentIndex = 0;
	Service& serv;

	// graphical elements
	QListWidget* plantClusterListWidget;
	QLineEdit* codedNameLineEdit, * speciesLineEdit, * ageInMonthsLineEdit, * digitizedScanLineEdit, * fileLocationLineEdit, *myListLocationLineEdit;
	QPushButton* addButton, * deleteButton, * updateButton, * listButton, * fileLocationButton, *modeAButton, *modeBButton, *nextButton, *saveButton, *myListButton, *myListLocationButton, *undoButton, *redoButton;
	QLabel* modeALabel, * modeBLabel, *spaceLabel;

public:
	GUI(Service& s);

private:
	void initGUI();
	void populateList();
	void connectsSignalsAndSlots();
	int getSelectedIndex();
	void fileLocation();
	void addPlant();
	void updatePlant();
	void deletePlant();
	void setmodeA();
	void setModeB();
	void next();
	void myListLocation();
	void save();
	void myList();
	void undo();
	void redo();
};

