//
// Created by Angel on 09.04.2021.
//

#include "PassengerGateway.h"

#include <iostream>
#include <algorithm>
#include <ctime>
#include <cmath>

bool PassengerGateway::login(Passenger passenger) {
    cout << "The passenger " << passenger.getName() << " tries to enter the application..." << endl;
    return app.authentication(move(passenger));
}

size_t splitStr(const std::string &txt, std::vector<std::string> &strs, char ch)
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

void PassengerGateway::showOrderHistory(Passenger passenger, Device device) {
    cout << "System check current device..." << endl;
    if (!app.checkDevice(passenger, device)) {
        cout << device.getName() << " is unknown device!" << endl;
        return;
    }

    cout << "Device is correct!" << endl;

    cout << "Getting order history from device " << device.getName() << "..." << endl;
    vector<string> orderHistory =  app.getOrderHistory(passenger);
    if (orderHistory.empty()) {
        cout << "Order history is empty!" << endl;
    }

    cout << "Order history of the " << passenger.getName() << " passenger:" << endl;
    for(int i = 0; i < orderHistory.size(); i++) {
        vector<string> tokens;
        splitStr(orderHistory[i], tokens, ' ');
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

void PassengerGateway::orderTaxiRide(Passenger passenger, string from, string to, string time) {
    try {
        app.checkPassengerAccess(passenger);
    } catch (char const* err) {
        cout << err << endl;
        return;
    }

    app.accessToRide(passenger, false);

    cout << "Passenger " << passenger.getName() << " order the ride!" << endl;
    app.addOrder(move(passenger), from, to, time);
    cout << "New order created!" << endl;
}

string PassengerGateway::getOrderTime(string from, string to) {
    vector<string> fromPos;
    vector<string> toPos;
    splitStr(from, fromPos, '/');
    splitStr(to, toPos, '/');
    int x = stoi(toPos[0]) - stoi(fromPos[0]);
    int y = stoi(toPos[1]) - stoi(fromPos[1]);
    double length = sqrt(x*x + y*y)/550;
    int minutes = (int)length;
    int seconds = (int)( ( length - floor(length) ) * pow(10, 2));
    while(seconds > 60) {
        minutes++;
        seconds -= 60;
    }
    string time;
    if(seconds<10) {
        time = to_string(minutes) + ":0" + to_string(seconds);
    } else {
        time = to_string(minutes) + ":" + to_string(seconds);
    }
    return time;
}

void PassengerGateway::addDevice(Passenger passenger, Device device) {
    app.addDevice(std::move(passenger), std::move(device));
}