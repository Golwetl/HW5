//
// Created by Angel on 12.04.2021.
//

#ifndef HOMEWORK4_CAR_H
#define HOMEWORK4_CAR_H

#include <string>
#include <utility>
#include <iostream>
#include "Passenger.h"

using namespace std;

class Car {
public:
    int carType;

    enum Colors {
        YELLOW = 1,
        BLACK,
        WHITE,
        GRAY,
        RED,
        PINK
    };

    enum CarType {
        Economy = 1,
        Comfort,
        ComfortPlus,
        Business
    };

    Car(string model, string number, Colors color, CarType carType, string current_coordinates);
    Car();

    string getModel() { return model; }
    string getCarType() const {
        switch (carType) {
            case 1: return "Economy";
            case 2: return "Comfort";
            case 3: return "Comfort Plus";
            case 4: return "Business";
        }
    }
    string getNumber() { return number; }
    string getColor() const {
        switch (color) {
            case 1: return "Yellow";
            case 2: return "Black";
            case 3: return "White";
            case 4: return "Gray";
            case 5: return "Red";
            case 6: return "Pink";
        }
    }

    string getCurrentCoordinates() { return current_coordinates; }

    bool operator==(Car other);
private:
    string model;
    string number;
    int color;
    string current_coordinates;
    bool adminCheck = false;
};

class EconomyCar: public Car {
public:
    EconomyCar(string model, string number, Colors color, string current_coordinates)
            :Car(move(model), move(number), color, Car::Economy, move(current_coordinates)){}
};

class ComfortCar: public Car {
public:
    int freeBottleOfwater = 0;

    ComfortCar(string model, string number, Colors color, string current_coordinates)
            :Car(move(model), move(number), color, Car::Comfort, move(current_coordinates)){}

    void BuyBottlesOfWater(int count) { freeBottleOfwater = freeBottleOfwater + count; }

    bool takeBottleOfWater(Passenger passenger) {
        if(freeBottleOfwater > 0) {
            freeBottleOfwater--;
            cout << "Driver give bottle of water to the passenger!" << endl;
        } else {
            cout << "Bottles of water ran out!" << endl;
        }
    }
};

class ComfortPlusCar: public Car {
public:
    ComfortPlusCar(string model, string number, Colors color, string current_coordinates)
            :Car(move(model), move(number), color, Car::ComfortPlus, move(current_coordinates)){}
};

class BusinessCar: public Car {
public:
    BusinessCar(string model, string number, Colors color, string current_coordinates)
            :Car(move(model), move(number), color, Car::Business, move(current_coordinates)){}

    void parkRightInFrontOfTheEntrance(Passenger passenger) {

    }
};

#endif //HOMEWORK4_CAR_H