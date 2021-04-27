//
// Created by Angel on 24.04.2021.
//

#ifndef HOMEWORK4_ADMINGATEWAY_H
#define HOMEWORK4_ADMINGATEWAY_H


#include "MobileApp.h"
#include "Admin.h"

class AdminGateway {
public:
    MobileApp app;

    explicit AdminGateway(MobileApp app);

    void login(Admin admin);

    void checkCars(Admin admin);

    void accessToRide(Admin admin, Passenger passenger, bool access);

    void accessToTakeOrder(Admin admin, Driver driver, bool access);
};


#endif //HOMEWORK4_ADMINGATEWAY_H