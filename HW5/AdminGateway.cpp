//
// Created by Angel on 24.04.2021.
//

#include "AdminGateway.h"

#include <utility>

using namespace std;

AdminGateway::AdminGateway(MobileApp app) {
    this->app = std::move(app);
}

void AdminGateway::login(Admin admin) {
    if(app.authentication(admin)) {
        cout << "Admin " << admin.getName() << " has successfully logged into the application!\n";
    } else {
        cout << admin.getName() << " was unable to enter the application!\n";
    }
}

void AdminGateway::checkCars(Admin admin) {
    app.checkDriversCars(move(admin));
}

void AdminGateway::accessToTakeOrder(Admin admin, Driver driver, bool access) {
    if (!app.checkAdminAuth(admin)) {
        cout << "Authentication fail!" << endl;
        return;
    }
    app.accessToTakeOrder(driver, access);
}

void AdminGateway::accessToRide(Admin admin, Passenger passenger, bool access) {
    if (!app.checkAdminAuth(admin)) {
        cout << "Authentication fail!" << endl;
        return;
    }
    app.accessToRide(passenger, access);
}