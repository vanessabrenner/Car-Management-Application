#pragma once

#include <stack>
#include "car_repo.h"
#include "car_domain.h"


class UndoAction {
public:
	// functie virtuala de undo la ultima modificare
	virtual void do_undo() = 0;
	// destructor virtual pentru fiecare obiect derivat din acesta
	virtual ~UndoAction() {};
};

class UndoAdd :public UndoAction {
private:
	Car addedCar;
	RepoAbstract& repo;
public:
	UndoAdd(Car& c, RepoAbstract& r) : addedCar{ c }, repo{ r } {};
	void do_undo() override {
		repo.remove(addedCar);
	}
};

class UndoRemove :public UndoAction {
private:
	Car removedCar;
	RepoAbstract& repo;
public:
	UndoRemove(Car& c, RepoAbstract& r) : removedCar{ c }, repo{ r } {};
	void do_undo() override {
		repo.store(removedCar);
	}
};

class UndoModify :public UndoAction {
private:
	Car old_car;
	RepoAbstract& repo;
public:
	UndoModify(Car& _old_car, RepoAbstract& r) : old_car{ _old_car }, repo{ r } {};
	void do_undo() override {
		repo.modify(old_car, old_car.getProducator(), old_car.getModel(), old_car.getTip());
	}

};

class MyUndoActions : public UndoAction {
private:
	std::stack<UndoAction*> actions;
public:
	MyUndoActions() : UndoAction() {};
	void add_undoAction(UndoAction* ua) {
		actions.push(ua);
	}
	void do_undo() override {
		actions.top()->do_undo();
		actions.pop();
	}

	size_t size() noexcept {
		return actions.size();
	}
};
