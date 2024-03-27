#include "car_domain.h"
#include "car_validator.h"
#include "car_repo.h"
#include "car_service.h"
#include "undo.h"

#include <assert.h>
#include <iostream>

using std::cout;

// domain
void test_car_domain() {
	Car c{ "MM23VAP", "VW", "Passat", 9 };

	assert(c.getNrInmatriculare() == "MM23VAP");
	assert(c.getProducator() == "VW");
	assert(c.getModel() == "Passat");
	assert(c.getTip() == 9);
}

// validator
void test_car_validator() {
	CarRepoFile repo("testRepo.txt");
	repo.emptyRepo();
	CarValidator val;
	CarService srv{ repo,val };

	try {
		srv.addCar("", "VW", "Passat", 9);
		assert(false);
	}
	catch (CarValidatorException) {
		assert(true);
	}

	try {
		srv.addCar("MM23VAP", "", "Passat", 9);
		assert(false);
	}
	catch (CarValidatorException) {
		assert(true);
	}

	try {
		srv.addCar("MM23VAP", "VW", "", 9);
		assert(false);
	}
	catch (CarValidatorException) {
		assert(true);
	}

	try {
		srv.addCar("MM23VAP", "VW", "Passat", -10);
		assert(false);
	}
	catch (CarValidatorException) {
		assert(true);
	}

	try {
		srv.addCar("", "", "", -10);
		assert(false);
	}
	catch (CarValidatorException) {
		assert(true);
	}

	assert(srv.getAll().size() == 0);
}

// repository
void test_add_car_repo() {
	CarRepoFile repo("testRepo.txt");
	repo.emptyRepo();

	Car c1{ "MM23VAP", "VW", "Passat", 9 };
	repo.store(c1);

	Car c2{ "MM01SAR", "BMW", "Q", 9 };
	repo.store(c2);

	Car c3{ "MM02HSA", "Nissan", "Juke", 9 };
	repo.store(c3);

	//cout << repo.getAll().size();
	assert(repo.getAll().size() == 3);

	try {
		Car c4{ "MM02HSA", "Nissan", "Juke", 9 };
		repo.store(c4);
		assert(false);
	}
	catch (CarRepoException) {
		assert(true);
	}
}

void test_remove_car_repo() {
	CarRepoFile repo("testRepo.txt");
	repo.emptyRepo();

	Car c1{ "MM23VAP", "VW", "Passat", 9 };
	repo.store(c1);

	Car c2{ "MM01SAR", "BMW", "Q", 9 };
	repo.store(c2);

	Car c3{ "MM02HSA", "Nissan", "Juke", 9 };
	repo.store(c3);

	repo.remove(c1);

	assert(repo.getAll().size() == 2);

	repo.remove(c3);
	assert(repo.getAll().size() == 1);
}

void test_modify_car_repo() {
	CarRepoFile repo("testRepo.txt");
	repo.emptyRepo();

	Car c1{ "MM23VAP", "VW", "Passat", 9 };
	repo.store(c1);

	Car c2{ "MM01SAR", "BMW", "Q", 9 };
	repo.store(c2);

	Car c3{ "MM02HSA", "Nissan", "Juke", 9 };
	repo.store(c3);

	repo.modify(c1, "Mercedes", "CLS", 10);
	assert(repo.getAll()[0].getProducator() == "Mercedes");
	assert(repo.getAll()[0].getModel() == "CLS");
	assert(repo.getAll()[0].getTip() == 10);

	repo.modify(c3, "VW", "Passat", 4);
	assert(repo.getAll()[2].getProducator() == "VW");
	assert(repo.getAll()[2].getModel() == "Passat");
	assert(repo.getAll()[2].getTip() == 4);

	assert(repo.getAll().size() == 3);
}

void test_find_car_repo() {
	CarRepoFile repo("testRepo.txt");
	repo.emptyRepo();

	Car c1{ "MM23VAP", "VW", "Passat", 9 };
	repo.store(c1);

	Car c2{ "MM01SAR", "BMW", "Q", 9 };
	repo.store(c2);

	Car c3{ "MM02HSA", "Nissan", "Juke", 9 };
	repo.store(c3);

	assert(repo.find("MM23VAP").getProducator() == "VW");
	assert(repo.find("MM23VAP").getModel() == "Passat");
	assert(repo.find("MM23VAP").getTip() == 9);

	try {
		repo.find("CJ01VAP");
		assert(false);
	}
	catch (CarRepoException) {
		assert(true);
	}
}

