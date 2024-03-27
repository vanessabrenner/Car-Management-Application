#pragma once
#include "car_domain.h"
#include "car_repo.h"
#include "car_validator.h"
#include "CountMap.h"
//#include "Garage.h"
#include "undo.h"
#include "Garage.h"

#include <string>
#include <vector>
#include <functional>

using std::function;

class CarService {
	RepoAbstract& repo;
	CarValidator& val;

	Garage garage;
	MyUndoActions undoActions;
	// lab8
	CountMap countmap;

	/**
	 * @brief Functie generica de filtrare
	 * @param fct - functia dupa care se va filtra
	 * @return - o noua lista filtrata
	*/
	vector<Car> filter(function<bool(const Car&)> fct) noexcept;

	/**
	 * @brief Functie generica de sortare
	 * @param cmp - comparatoru dupa care se va sorta
	 * @return - o noua lista sortata
	*/
	vector<Car> generalsort(bool(*cmp)(const Car& c1, const Car& c2));

public:
	// initilaizare obiect de tip CarService
	CarService(RepoAbstract& r, CarValidator& v) noexcept :repo{ r }, val{ v } {}

	// nu permitem copierea de obiecte de tip CarService
	CarService(const CarService& s) = delete;

	/**
	 * @brief Returneaza lista de obiecte de tip Car
	 * @return - o lista de obiecte de tip Car
	*/
	const vector<Car> getAll();

	map<string, vector<Car>> getCountMap() {
		return countmap.CountCarsProducator(getAll());
	}

	/**
	 * @brief Adauga o masina in lista
	 * @param NrInmatriculare
	 * @param Producator
	 * @param Model
	 * @param Tip
	*/
	void addCar(const string& NrInmatriculare, const string& Producator, const string& Model, int Tip);

	/**
	 * @brief Sterge un obiect din lista daca acesta exista
	 * @param c - obiectul de sters
	*/
	void removeCar(const string& NrInmatriculare);

	/**
	 * @brief Modifica un obiect din lista curenta care are nr. de inmatriculare dat
	 * @param NrInamtriculare
	 * @param Producator
	 * @param Model
	 * @param tip
	*/
	void modifyCar(string NrInamtriculare, string Producator, string Model, int Tip);

	/**
	 * @brief Cauta o masina in lista
	 * @param NrInmatriculare
	 * @return - masina gasita
	*/
	const Car& findCar(string NrInmatriculare);

	/**
	 * @brief Filtreaza dupa producator
	 * @param Producator - producatorul dupa care se filtreaza
	 * @return - o lista de obiecte Car
	*/
	vector<Car> filtrareProducator(string Producator);

	/**
	 * @brief FIltreaza lista dupa tip
	 * @param Tip - tipul dupa care se filtreaza
	 * @return - o lista de obiecte Car
	*/
	vector<Car> filtrareTip(int Tip);

	/**
	 * @brief Sorteaza dupa nr. de inmatriculare
	 * @return - o lista de obiecte Car
	*/
	vector<Car> sortareNrInmatriculare();

	/**
	 * @brief Sorteaza dupa tip
	 * @return - o lista de obiecte Car
	*/
	vector<Car> sortareTip();

	/**
	 * @brief Sorteaza dupa producator si model in acelasi timp
	 * @return - o lista de obiecte Car
	*/
	vector<Car> sortareProducator_Model();

	// pentru garaj................................

	
	// * @brief Adauga o masina in garaj
	// * @param c - masina de adaugat
	void addCarToGarage(string NumarInmatriculare);
	
	// * @brief Elimina toate elementele din lista	
	void emptyGarage();

	// * @brief Adauga masini random in garaj de un numar dat
	// * @param cars - masinile din acre se alege
	// * @param nr - numarul de masini de adaugat	
	void addRandomCars(int nr);
	
	// * @brief Returneaza masinile din garaj
	// * @return - un vector ce contine toate masinile adaugate anterior in garaj	
	const vector<Car>& getAllGarageCars();
	
	// * @brief Scrie in fisier masinile din garaj
	// * @param nume_fisier - fisierul in care se va scrie
	void write_to_file(string nume_fisier);


	Garage& getGarage() {
		return this->garage;
	}

	// undo.......................................

	/**
	 * @brief Face undo la ultima modificare
	*/
	void undo();

};

