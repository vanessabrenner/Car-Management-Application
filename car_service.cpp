#include "car_service.h"

#include <assert.h>
#include <functional>
#include <algorithm>

using std::function;

void CarService::addCar(const string& NrInmatriculare, const string& Producator, const string& Model, int Tip) {
	Car c{ NrInmatriculare, Producator, Model, Tip };
	val.validate(c);
	repo.store(c);
	undoActions.add_undoAction(new UndoAdd(c, repo));
}

void CarService::removeCar(const string& NrInmatriculare) {
	Car c = repo.find(NrInmatriculare);
	repo.remove(c);
	undoActions.add_undoAction(new UndoRemove(c, repo));
}

void CarService::modifyCar(string NrInamtriculare, string Producator, string Model, int Tip) {
	Car c = repo.find(NrInamtriculare);
	repo.modify(c, Producator, Model, Tip);
	undoActions.add_undoAction(new UndoModify(c, repo));
}

const Car& CarService::findCar(const string NrInmatriculare) {
	return repo.find(NrInmatriculare);
}

vector<Car> CarService::filter(function<bool(const Car&)> fct) noexcept {
	vector<Car> filteredlist;
	for (const auto& car : getAll()) {
		if (fct(car))
			filteredlist.push_back(car);
	}

	return filteredlist;
}

vector<Car> CarService::filtrareProducator(string Producator) {
	return filter([=](const Car& c) {
		return c.getProducator() == Producator;
		});
}

vector<Car> CarService::filtrareTip(int Tip) {
	return filter([=](const Car& c) noexcept {
		return c.getTip() == Tip;
		});
}

//vector<Car> CarService::generalsort(bool(*cmp)(const Car& c1, const Car& c2)) {
//	vector<Car> sortedlist = getAll();
//	for (int i = 0; i < sortedlist.size(); i++) {
//		for (int j = 0; j < sortedlist.size(); j++) {
//			if (cmp(sortedlist[i], sortedlist[j])) {
//				Car aux = sortedlist[i];
//				sortedlist[i] = sortedlist[j];
//				sortedlist[j] = aux;
//			}
//		}
//	}
//	return sortedlist;
//}

vector<Car> CarService::sortareNrInmatriculare() {
	auto sortedlist = getAll();
	sort(sortedlist.begin(), sortedlist.end(), cmpNrInmatriculare);
	return sortedlist;
	//return generalsort(cmpNrInmatriculare);
}

vector<Car> CarService::sortareTip() {
	auto sortedlist = getAll();
	sort(sortedlist.begin(), sortedlist.end(), cmpTip);
	return sortedlist;
	//return generalsort(cmpTip);
}

vector<Car> CarService::sortareProducator_Model() {
	auto sortedlist = getAll();
	sort(sortedlist.begin(), sortedlist.end(), cmpProducator_Model);
	return sortedlist;
	//return generalsort(cmpProducator_Model);
}

const vector<Car> CarService::getAll() {
	return this->repo.getAll();
}

// pentru garaj..............................

void CarService::addCarToGarage(string NrInmatriculare) {
	const auto& car = this->repo.find(NrInmatriculare);
	garage.addCarToGarage(car);
}

void CarService::addRandomCars(int nr) {
	garage.addRandomCars(this->getAll(), nr);
}

void CarService::emptyGarage() {
	garage.emptyGarage();
}

const vector<Car>& CarService::getAllGarageCars() {
	return garage.getAllGarageCars();
}

void CarService::write_to_file(string nume_fisier) {
	garage.write_to_file(this->getAllGarageCars(), nume_fisier);
}

// undo..............................

void CarService::undo() {
	if (undoActions.size() == 0)
		throw CarRepoException("Nu se mai poate face undo");
	undoActions.do_undo();
}
