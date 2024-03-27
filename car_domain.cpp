#include "car_domain.h"

bool cmpNrInmatriculare(const Car& c1, const Car& c2) {
	return c1.getNrInmatriculare() < c2.getNrInmatriculare();
}

bool cmpTip(const Car& c1, const Car& c2) noexcept {
	return c1.getTip() < c2.getTip();
}

bool cmpProducator_Model(const Car& c1, const Car& c2) {
	if (c1.getProducator() == c2.getProducator())
		return c1.getModel() < c2.getModel();
	else
		return c1.getProducator() < c2.getProducator();
}

// pentru printarea pe ecran a unui obiect de tip Car
ostream& operator<<(ostream& os, const Car& c) {
	return os << "Numar de inmatriculare: " << c.NrInmatriculare << "   |   Producator: " << c.Producator
		<< "   |   Model: " << c.Model << "    |   Tip: " << c.Tip << std::endl;
}

