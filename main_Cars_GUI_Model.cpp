#include "main_Cars_GUI_Model.h"

void CarsGUIModel::initGUI() {

    setLayout(mainly);

    // primul layout ce contine o scurta descriere si lista de masini
    auto ly1 = new QVBoxLayout{};

    auto titlu = new QLabel{ "Masinile noastre sunt:" };

    // setam tabela de masini
    model = new MyTableModel{ srv.getAll() };
    this->tableCars->setModel(model);
    //this->tableCars->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // lab 11
    //tableCars = new QListWidget;


    btnReloadData = new QPushButton("Reload data");
    ly1->addWidget(titlu);
    ly1->addWidget(tableCars);
    ly1->addWidget(btnReloadData);

    mainly->addLayout(ly1);

    // al doilea layout ce contine formurile si butoane
    auto ly2 = new QVBoxLayout{};

    auto formLy = new QFormLayout;

    editNrInmatriculare = new QLineEdit;
    editProducator = new QLineEdit;
    editModel = new QLineEdit;
    editTip = new QLineEdit;
    formLy->addRow(lblNrInmatriculare, editNrInmatriculare);
    formLy->addRow(lblProducator, editProducator);
    formLy->addRow(lblModel, editModel);
    formLy->addRow(lblTip, editTip);

    // pentru estetica punem butoanele pe mai multe coloane
    auto lyButtons = new QVBoxLayout{};

    auto lyBtn1 = new QHBoxLayout{};
    btnAddCar = new QPushButton("Adauga masina");
    btnRemoveCar = new QPushButton("Sterge masina");
    lyBtn1->addWidget(btnAddCar);
    lyBtn1->addWidget(btnRemoveCar);
    auto lyBtn2 = new QHBoxLayout{};
    btnModifyCar = new QPushButton("Modifica masina");
    btnFindCar = new QPushButton("Gaseste masina");
    lyBtn2->addWidget(btnModifyCar);
    lyBtn2->addWidget(btnFindCar);

    btnGarage = new QPushButton("Garage");
    lyButtons->addWidget(btnGarage);
    lyButtons->addLayout(lyBtn1);
    lyButtons->addLayout(lyBtn2);
    btnUndo = new QPushButton("Undo");
    lyButtons->addWidget(btnUndo);

    ly2->addLayout(formLy);
    ly2->addLayout(lyButtons);

    mainly->addLayout(ly2);

    // al treilea layout pentru partea de sortare, filtrare
    auto ly3 = new QVBoxLayout{};
    // radiobuttons pentru sortare
    auto lySorting = new QVBoxLayout{};
    sortingBox->setLayout(lySorting);
    lySorting->addWidget(radioSortNrInmatriculare);
    lySorting->addWidget(radioSortTip);
    lySorting->addWidget(radioSortProducator_Model);

    btnSortCars = new QPushButton("Sorteaza");
    lySorting->addWidget(btnSortCars);

    ly3->addWidget(sortingBox);

    //form pentru filtrare
    auto lyFilter = new QVBoxLayout{};

    auto formFilter = new QWidget;
    auto lyformFilter = new QFormLayout;
    formFilter->setLayout(lyformFilter);
    editFilter = new QLineEdit;
    lyformFilter->addRow(lblFilterCriteria, editFilter);
    btnFilterCarsProducator = new QPushButton("Filtreaza dupa producator");
    btnFilterCarsTip = new QPushButton("Filtreaza dupa tip");
    lyformFilter->addWidget(btnFilterCarsProducator);
    lyformFilter->addWidget(btnFilterCarsTip);

    lyFilter->addWidget(formFilter);
    ly3->addLayout(lyFilter);

    mainly->addLayout(ly3);

}

void CarsGUIModel::reloadCarList(vector<Car> cars) {
   
    this->model->setCars(cars);

}

