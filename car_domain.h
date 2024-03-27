#pragma once

#include <string>
#include <iostream>
#include <ostream>

using std::cout;
using std::string;
using std::ostream;

class Car {
	std::string NrInmatriculare;
	std::string Producator;
	std::string Model;
	int Tip;

	friend ostream& operator<<(ostream& os, const Car& c);
public:
	Car() = default;
	// intializare obiect de tip Car
	Car(const string nr, const string prod, const string model, int t) : NrInmatriculare{ nr }, Producator{ prod }, Model{ model }, Tip{ t } {}

	// copierea unui obiect Car intr-altul
	Car(const Car& el) :NrInmatriculare{ el.NrInmatriculare }, Producator{ el.Producator }, Model{ el.Model }, Tip{ el.Tip } {
		//cout << "!!!!!" << '\n';
	}

	// get-ere
	string getNrInmatriculare() const {
		return NrInmatriculare;
	}
	string getProducator() const {
		return Producator;
	}
	string getModel() const {
		return Model;
	}
	int getTip() const noexcept {
		return Tip;
	}

	//set-ere
	void setProducator(string prod) {
		this->Producator = prod;
	}

	void setModel(string m) {
		this->Model = m;
	}

	void setTip(int tip) noexcept {
		this->Tip = tip;
	}

};

/**
 * @brief Functie de comparare a doua obiecte de tip Car
 * @param c1
 * @param c2
 * @return - true, daca c1 are numarul de inmatriculare mai mic (alfabetic) decat c2, false, altfel
*/
bool cmpNrInmatriculare(const Car& c1, const Car& c2);

/**
 * @brief Functie de comparare a doua obiecte de tip Car
 * @param c1
 * @param c2
 * @return - true, daca c1 are tipul mai mic decat c2, false, altfel
*/
bool cmpTip(const Car& c1, const Car& c2) noexcept;

/**
 * @brief Functie de comparare a doua obiecte de tip Car
 * @param c1
 * @param c2
 * @return - true, daca c1 are producatorul mai mic (alfabetic) decat c2, false, altfel
 *  in caz de egalitate se face compararea intre modelele celor doua obiecte Car, in acelasi mod
*/
bool cmpProducator_Model(const Car& c1, const Car& c2);

