#pragma once
#include "car_domain.h"

#include <string>
#include <vector>

using std::vector;
using std::string;
using std::ostream;

class CarValidator {
public:
	/**
	 * @brief Valideaza un obiect de tip Car
	 * @param c - obiectul de validat
	*/
	void validate(const Car& c);
};

class CarValidatorException {
	vector<string> msgs;
public:
	// initializare obiect de tip CarValidatorException
	CarValidatorException(const vector<string>& errors) : msgs{ errors } {}

	friend ostream& operator<<(ostream& out, const CarValidatorException& ex);

	string getCarValidatorException() {
		string msg = "";
		for (const string e : msgs) {
			msg += e + '\n';
		}
		return msg;
	}
};

ostream& operator<<(ostream& out, const CarValidatorException& ex);