// service
void test_add_car_srv() {
	CarRepoFile repo("testRepo.txt");
	repo.emptyRepo();
	CarValidator val;
	CarService srv{ repo,val };

	srv.addCar("MM23VAP", "VW", "Passat", 9);
	srv.addCar("MM01SAR", "BMW", "Q", 9);
	srv.addCar("MM02HSA", "Nissan", "Juke", 9);

	assert(srv.getAll().size() == 3);
}

void test_remove_car_srv() {
	CarRepoFile repo("testRepo.txt");
	repo.emptyRepo();
	CarValidator val;
	CarService srv{ repo,val };

	srv.addCar("MM23VAP", "VW", "Passat", 9);
	srv.addCar("MM01SAR", "BMW", "Q", 9);
	srv.addCar("MM02HSA", "Nissan", "Juke", 9);

	srv.removeCar("MM23VAP");
	assert(srv.getAll().size() == 2);

	srv.removeCar("MM02HSA");
	assert(srv.getAll().size() == 1);

	try {
		srv.removeCar("CJ01VAP");
		assert(false);
	}
	catch (CarRepoException) {
		assert(true);
	}
}

void test_modify_car_srv() {
	CarRepoFile repo("testRepo.txt");
	repo.emptyRepo();
	CarValidator val;
	CarService srv{ repo,val };

	srv.addCar("MM23VAP", "VW", "Passat", 9);
	srv.addCar("MM01SAR", "BMW", "Q", 9);
	srv.addCar("MM02HSA", "Nissan", "Juke", 9);

	srv.modifyCar("MM23VAP", "Mercedes", "CLS", 10);
	assert(repo.getAll()[0].getProducator() == "Mercedes");
	assert(repo.getAll()[0].getModel() == "CLS");
	assert(repo.getAll()[0].getTip() == 10);

	srv.modifyCar("MM02HSA", "VW", "Passat", 4);
	assert(repo.getAll()[2].getProducator() == "VW");
	assert(repo.getAll()[2].getModel() == "Passat");
	assert(repo.getAll()[2].getTip() == 4);

	assert(srv.getAll().size() == 3);

	try {
		srv.modifyCar("CJ01VAP", "VW", "Passat", 9);
		assert(false);
	}
	catch (CarRepoException) {
		assert(true);
	}
}

void test_find_car_srv() {
	CarRepoFile repo("testRepo.txt");
	repo.emptyRepo();
	CarValidator val;
	CarService srv{ repo,val };

	srv.addCar("MM23VAP", "VW", "Passat", 9);
	srv.addCar("MM01SAR", "BMW", "Q", 9);
	srv.addCar("MM02HSA", "Nissan", "Juke", 9);

	assert(srv.findCar("MM23VAP").getProducator() == "VW");
	assert(srv.findCar("MM23VAP").getModel() == "Passat");
	assert(srv.findCar("MM23VAP").getTip() == 9);

	try {
		srv.findCar("CJ01VAP");
		assert(false);
	}
	catch (CarRepoException) {
		assert(true);
	}
}

void test_filter_srv() {
	// tip si producator

	CarRepoFile repo("testRepo.txt");
	repo.emptyRepo();
	CarValidator val;
	CarService srv{ repo,val };

	srv.addCar("MM23VAP", "VW", "Passat", 10);
	srv.addCar("MM01SAR", "VW", "Bora", 9);
	srv.addCar("MM02HSA", "Nissan", "Juke", 9);

	vector<Car> filtredlist1 = srv.filtrareTip(9);
	assert(filtredlist1.size() == 2);

	vector<Car> filtredlist2 = srv.filtrareTip(10);
	assert(filtredlist2.size() == 1);

	vector<Car> filtredlist3 = srv.filtrareTip(3);
	assert(filtredlist3.size() == 0);


	vector<Car> filtredlist4 = srv.filtrareProducator("VW");
	assert(filtredlist4.size() == 2);

	vector<Car> filtredlist5 = srv.filtrareProducator("Nissan");
	assert(filtredlist5.size() == 1);

	vector<Car> filtredlist6 = srv.filtrareProducator("Mercedes");
	assert(filtredlist6.size() == 0);
}