void CarsGUIModel::clearLayout(QLayout* layout) {
    if (layout == NULL)
        return;
    QLayoutItem* item;
    while ((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

void CarsGUIModel::dinamicButtons() {
    map<string, vector<Car>> countmap;
    countmap = srv.getCountMap();

    clearLayout(ly4);

    for (auto& item : countmap) {
        auto a = new QPushButton;
        a->setText(QString::fromStdString(item.first));

        QObject::connect(a, &QPushButton::clicked, this, [=]() {
            guiCountMap(countmap, item.first);
            });

        ly4->addWidget(a);
    }

    mainly->addLayout(ly4);

}

void CarsGUIModel::connectSignalsSlots() {
    QObject::connect(btnAddCar, &QPushButton::clicked, this, &CarsGUIModel::guiAddCar);

    QObject::connect(btnRemoveCar, &QPushButton::clicked, this, &CarsGUIModel::guiRemoveCar);

    QObject::connect(btnModifyCar, &QPushButton::clicked, this, &CarsGUIModel::guiModifyCar);

    QObject::connect(btnFindCar, &QPushButton::clicked, this, &CarsGUIModel::guiFindCar);

    QObject::connect(btnUndo, &QPushButton::clicked, this, [=]() {
        try {
            srv.undo();
            dinamicButtons();
            reloadCarList(srv.getAll());
        }
        catch (CarRepoException& ex) {
            QMessageBox::information(this, "Warning", QString::fromStdString(ex.getCarRepoException()));
        }
        });

    QObject::connect(btnSortCars, &QPushButton::clicked, this, [&]() {
        if (radioSortNrInmatriculare->isChecked())
            reloadCarList(srv.sortareNrInmatriculare());
        else if (radioSortTip->isChecked())
            reloadCarList(srv.sortareTip());
        else if (radioSortProducator_Model->isChecked())
            reloadCarList(srv.sortareProducator_Model());
        });

    QObject::connect(btnFilterCarsProducator, &QPushButton::clicked, this, [&]() {
        string filter = editFilter->text().toStdString();
        reloadCarList(srv.filtrareProducator(filter));
        });

    QObject::connect(btnFilterCarsTip, &QPushButton::clicked, this, [&]() {
        int filter = editFilter->text().toInt();
        reloadCarList(srv.filtrareTip(filter));
        });

    QObject::connect(btnReloadData, &QPushButton::clicked, this, [&]() {
        reloadCarList(srv.getAll());
        });

    // garaj

    QObject::connect(btnGarage, &QPushButton::clicked, this, [&]() {
        garage.show();
        });
}

void CarsGUIModel::guiAddCar() {
    try {
        string NrInmatriculare = editNrInmatriculare->text().toStdString();
        string Producator = editProducator->text().toStdString();
        string Model = editModel->text().toStdString();
        int Tip = editTip->text().toInt();

        srv.addCar(NrInmatriculare, Producator, Model, Tip);
        reloadCarList(srv.getAll());
        dinamicButtons();

        // afisam mesaj ca masina s a adaugat
        QMessageBox::information(this, "Info", QString::fromStdString("Masina s-a adaugat cu succes!"));
    }
    catch (CarRepoException& ex) {
        QMessageBox::information(this, "Warning", QString::fromStdString(ex.getCarRepoException()));
    }
    catch (CarValidatorException& ex) {
        QMessageBox::information(this, "Warning", QString::fromStdString(ex.getCarValidatorException()));
    }
}

void CarsGUIModel::guiRemoveCar() {
    try {
        string NrInmatriculare = editNrInmatriculare->text().toStdString();

        srv.removeCar(NrInmatriculare);
        reloadCarList(srv.getAll());
        dinamicButtons();

        // afisam mesaj ca masina s a sters cu succes
        QMessageBox::information(this, "Info", QString::fromStdString("Masina s-a sters cu succes!"));
    }
    catch (CarRepoException& ex) {
        QMessageBox::information(this, "Warning", QString::fromStdString(ex.getCarRepoException()));
    }
}

void CarsGUIModel::guiModifyCar() {
    try {
        string NrInmatriculare = editNrInmatriculare->text().toStdString();
        string Producator = editProducator->text().toStdString();
        string Model = editModel->text().toStdString();
        int Tip = editTip->text().toInt();

        srv.modifyCar(NrInmatriculare, Producator, Model, Tip);
        reloadCarList(srv.getAll());
        dinamicButtons();

        // afisam mesaj ca masina s a modificat cu succes
        QMessageBox::information(this, "Info", QString::fromStdString("Masina s-a modificat cu succes!"));
    }
    catch (CarRepoException& ex) {
        QMessageBox::information(this, "Warning", QString::fromStdString(ex.getCarRepoException()));
    }
}

void CarsGUIModel::guiFindCar() {
    try {
        string NrInmatriculare = editNrInmatriculare->text().toStdString();

        Car c = srv.findCar(NrInmatriculare);
        //reloadCarList(srv.getAll());

        // afisam mesaj cu masina gasita
        QMessageBox::information(this, "Info", QString::fromStdString("Masina data s-a gasit! Detalii despre ea: \nNumar de inmatriculare: " + c.getNrInmatriculare() + '\n'
            + "Producator: " + c.getProducator() + '\n'
            + "Model: " + c.getModel() + '\n'
            + "Tip: " + std::to_string(c.getTip())));
    }
    catch (CarRepoException& ex) {
        QMessageBox::information(this, "Warning", QString::fromStdString(ex.getCarRepoException()));
    }
}

void CarsGUIModel::guiCountMap(map<string, vector<Car>> countmap, string prod) {
    QMessageBox::information(this, "Numarul de masini cu producatorul dat", QString::fromStdString("Masina cu producatorul " + prod + " exista de " + std::to_string(countmap[prod].size()) + " ori."));
}