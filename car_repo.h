#pragma once
#include "car_domain.h"
//#include "MyList.h"

#include <vector>
#include <string>
#include <ostream>
#include <fstream>
#include <map>
#include <time.h>
#include <random>

using std::vector;
using std::map;
using std::string;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::pair;

class RepoAbstract {
public:
	RepoAbstract() = default;
	virtual ~RepoAbstract() {};
	RepoAbstract(const RepoAbstract& cr) = delete;
	virtual void store(const Car& c) = 0;
	virtual void remove(const Car& c) = 0;
	virtual void modify(const Car& c, string Producator, string Model, int Tip) = 0;
	virtual const Car& find(string NrInmatriculare) = 0;
	virtual const vector<Car> getAll() = 0;
	virtual bool exist(const Car& c) = 0;
	virtual void emptyRepo() = 0;
};

class RepoLab : public RepoAbstract {
private:
	map<string, Car> all;
	double prob;
public:
	RepoLab(double nr) : prob{ nr } {};

	/**
	 * @brief Adauga la lista noul obiect
	 * @param c - obiectul de tip Car ce trebuie adaugat
	 * @exception - arunca exceptie de tip CarRepoException daca masina exista deja
	*/
	virtual void store(const Car& c);

	/**
	 * @brief Sterge un obiect din lista daca acesta exista
	 * @param c - obiectul de sters
	 * @exception - arunca exceptie de tip CarRepoException daca masina nu exista in lista
	*/
	virtual void remove(const Car& c);

	/**
	 * @brief Modifica un obiect din lista
	 * @param c - obiectul de modificat
	 * @exception - arunca exceptie de tip CarRepoException daca masina nu exista in lista
	*/
	virtual void modify(const Car& c, string Producator, string Model, int Tip);

	/**
	 * @brief Cauta un obiect avand NrInmatriculare dat
	 * @param NrInmatriculare - nr. de inmatriculare dupa care trebuie sa cautam (id ul aferent)
	 * @return - un obiect de tip Car
	 * @exception - arunca exceptie de tip CarRepoException daca masina nu exista in lista
	*/
	const Car& find(string NrInmatriculare);

	/**
	 * @brief Functie de returnare a listei de obiecte Car
	 * @return - lista de obiecte Car
	*/
	virtual const vector<Car> getAll();

	double get_prob() {
		return prob;
	}

	/**
	 * @brief Verifica daca un obiect de tip Car exista in lista
	 * @param c - obiectul pe care l verificam
	 * @return - True daca nu exista, False daca exista
	*/
	bool exist(const Car& c);

	/**
	 * @brief Goleste vectorul de obiecte Car
	*/
	virtual void emptyRepo() override {
		this->all.clear();
	}
};

class CarRepo : public RepoAbstract {
	vector<Car> all;

public:
	//CarRepo() = default;

	// nu permitem copierea listei de obiecte
	//CarRepo(const CarRepo& cr) = delete;

	//virtual ~CarRepo() {};

	/**
	 * @brief Adauga la lista noul obiect
	 * @param c - obiectul de tip Car ce trebuie adaugat
	 * @exception - arunca exceptie de tip CarRepoException daca masina exista deja
	*/
	virtual void store(const Car& c);

	/**
	 * @brief Sterge un obiect din lista daca acesta exista
	 * @param c - obiectul de sters
	 * @exception - arunca exceptie de tip CarRepoException daca masina nu exista in lista
	*/
	virtual void remove(const Car& c);

	/**
	 * @brief Modifica un obiect din lista
	 * @param c - obiectul de modificat
	 * @exception - arunca exceptie de tip CarRepoException daca masina nu exista in lista
	*/
	virtual void modify(const Car& c, string Producator, string Model, int Tip);

	/**
	 * @brief Cauta un obiect avand NrInmatriculare dat
	 * @param NrInmatriculare - nr. de inmatriculare dupa care trebuie sa cautam (id ul aferent)
	 * @return - un obiect de tip Car
	 * @exception - arunca exceptie de tip CarRepoException daca masina nu exista in lista
	*/
	const Car& find(string NrInmatriculare);

	/**
	 * @brief Functie de returnare a listei de obiecte Car
	 * @return - lista de obiecte Car
	*/
	virtual const vector<Car> getAll();

	/**
	 * @brief Verifica daca un obiect de tip Car exista in lista
	 * @param c - obiectul pe care l verificam
	 * @return - True daca nu exista, False daca exista
	*/
	bool exist(const Car& c);

	/**
	 * @brief Functie virtuala de undo
	*/
	//virtual void undo() = 0;

	/**
	 * @brief Goleste vectorul de obiecte Car
	*/
	virtual void emptyRepo() {
		this->all.clear();
	}

};

class CarRepoFile : public CarRepo {
private:
	string nume_fisier;
	void write_to_file();
	void load_from_file();
public:
	CarRepoFile(string fisier) : CarRepo(), nume_fisier{ fisier } {}

	/**
	 * @brief Adauga o masina in lista
	 * @param c - masina de adaugat
	 * Fisierul se actualizeaza
	*/
	void store(const Car& c) override {
		CarRepo::store(c);
		write_to_file();
	}

	/**
	 * @brief Sterge o masina din lista
	 * @param c - masina de sters
	 * Fisierul se actulizeaza
	*/
	void remove(const Car& c) override {
		CarRepo::remove(c);
		write_to_file();
	}
	/**
	 * @brief Modifica o masina data
	 * @param c - masina ce trebuie modificata
	 * @param Producator
	 * @param Model
	 * @param Tip
	 * Fisierul se va actualiza
	*/
	void modify(const Car& c, string Producator, string Model, int Tip) override {
		CarRepo::modify(c, Producator, Model, Tip);
		write_to_file();
	}

	/**
	 * @brief Returneaza toate masinile din lista
	 * @return masinile din fisier
	*/
	const vector<Car> getAll() override {
		load_from_file();
		return CarRepo::getAll();
	}

	/**
	 * @brief Goleste vectorul de obiecte Car
	 * Fisierul se va actualiza
	*/
	void emptyRepo() override {
		CarRepo::emptyRepo();
		write_to_file();
	}

	//void undo() override {

	//}

};

class CarRepoException {
	string msg;
public:
	// initializare obiect de tip CarRepoException
	CarRepoException(string m) : msg{ m } {}

	// pentru printare
	friend ostream& operator<<(ostream& out, const CarRepoException& exc);

	string getCarRepoException() {
		return msg;
	}
};

ostream& operator<<(ostream& out, const CarRepoException& exc);