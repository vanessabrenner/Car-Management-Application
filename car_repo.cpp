#include "car_repo.h"

#include <assert.h>

void CarRepo::store(const Car& c) {
	if (exist(c)) {
		throw CarRepoException("Exista deja masina cu numarul de inmatriculare: " + c.getNrInmatriculare());
	}
	this->all.push_back(c);
}

bool CarRepo::exist(const Car& c) {
	try {
		find(c.getNrInmatriculare());
		return true;
	}
	catch (CarRepoException&) {
		return false;
	}
}

void CarRepo::remove(const Car& c) {
	/*MyList<Car> newlist;
	for (int i = 0; i < this->all.size(); i++) {
		if (this->all.get(i).getNrInmatriculare() != c.getNrInmatriculare())
			newlist.push_back(this->all.get(i));
	}
	this->all = newlist;*/

	vector<Car>::iterator f = std::remove_if(this->all.begin(), this->all.end(),
		[=](const Car& car) {
			return car.getNrInmatriculare() == c.getNrInmatriculare();
		});
	this->all.erase(f);
}

void CarRepo::modify(const Car& c, string Producator, string Model, int Tip) {
	/*for (auto& car : this->all) {
		if (car.getNrInmatriculare() == c.getNrInmatriculare()) {
			car.setProducator(Producator);
			car.setModel(Model);
			car.setTip(Tip);
		}
	}*/
	vector<Car>::iterator f = std::find_if(this->all.begin(), this->all.end(),
		[=](const Car& car) {
			return car.getNrInmatriculare() == c.getNrInmatriculare();
		});

	(*f).setProducator(Producator);
	(*f).setModel(Model);
	(*f).setTip(Tip);
}

const Car& CarRepo::find(string NrInmatriculare) {
	/*for (const auto& car : this->all) {
		if (car.getNrInmatriculare() == NrInmatriculare)
			return car;
	}*/
	vector<Car>::iterator f = std::find_if(this->all.begin(), this->all.end(),
		[=](const Car& c) {
			return c.getNrInmatriculare() == NrInmatriculare;
		});

	if (f != this->all.end())
		return(*f);
	else
		// aruncam exceptie daca nu l gasim
		throw CarRepoException("Nu exista in lista masina cu numarul de inmatriculare: " + NrInmatriculare);
}

const vector<Car> CarRepo::getAll() {
	vector<Car> cars;
	for (auto const &car : this->all) {
		cars.push_back(car);
	}
	return cars;
}

// repo file ****************************************

void CarRepoFile::load_from_file() {
	ifstream fin(nume_fisier);
	CarRepo::emptyRepo();
	if (!fin.is_open()) {
		throw CarRepoException("Eroare la deschiderea fisierului: " + nume_fisier);
	}

	while (!fin.eof()) {
		string NrInmatriculare;
		fin >> NrInmatriculare;

		// daca gasim linii goale
		if (fin.eof())
			break;
		string Producator;
		fin >> Producator;
		string Model;
		fin >> Model;
		int Tip;
		fin >> Tip;

		Car c(NrInmatriculare, Producator, Model, Tip);
		CarRepo::store(c);
	}

	fin.close();
}

void CarRepoFile::write_to_file() {
	ofstream fout(nume_fisier);
	if (!fout.is_open()) {
		throw CarRepoException("Eroare la deschiderea fisierului " + nume_fisier);
	}

	for (auto& car : CarRepo::getAll()) {
		fout << car.getNrInmatriculare() << ' ' << car.getProducator() << ' ' << car.getModel() << ' ' << car.getTip() << std::endl;
	}

	fout.close();
}

ostream& operator<<(ostream& out, const CarRepoException& exc) {
	out << exc.msg;
	return out;
}

// pentru RepoLab...................................

void RepoLab::store(const Car& c) {
	double lower_bound = 0;
	double upper_bound = 1;
	std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
	std::default_random_engine re;
	double a_random_double = unif(re);

	if (a_random_double < get_prob()) {
		throw CarRepoException("Probabilitate " + std::to_string(a_random_double) + " sub cea data");
	}

	if (exist(c)) {
		throw CarRepoException("Exista deja masina cu numarul de inmatriculare: " + c.getNrInmatriculare());
	}
	this->all.insert(pair<string, Car>(c.getNrInmatriculare(), c));
}

bool RepoLab::exist(const Car& c) {
	try {
		find(c.getNrInmatriculare());
		return true;
	}
	catch (CarRepoException&) {
		return false;
	}
}

void RepoLab::remove(const Car& c) {

	double lower_bound = 0;
	double upper_bound = 1;
	std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
	std::default_random_engine re;
	double a_random_double = unif(re);

	if (a_random_double < get_prob()) {
		throw CarRepoException("Probabilitate " + std::to_string(a_random_double) + " sub cea data");
	}

	this->all.erase(c.getNrInmatriculare());
}

void RepoLab::modify(const Car& c, string Producator, string Model, int Tip) {

	double lower_bound = 0;
	double upper_bound = 1;
	std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
	std::default_random_engine re;
	double a_random_double = unif(re);

	if (a_random_double < get_prob()) {
		throw CarRepoException("Probabilitate " + std::to_string(a_random_double) + " sub cea data");
	}
	all[c.getNrInmatriculare()].setProducator(Producator);
	all[c.getNrInmatriculare()].setModel(Model);
	all[c.getNrInmatriculare()].setTip(Tip);
}

const Car& RepoLab::find(string NrInmatriculare) {

	double lower_bound = 0;
	double upper_bound = 1;
	std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
	std::default_random_engine re;
	double a_random_double = unif(re);

	if (a_random_double < get_prob()) {
		throw CarRepoException("Probabilitate " + std::to_string(a_random_double) + " sub cea data");
	}

	for (const auto& car : this->all) {
		if (car.first == NrInmatriculare)
			return all[NrInmatriculare];
	}

	throw CarRepoException(("Nu exista in lista masina cu numarul de inmatriculare: " + NrInmatriculare));
}

const vector<Car> RepoLab::getAll() {
	double lower_bound = 0;
	double upper_bound = 1;
	std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
	std::default_random_engine re;
	double a_random_double = unif(re);

	if (a_random_double < get_prob()) {
		throw CarRepoException("Probabilitate " + std::to_string(a_random_double) + " sub cea data");
	}

	vector<Car> cars;
	for (auto const& car : this->all) {
		cars.push_back(car.second);
	}
	return cars;
}

