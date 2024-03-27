#pragma once
#include <vector>
#include <algorithm>

using std::vector;
using std::remove;

/**
 * @brief Clasa abstracta pt Observer
*/
class Observer {
public:
	virtual void update() = 0;
};


class Observable{
private:
	vector <Observer*> observers;
public:
	void addObserver(Observer* obs) {
		observers.push_back(obs);
	}
	void removeObserver(Observer* obs) {
		observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
	}
	void notify() {
		for (auto obs : observers)
			obs->update();
	}
};