void test_sort_srv() {
	CarRepoFile repo("testRepo.txt");
	repo.emptyRepo();
	CarValidator val;
	CarService srv{ repo,val };

	srv.addCar("MM23VAP", "VW", "Passat", 10);
	srv.addCar("CJ01SAR", "Mercedes", "S", 1);
	srv.addCar("B100HSA", "Mercedes", "CLS", 15);
	srv.addCar("SM15VAP", "BMW", "M", 5);
	srv.addCar("AB89SAR", "Audi", "R", 8);

	vector<Car> sortedlist1 = srv.sortareNrInmatriculare();
	assert(sortedlist1[0].getNrInmatriculare() == "AB89SAR");
	assert(sortedlist1[1].getNrInmatriculare() == "B100HSA");
	assert(sortedlist1[2].getNrInmatriculare() == "CJ01SAR");
	assert(sortedlist1[3].getNrInmatriculare() == "MM23VAP");
	assert(sortedlist1[4].getNrInmatriculare() == "SM15VAP");

	vector<Car> sortedlist2 = srv.sortareTip();
	assert(sortedlist2[0].getTip() == 1);
	assert(sortedlist2[1].getTip() == 5);
	assert(sortedlist2[2].getTip() == 8);
	assert(sortedlist2[3].getTip() == 10);
	assert(sortedlist2[4].getTip() == 15);

	vector<Car> sortedlist3 = srv.sortareProducator_Model();
	assert(sortedlist3[0].getModel() == "R");
	assert(sortedlist3[1].getModel() == "M");
	assert(sortedlist3[2].getModel() == "CLS");
	assert(sortedlist3[3].getModel() == "S");
	assert(sortedlist3[4].getModel() == "Passat");

}

// garage
//void test_garage() {
//	CarRepoFile repo("testRepo.txt");
//	repo.emptyRepo();
//	CarValidator val;
//	CarService service{ repo,val };
//
//	service.addCar("CJ09VAN", "VW", "Golf", 3);
//	service.addCar("MM05NHJ", "BMW", "X5", 8);
//	service.addCar("B100GHI", "Audi", "Q7", 5);
//	service.addCar("PH67HAA", "Dacia", "Sandero", 4);
//	service.addCar("SM45MUN", "Renault", "Clio", 3);
//	service.addCar("CJ12ALN", "Volvo", "XC", 60);
//
//	service.write_to_file("garage.txt");
//
//	service.addRandomCars(4);
//	assert(service.getAllGarageCars().size() == 4);
//	service.emptyGarage();
//	assert(service.getAllGarageCars().size() == 0);
//
//	service.addRandomCars(20);
//
//	assert(service.getAllGarageCars().size() == 6);
//
//	service.emptyGarage();
//	service.addCarToGarage("MM05NHJ");
//	assert(service.getAllGarageCars().size() == 1);
//
//	try {
//		service.addCarToGarage("MM23VAP");
//		assert(false);
//	}
//	catch (CarRepoException&) {
//		assert(true);
//	}
//
//}

void test_undo() {
	CarRepoFile repo{ "testRepo.txt" };
	repo.emptyRepo();
	CarValidator val;
	CarService srv{ repo, val };

	srv.addCar("CJ09VAN", "VW", "Golf", 3);
	srv.addCar("MM05NHJ", "BMW", "X5", 8);
	srv.addCar("B100GHI", "Audi", "Q7", 5);

	assert(srv.getAll().size() == 3);
	srv.undo();
	assert(srv.getAll().size() == 2);

	srv.removeCar("MM05NHJ");
	assert(srv.getAll().size() == 1);
	srv.undo();
	assert(srv.getAll().size() == 2);

	srv.modifyCar("MM05NHJ", "Audi", "Q7", 5);
	srv.undo();
	assert(srv.getAll().size() == 2);
	assert(srv.getAll()[1].getNrInmatriculare() == "MM05NHJ");
	assert(srv.getAll()[1].getProducator() == "BMW");
	assert(srv.getAll()[1].getModel() == "X5");
	assert(srv.getAll()[1].getTip() == 8);
}

void testAll() {
	// domain
	test_car_domain();
	// validator
	test_car_validator();
	// repository
	test_add_car_repo();
	test_remove_car_repo();
	test_modify_car_repo();
	test_find_car_repo();
	// service
	test_add_car_srv();
	test_remove_car_srv();
	test_modify_car_srv();
	test_find_car_srv();
	test_filter_srv();
	test_sort_srv();
	// garage
	//test_garage();
	// undo
	test_undo();

	cout << "Teste trecute!\n";
}