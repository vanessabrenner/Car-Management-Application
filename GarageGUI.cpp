#include "GarageGUI.h"

void GarageGUI::connectSignalsSlotsGarage() {
    QObject::connect(btnAddCarToGarage, &QPushButton::clicked, this, [=]() {
        string NrInmatriculare = editNrInmatricularegarage->text().toStdString();
        try {
            srv.addCarToGarage(NrInmatriculare);
            reloadGarage(srv.getAllGarageCars());
            QMessageBox::information(this, "Info", "Masina a fost adaugata cu succes in garaj!");
        }
        catch (CarRepoException& ex) {
            QMessageBox::information(this, "Warning", QString::fromStdString(ex.getCarRepoException()));
        }
        });

    QObject::connect(btnAddRandomCars, &QPushButton::clicked, this, [=]() {
        int numar = editNumar->text().toInt();
        srv.addRandomCars(numar);
        reloadGarage(srv.getAllGarageCars());
        QMessageBox::information(this, "Info", "Masinile au fost adaugate cu succes!");
        });

    QObject::connect(btnEmptyGarage, &QPushButton::clicked, this, [=]() {
        srv.emptyGarage();
        reloadGarage(srv.getAllGarageCars());
        QMessageBox::information(this, "Info", "Garajul a fost golit!");
        });

    /*QObject::connect(btnGetAllGarage, &QPushButton::clicked, this, [=]() {
        reloadGarage(srv.getAllGarageCars());
        });*/

    QObject::connect(btnWriteToFile, &QPushButton::clicked, this, [=]() {
        try {
            string file = editFile->text().toStdString();
            srv.write_to_file(file);
            QMessageBox::information(this, "Info", "Garajul a fost scris in fisier!");
        }
        catch (CarRepoException& ex) {
            QMessageBox::information(this, "Warning", QString::fromStdString(ex.getCarRepoException()));
        }
        });

    QObject::connect(btnGarage, &QPushButton::clicked, this, [=]() {
        auto garageWindow = new GarageGUITable{ srv.getGarage() };
        garageWindow->show();
        });

    QObject::connect(btnNoCarsGarage, &QPushButton::clicked, this, [=]() {
        auto garageWindow = new GarageGUILabel_Draw{ srv.getGarage() };
        garageWindow->resize(300, 300);
        garageWindow->show();
        });
}

void GarageGUI::reloadGarage(vector<Car> garage) {
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

void GarageGUI::initGarageGUI() {

    this->setLayout(mainly);    

    tableGarage = new QTableWidget(3, 4);
    QStringList hdrTabelCars;
    hdrTabelCars << "Numar Inmatriculare" << "Producator" << "Model" << "Tip";
    tableGarage->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableGarage->setHorizontalHeaderLabels(hdrTabelCars);

    mainly->addWidget(tableGarage);   

    auto formly = new QFormLayout;

    editNrInmatricularegarage = new QLineEdit;
    editNumar = new QLineEdit;
    editFile = new QLineEdit;

    formly->addRow(lblNrInmatricularegarage, editNrInmatricularegarage);
    formly->addRow(lblNumar, editNumar);
    formly->addRow(lblFisier, editFile);

    rightgaragely->addLayout(formly);

    mainly->addLayout(rightgaragely);

    btnAddCarToGarage = new QPushButton("Adauga masina in garaj");
    btnEmptyGarage = new QPushButton("Goleste garaj");
    btnAddRandomCars = new QPushButton("Adauga masini random in garaj");
    //btnGetAllGarage = new QPushButton("Vezi toate masinile");
    btnWriteToFile = new QPushButton("Scrie masinile in fisier ");
    btnGarage = new QPushButton("Deschide garaj");
    btnGarage->setStyleSheet("background-color: green");
    btnNoCarsGarage = new QPushButton("Vizualizeaza nr. masini");
    btnNoCarsGarage->setStyleSheet("background-color: magenta");

    rightgaragely->addWidget(btnAddCarToGarage);
    rightgaragely->addWidget(btnAddRandomCars);
    rightgaragely->addWidget(btnEmptyGarage);
    // rightgaragely->addWidget(btnGetAllGarage);
    rightgaragely->addWidget(btnWriteToFile);
    rightgaragely->addWidget(btnGarage);
    rightgaragely->addWidget(btnNoCarsGarage);


    mainly->addLayout(rightgaragely);

    

}