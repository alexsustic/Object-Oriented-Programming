#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PlantClustersGUI.h"

class PlantClustersGUI : public QMainWindow
{
    Q_OBJECT

public:
    PlantClustersGUI(QWidget *parent = Q_NULLPTR);

private:
    Ui::PlantClustersGUIClass ui;
};
