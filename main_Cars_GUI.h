#pragma once
#include <QtWidgets/Qwidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/Qboxlayout>
#include <QtWidgets/Qpushbutton>
#include <QtWidgets/Qlineedit>
#include <QtWidgets/Qtablewidget>
#include <QtWidgets/Qlistwidget>
#include <QtWidgets/Qformlayout>
#include <QtWidgets/Qheaderview>
#include <QtWidgets/Qmessagebox>
#include <QtWidgets/Qgroupbox>
#include <QtWidgets/Qradiobutton>
#include <qtableview.h>


#include "car_service.h"
#include "car_domain.h"
#include "GarageGUI.h"


class CarsGUI :public QWidget {
private:

    CarService& srv;
    GarageGUI garage{ srv };

    QHBoxLayout* mainly = new QHBoxLayout{};
    // al patrulea layout pentru butoanele dinamice
    QVBoxLayout* ly4 = new QVBoxLayout{};

    QLabel* lblNrInmatriculare = new QLabel{"Numar inmatriculare"};
    QLabel* lblProducator = new QLabel{ "Producator" };
    QLabel* lblModel = new QLabel{ "Model" };
    QLabel* lblTip = new QLabel{ "Tip" };

    QLineEdit* editNrInmatriculare;
    QLineEdit* editProducator;
    QLineEdit* editModel;
    QLineEdit* editTip;

    QLineEdit* editFilter;

    QPushButton* btnReloadData;

    QPushButton* btnAddCar;
    QPushButton* btnRemoveCar;
    QPushButton* btnModifyCar;
    QPushButton* btnFindCar;

    QPushButton* btnSortCars;

    QPushButton* btnFilterCarsProducator;
    QPushButton* btnFilterCarsTip;

    QPushButton* btnUndo;


    QGroupBox* sortingBox = new QGroupBox("Sorteaza dupa:");

    QRadioButton* radioSortNrInmatriculare = new QRadioButton("Numar de inmatriculare");
    QRadioButton* radioSortTip = new QRadioButton(QString::fromStdString("Tip"));
    QRadioButton* radioSortProducator_Model = new QRadioButton(QString::fromStdString("Producator+Model")); 

    QLabel* lblFilterCriteria = new QLabel{ "Filtreaza dupa:" };


    QTableWidget* tableCars;    

    // garaj
    QPushButton* btnGarage; 

    /**
     * @brief initializeaza fereastra
    */
    void initGUI();

    void connectSignalsSlots();

    void reloadCarList(vector<Car> cars);

    // pentru butoane dinamice (functionalitate lab 10)
    void dinamicButtons();

    void clearLayout(QLayout* ly);    

public:

    // initializeaza obiect de tip CarsGUI
    CarsGUI(CarService& _srv) :srv{ _srv } {
        initGUI();
        connectSignalsSlots();
        dinamicButtons();
        reloadCarList(srv.getAll());
    }

    // nu permitem copierea unui obiect de tip CarsGUI
    CarsGUI(CarsGUI& _gui) = delete;

    void guiAddCar();

    void guiRemoveCar();

    void guiModifyCar();

    void guiFindCar();

    void guiCountMap(map<string, vector<Car>> countmap, string prod);

};
