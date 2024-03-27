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
#include <qpainter.h>


#include "car_service.h"
#include "car_domain.h"
#include "Observer.h"

class GarageGUI: public QWidget, public Observer{
private:
	CarService& srv;

    QHBoxLayout* mainly = new QHBoxLayout{};

    //QVBoxLayout* leftgaragely = new QVBoxLayout{};
    QVBoxLayout* rightgaragely = new QVBoxLayout{};

    QLabel* lblNrInmatricularegarage = new QLabel{ "Numar inmatriculare" };
    QLabel* lblNumar = new QLabel{ "Numar:" };
    QLabel* lblFisier = new QLabel{ "Fisier" };

    QPushButton* btnAddCarToGarage;
    QPushButton* btnEmptyGarage;
    QPushButton* btnAddRandomCars;
    //QPushButton* btnGetAllGarage;
    QPushButton* btnWriteToFile;
    QPushButton* btnGarage;
    QPushButton* btnNoCarsGarage;


    QLineEdit* editNrInmatricularegarage;
    QLineEdit* editNumar;
    QLineEdit* editFile;  

    QTableWidget* tableGarage;

    void connectSignalsSlotsGarage();

    void reloadGarage(vector<Car> garage);

    void initGarageGUI();

    void update() override{
        reloadGarage(srv.getAllGarageCars());
    }

public:
	GarageGUI(CarService& _srv) : srv{ _srv } {
        srv.getGarage().addObserver(this);
        initGarageGUI();
        connectSignalsSlotsGarage();
        reloadGarage(srv.getAllGarageCars());
    };
};

class GarageGUILabel_Draw: public QWidget, public Observer{
private:
    Garage& garage;
    QLabel* lblNrGarage;
    QLineEdit* editNrGarage;

    void initGUI() {
        auto ly = new QHBoxLayout{};
        this->setLayout(ly);

        lblNrGarage = new QLabel{ "Numar masini din garaj:" };
        //lblNrGarage->setStyleSheet("QLabel { background-color : gray }");
        editNrGarage = new QLineEdit{};
        
        auto formly = new QFormLayout{};
        formly->addRow(lblNrGarage, editNrGarage);
        ly->addLayout(formly);

        garage.addObserver(this);
    }

    void paintEvent(QPaintEvent* ev) override {
        QPainter p{ this };
        int x = 0;
        int y = 0;
        for (auto car : garage.getAllGarageCars()) {
            //p.drawRect(x, y, 10, song.getDurata() * 10);
            x = rand() % 200 + 1;
            y = rand() % 200 + 1;
            qDebug() << x << " " << y;            
            QRectF target(x, y, 100, 94);
            QRectF source(0, 0, 732, 720);
            QImage image("car.jpg");

            p.drawImage(target, image, source);

            x += 40;

        }
    }

    void update() override{
        this->editNrGarage->setText(QString::number(garage.getAllGarageCars().size()));
        repaint();
    }

    ~GarageGUILabel_Draw(){
        garage.removeObserver(this);
    }

public:
    GarageGUILabel_Draw(Garage& _garage) : garage{ _garage } {
        initGUI();
    };
};

class GarageGUITable : public QWidget, public Observer {
private:
    Garage& garage;
    QHBoxLayout* ly = new QHBoxLayout{};
    QTableWidget* tableGarage;
    QPushButton* btnEmpty;

    void initGUI() {
        setLayout(ly);
        tableGarage = new QTableWidget(3, 4);
        btnEmpty = new QPushButton{ "Goleste garaj" };
        ly->addWidget(tableGarage);
        ly->addWidget(btnEmpty);

        garage.addObserver(this);
    }    

    void reloadGarage(vector<Car> garage) {
        tableGarage->clearContents();
        tableGarage->setRowCount(garage.size());

        int line = 0;
        for (auto& car : garage) {
            tableGarage->setItem(line, 0, new QTableWidgetItem(QString::fromStdString(car.getNrInmatriculare())));
            tableGarage->setItem(line, 1, new QTableWidgetItem(QString::fromStdString(car.getProducator())));
            tableGarage->setItem(line, 2, new QTableWidgetItem(QString::fromStdString(car.getModel())));
            tableGarage->setItem(line, 3, new QTableWidgetItem(QString::number(car.getTip())));
            line++;
        }
    }

    void connectSignalSlots() {
        QObject::connect(btnEmpty, &QPushButton::clicked, this, [&]() {
            garage.emptyGarage();
            });
    }

    void update() override{
        reloadGarage(garage.getAllGarageCars());        
    }

    ~GarageGUITable() {
        garage.removeObserver(this);
    }

public:
    GarageGUITable(Garage& _garage) : garage{ _garage } {
        initGUI();
        connectSignalSlots();
    };
};