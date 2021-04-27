//
// Created by Angel on 10.04.2021.
//

#ifndef HOMEWORK4_DRIVER_H
#define HOMEWORK4_DRIVER_H

#include <string>
#include <utility>
#include <vector>
#include "Car.h"

using namespace std;

class Driver {
public:
    vector<Car> cars;

    Car currentCar;

    explicit Driver(string name, Car car);

    explicit Driver(string name, vector<Car> cars);

    Car getCar();

    vector<Car> getCars();

    void addCar(Car car);

    void chooseCar(Car car);

    void removeCar(Car car);

    string getName();

    bool getStatus();

    void setStatus(bool status);

    bool getAccess();
private:
    string name;
    bool status =  false;
};

#endif //HOMEWORK4_H