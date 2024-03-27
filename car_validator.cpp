#include "car_validator.h"

#include <assert.h>

using std::string;

void CarValidator::validate(const Car& c) {
	vector<string> msgs;
	if (c.getNrInmatriculare().size() == 0)
		msgs.push_back("Numar de inmatriculare invalid!");
	if (c.getProducator().size() == 0)
		msgs.push_back("Producator invalid!");
	if (c.getModel().size() == 0)
		msgs.push_back("Model invalid!");
	if (c.getTip() <= 0)
		msgs.push_back("Tip invalid!");

	if (msgs.size() != 0)
		throw CarValidatorException(msgs);

}

ostream& operator<<(ostream& out, const CarValidatorException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << '\n';
	}
	return out;
}
