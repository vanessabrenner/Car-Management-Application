#include "CountMap.h"

map<string, vector<Car>> CountMap::CountCarsProducator(vector<Car> AllCars) {
	Producatori.clear();
	for (auto car : AllCars) {
		Producatori[car.getProducator()].push_back(car);
	}	
	return Producatori;
}
