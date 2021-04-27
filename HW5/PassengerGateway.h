
#ifndef HOMEWORK4_PASSENGERGATEWAY_H
#define HOMEWORK4_PASSENGERGATEWAY_H
#include <string>
#include <vector>
#include "Passenger.h"
#include "MobileApp.h"

using namespace std;

class PassengerGateway {
public:
    MobileApp app;

    explicit PassengerGateway(MobileApp app) { this->app = app; }

    bool login(Passenger passenger);

    void choosePaymentMethod(Passenger passenger);

    void showOrderHistory(Passenger passenger, Device device);

    void orderTaxiRide(Passenger passenger, string from, string to, string time);

    string getOrderTime(string from, string to);

    void addDevice(Passenger passenger, Device device);
};


#endif //HOMEWORK4_PASSENGERGATEWAY_H
