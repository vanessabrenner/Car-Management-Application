#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Cars_GUI.h"

class Cars_GUI : public QMainWindow
{
    Q_OBJECT

public:
    Cars_GUI(QWidget *parent = nullptr);
    ~Cars_GUI();

private:
    Ui::Cars_GUIClass ui;
};
