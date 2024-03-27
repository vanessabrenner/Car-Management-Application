#pragma once
#include "car_domain.h"
#include "Observer.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using std::vector;

class Garage : public Observable {
private:
	vector<Car> garage;
public:
	Garage() = default;

	/**
	 * @brief Adauga o masina in garaj
	 * @param c - masina de adaugat
	*/
	void addCarToGarage(const Car& c);
	/**
	 * @brief Elimina toate elementele din lista
	*/
	void emptyGarage();
	/**
	 * @brief Adauga masini random in garaj de un numar dat
	 * @param cars - masinile din acre se alege
	 * @param nr - numarul de masini de adaugat
	*/
	void addRandomCars(vector<Car> cars, int nr);
	/**
	 * @brief Returneaza masinile din garaj
	 * @return - un vector ce contine toate masinile adaugate anterior in garaj
	*/
	const vector<Car>& getAllGarageCars();

	void write_to_file(vector<Car> cars, string nume_fisier);
};


