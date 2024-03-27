#pragma once

#include <map>
#include <vector>

#include "car_domain.h"

using std::map;
using std::vector;

class CountMap {
private:
	map<string, vector<Car>> Producatori;
public:

	CountMap() = default;

	map<string, vector<Car>> CountCarsProducator(vector<Car> cars);
};