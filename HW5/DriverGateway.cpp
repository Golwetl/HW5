//
// Created by Angel on 12.04.2021.
//

#include "DriverGateway.h"

#include <fstream>
#include <ctime>
#include <cmath>

using namespace std;

bool DriverGateway::login(Driver driver) {
    cout << "The driver " << driver.getName() << " tries to enter the application..." << endl;
    return app.authentication(move(driver));
}

size_t getTokens(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}

void DriverGateway::showOrderHistory(Driver driver) {
    if (!checkAuth(driver)) {return;}

    cout << "Getting order history from..." << endl;
    vector<string> orderHistory =  app.getOrderHistory(driver);
    if (orderHistory.empty()) {
        cout << "Order history is empty!" << endl;
    }

    cout << "Order history of the " << driver.getName() << " driver:" << endl;
    for(int i = 0; i < orderHistory.size(); i++) {
        vector<string> tokens;
        getTokens(orderHistory[i], tokens, ' ');
        cout << "Order #" << i+1 << endl;
        cout << "From " << tokens[0] << " to " << tokens[1] << endl;
        cout << "Payment method: ";
        if(tokens[2] == "card:") {
            cout << "card" << endl;
            cout << "Card number: " << tokens[3] << endl;
        } else {
            cout << "cash" << endl;
        }
    }
}

void DriverGateway::updateStatus(Driver driver, bool status) {
    if (!checkAuth(driver)) {return;}

    if(status) {
        cout << "Driver " << driver.getName() << " is online!" << endl;
    } else {
        cout << "Driver " << driver.getName() << " is offline!" << endl;
    }

    app.setStatus(move(driver), status);
}

void DriverGateway::showCarInfo(Driver driver) {
    if (!checkAuth(driver)) {return;}

    cout << "Car information!" << endl;
    cout << "Model: " << driver.getCar().getModel() << endl;
    cout << "Number: " << driver.getCar().getNumber() << endl;
    cout << "Car Type: " << driver.getCar().getCarType() << endl;
    cout << "Color: " << driver.getCar().getColor() << endl;
}

void DriverGateway::getOrders() {
    orders = app.getOrders();
}

void DriverGateway::showOrders(Driver driver) {
    if (!checkAuth(driver)) { return; }

    getOrders();

    if (orders.empty()) {
        cout << "There no available orders!" << endl;
        return;
    }
    cout << "Available orders" << endl;

    for(int i = 0; i < orders.size(); i++) {
        vector<string> fromPos;
        vector<string> toPos;
        getTokens(orders[i][1], fromPos, '/');
        getTokens(orders[i][2], toPos, '/');
        int x = stoi(toPos[0]) - stoi(fromPos[0]);
        int y = stoi(toPos[1]) - stoi(fromPos[1]);
        double length = sqrt(x*x + y*y);
        double cost;
        switch (driver.getCar().carType) {
            case 1:
                cost = length*0.5;
                break;
            case 2:
                cost = length;
                break;
            case 3:
                cost = length*1.5;
                break;
            case 4:
                cost = length*2;
        }

        cout << "Order #" << i+1 << endl;
        cout << "Client name: " << orders[i][0] << endl;
        cout << "From: " << orders[i][1] << endl;
        cout << "To: " << orders[i][2] << endl;
        cout << "Time: " << orders[i][3] << endl;
        cout.precision(3);
        cout << "Cost: " << cost << "$" << endl;
    }
}

bool DriverGateway::checkAuth(Driver driver) {
    if (!app.checkDriverAuth(driver)) {
        cout << "Driver " << driver.getName() << " is not logged in!" << endl;
        return false;
    }
    return true;
}

int getRandomNm(int min, int max){ return min + rand() % max; }

void DriverGateway::takeOrder(Driver driver, Passenger passenger ,int orderId) {
    try {
        app.checkDriverAccess(driver);
    } catch (char const* err) {
        cout << err << endl;
        return;
    }

    app.accessToTakeOrder(driver, false);

    if (!app.checkAcceptedDriverCars(driver)) {
        cout << "Driver " << driver.getName() << " doesn't has accepted cars!" << endl;
        return;
    }

    cout << "Driver " << driver.getName() << " has accepted cars!" << endl;

    app.activeOrders.push_back(orders[orderId]);

    app.writeOrderToHistory(driver, passenger, orders[orderId]);

    app.orders.erase(app.orders.begin() + orderId);
    driver.setStatus(false);
    cout << "Driver " << driver.getName() << " take the order!" << endl;
    cout << "Order information:" << endl;
    cout << "Client name: " << orders[orderId][0] << endl;
    cout << "From: " << orders[orderId][1] << endl;
    cout << "To: " << orders[orderId][2] << endl;
    cout << "Approximate time: " << orders[orderId][3] << endl;

    ride(orderId, passenger, driver);

    if (orders.size() == 1) {
        orders.pop_back();
    } else {
        app.orders.erase(app.orders.begin() + orderId);
    }
}

int DriverGateway::getOrderNumber() {
    return orders.size();
}

void DriverGateway::getCurrentCoordinates(double length, double partOfLength, int x, int y, vector<string> fromPos) {
    cout << "Passenger wants get current coordinates!" << endl;
    double angle = asin(stod(fromPos[0])/length);
    x = sin(angle) * partOfLength + stoi(fromPos[0]);
    y = cos(angle) * partOfLength + stoi(fromPos[1]);

    cout << "Current coordinates: " << x << "/" << y << endl;
}

bool DriverGateway::ride(int orderId, Passenger passenger, Driver driver) {
    vector<string> fromPos;
    vector<string> toPos;
    getTokens(orders[orderId][1], fromPos, '/');
    getTokens(orders[orderId][2], toPos, '/');
    int x = stoi(toPos[0]) - stoi(fromPos[0]);
    int y = stoi(toPos[1]) - stoi(fromPos[1]);
    double length = sqrt(x*x + y*y);

    cout << "Order execution!" << endl;

    time_t pref_timestart = time(0);
    vector<string> time;
    getTokens(orders[orderId][3], time, ':');
    int seconds = stoi(time[0])*60 + stoi(time[1]);
    int pref_timeduration;
    bool once = true;
    int randomTime = getRandomNm(1, seconds-1);
    do {
        time_t pref_timefinish = std::time(0);
        pref_timeduration = pref_timefinish - pref_timestart;
        if(pref_timeduration == randomTime && once) {
            double partOfLength = (length/seconds)*pref_timeduration;
            getCurrentCoordinates(length, partOfLength, x, y, fromPos);
            once = false;
        }
    } while (pref_timeduration < seconds);

    cout << "Client delivered!" << endl;

    app.accessToTakeOrder(driver, true);
    app.accessToRide(passenger, true);
}

void DriverGateway::checkCar(Driver driver, Car car) {
    app.validateCarRequest(driver, car);
}