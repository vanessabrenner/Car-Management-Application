#include <crtdbg.h>
#include <QtWidgets/qapplication.h>


#include "main_Cars_GUI.h"
#include "main_Cars_GUI_Model.h"
#include "car_validator.h"
#include "car_repo.h"
#include "car_service.h"
#include "tests.h"

/*
  9.
  Închiriere mașini
  Creați o aplicație care permite:
· gestiunea unei liste de mașini. Mașina: nrInmatriculare, producător, model, tip
· adăugare, ștergere, modificare și afișare mașini
· căutare mașina
· filtrare mașini după: producător, tip
· sortare mașini după: nrInmatriculare, tip, producator + model
*/



int main(int argc, char* argv[]) {
	//testAll();
	QApplication a(argc, argv);

	CarRepoFile repo{ "Repository.txt" };
	CarValidator val;
	CarService srv{ repo,val };
	CarsGUIModel gui{ srv };
	//CarsGUI gui{ srv };
	gui.resize(800, 400);	
	gui.show();

	return a.exec();
}