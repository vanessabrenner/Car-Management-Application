#include "Garage.h"
#include "car_repo.h"
using std::shuffle;
using std::ifstream;
using std::ofstream;

void Garage::addCarToGarage(const Car& c) {
	this->garage.push_back(c);
	notify();
}

void Garage::emptyGarage() {
	this->garage.clear();
	notify();
}

void Garage::addRandomCars(vector<Car> cars, int nr) {
	// amestecam vectorul
	shuffle(cars.begin(), cars.end(), std::default_random_engine(std::random_device{}()));
	while (garage.size() < nr and cars.size() > 0) {
		garage.push_back(cars.back());
		cars.pop_back();
	}
	notify();
}

const vector<Car>& Garage::getAllGarageCars() {
	return this->garage;
}

//void GarageFile::loadFromFile() {
//	ifstream fin(nume_fisier);
//	if (!fin.is_open()) {
//		throw CarRepoException("Eroare la deschiderea fisierului " + nume_fisier);
//	}
//
//	while (!fin.eof()) {
//		string NrInmatriculare;
//		fin >> NrInmatriculare;
//		string Producator;
//		fin >> Producator;
//		string Model;
//		fin >> Model;
//		int Tip;
//		fin >> Tip;
//	}
//}

void Garage::write_to_file(vector<Car> cars, string nume_fisier) {
	ofstream fout(nume_fisier);
	if (!fout.is_open()) {
		throw CarRepoException("Eroare la deschiderea fisierului " + nume_fisier);
	}

	for (auto& car : cars) {
		fout << car.getNrInmatriculare() << ' ' << car.getProducator() << ' ' << car.getModel() << ' ' << car.getTip() << std::endl;
	}

	fout.close();
}
