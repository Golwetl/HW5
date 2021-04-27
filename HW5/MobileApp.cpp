//
// Created by Angel on 09.04.2021.
//

#include "MobileApp.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <utility>
#include <ctime>

using namespace std;

static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

size_t split(const std::string &txt, std::vector<std::string> &strs, char ch) {
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

MobileApp::MobileApp(string name) {
    this->name = move(name);
    ofstream ok("orders.txt", ios::trunc);

}

bool MobileApp::authentication(Passenger passenger) {
    string line;
    vector<string> tokens;
    ifstream file("users.txt");

    while (getline (file, line)) {
        split(line, tokens, ' ');
        if (tokens[1] == "1" && tokens[2] == passenger.getName()) {
            cout << "Authentication successful!" << endl;
            passengersInSystem.push_back(tokens);
            return true;
        }
    }

    cout << "Authentication failed!" << endl;
    return false;
}

vector<string> MobileApp::getOrderHistory(Passenger passenger) {
    vector<string> orderHistory;
    for(int i = 0; i < passengersInSystem.size();i++) {
        if(passengersInSystem[i][2] == passenger.getName()) {
            string order = "";
            for(int j = 4; j < passengersInSystem[i].size(); j++) {
                order = order + " " + passengersInSystem[i][j] ;
                if(passengersInSystem[i][j].find('}') != string::npos) {
                    break;
                }
            }
            order.erase(order.find('{'), 1);
            order.erase(order.find('}'), 1);
            split(order, orderHistory, ',');
            for(int j = 0; j < orderHistory.size(); j++) {
                trim(orderHistory[j]);
            }
            break;
        }
    }
    return orderHistory;
}

MobileApp::MobileApp() {}

bool MobileApp::authentication(Driver driver) {
    string line;
    vector<string> tokens;
    ifstream file("users.txt");

    while (getline (file, line)) {
        split(line, tokens, ' ');
        if (tokens[1] == "2" && tokens[2] == driver.getName()) {
            cout << "Authentication successful!" << endl;
            driversInSystem.push_back(tokens);
            return true;
        }
    }

    cout << "Authentication failed!" << endl;
    return false;
}

bool MobileApp::authentication(Admin admin) {
    string line;
    vector<string> tokens;
    ifstream file("users.txt");

    while (getline (file, line)) {
        split(line, tokens, ' ');
        if (tokens[1] == "3" && tokens[2] == admin.getName()) {
            adminsInSystem.push_back(tokens);
            return true;
        }
    }
    return false;
}

vector<string> MobileApp::getOrderHistory(Driver driver) {
    vector<string> orderHistory;
    for(int i = 0; i < driversInSystem.size();i++) {
        if(driversInSystem[i][2] == driver.getName()) {
            string order = "";
            for(int j = 4; j < driversInSystem[i].size(); j++) {
                order = order + " " + driversInSystem[i][j] ;
                if(driversInSystem[i][j].find('}') != string::npos) {
                    break;
                }
            }
            order.erase(order.find('{'), 1);
            order.erase(order.find('}'), 1);
            split(order, orderHistory, ',');
            for(int j = 0; j < orderHistory.size(); j++) {
                trim(orderHistory[j]);
            }
            break;
        }
    }
    return orderHistory;
}

void MobileApp::setStatus(Driver driver, bool status) {
    driver.setStatus(status);
}

bool MobileApp::getDriverStatus(Driver driver) {
    return driver.getStatus();
}

void MobileApp::addOrder(Passenger passenger, string from, string to, string time) {
    ofstream out;
    out.open("orders.txt");
    if (out.is_open()) {
        out << passenger.getName() << " " << from << " " << to << " " << time << " " << 0 << endl;
    }
}

vector<vector<string>> MobileApp::getOrders() {
    string line;
    ifstream in("orders.txt");
    if (in.is_open()) {
        while (getline(in, line)) {
            vector<string> order;
            split(line, order, ' ');
            orders.push_back(order);
        }
    }
    return orders;
}

bool MobileApp::checkDriverAuth(Driver driver) {
    if (driversInSystem.empty()) {
        cout << "Driver " << driver.getName() << " is not logged in!" << endl;
        return false;
    }

    for (auto & i : driversInSystem) {
        if (i[2] == driver.getName()) {
            return true;
        }
    }
    return false;
}

void MobileApp::validateCarRequest(Driver driver, Car car) {
    vector<string> request;
    request.push_back(driver.getName());
    request.push_back(car.getCarType());
    request.push_back(car.getModel());
    request.push_back(car.getNumber());
    request.push_back(car.getColor());

    ifstream requests;
    requests.open("requests.txt");
    ofstream temp;
    temp.open("temp.txt");
    string line;

    while(getline(requests, line)) {
        temp << line << endl;
    }

    temp << request[0] + " ";
    for (int i = 1; i < request.size(); ++i) {
        if (i+1 == request.size()) {
            temp << request[i];
            break;
        }
        temp << request[i] + "/";
    }

    temp.close();
    requests.close();
    remove("requests.txt");
    rename("temp.txt", "requests.txt");
}

bool MobileApp::checkAcceptedDriverCars(Driver driver) {
    ifstream cars;
    cars.open("cars.txt");

    string line;
    vector<string> tokens;
    while (getline(cars, line)) {
        if (line.empty()) continue;
        split(line, tokens, ' ');
        if (tokens[0] == driver.getName()) {
            for (int i = 1; i < tokens.size(); ++i) {
                vector<string> car;
                split(tokens[i], car, '/');
                if (driver.currentCar.getCarType() == car[0] && driver.currentCar.getModel() == car[1]
                        && driver.currentCar.getNumber() == car[2]
                        && driver.currentCar.getColor() == car[3]) {
                    return true;
                }
            }
        }
    }
    return false;
}

void MobileApp::checkDriversCars(Admin admin) {
    srand(time(0));
    vector<vector<string>> validationRequestCars;
    string line;
    vector<string> tokens;

    ifstream requests;
    requests.open("requests.txt");
    if(requests.peek() == ifstream::traits_type::eof()) {
        cout << "There are no request for validation of cars!" << endl;
    }

    while (getline(requests, line)) {
        split(line, tokens, ' ');
        validationRequestCars.push_back(tokens);
    }
    requests.close();
    requests.open("requests.txt", std::ofstream::out | std::ofstream::trunc);
    requests.close();

    for (vector<string> request: validationRequestCars) {
        cout << "Admin validate car of " << request[0] << endl;
        int mode = rand() % 1;
        if (mode == 0) {
            cout << "Admin accept car of driver!" << endl;
            ifstream driverCars;
            driverCars.open("cars.txt");
            ofstream temp;
            temp.open("temp.txt");

            bool noCars = true; // Case when file doesn't contain such user

            while (getline(driverCars, line)) {
                split(line, tokens, ' ');
                if (tokens[0] == request[0]) {
                    noCars = false;
                    line += " " + request[1];
                }

                temp << line << endl;
            }

            if (noCars) {
                line = request[0] + " " + request[1];
            }

            temp << line << endl;
            driverCars.close();
            temp.close();
            remove("cars.txt");
            rename("temp.txt", "cars.txt");
            return;
        }
        cout << "Admin doesn't accept car with number " << request[3] << " of " << request[0] << "!\n";
    }
}

void MobileApp::addDevice(Passenger passenger, Device device) {
    string line;
    vector<string> tokens;

    ifstream devices;
    devices.open("devicesPassenger.txt");
    ofstream temp;
    temp.open("temp.txt");

    bool noUser = true;

    while (getline(devices, line)) {
        split(line, tokens, ' ');
        if (passenger.getName() == tokens[0]) {
            noUser = false;
            for (int i = 1; i < tokens.size(); ++i) {
                if (device.getMac() == tokens[i]) {
                    cout << "The device was connected earlier!" << endl;
                    remove("temp.txt");
                    return;
                }
                if (i+1 == tokens.size()) {
                    line += " " + device.getMac();
                    cout << "Device is added!" << endl;
                }
            }
        }
        temp << line << endl;
    }

    if (noUser) {
        temp << passenger.getName() << " " << device.getMac() << endl;
        cout << "Device is added!" << endl;

    }

    temp.close();
    devices.close();
    remove("devicesPassenger.txt");
    rename("temp.txt", "devicesPassenger.txt");
}

bool MobileApp::checkDevice(Passenger passenger, Device device) {
    string line;
    vector<string> tokens;

    ifstream devices;
    devices.open("devicesPassenger.txt");

    while (getline(devices, line)) {
        split(line, tokens, ' ');
        if (passenger.getName() == tokens[0]) {
            for (int i = 1; i < tokens.size(); ++i) {
                if (device.getMac() == tokens[i]) {
                    return true;
                }
            }
            return false;
        }
    }

    return false;
}

void MobileApp::accessToRide(Passenger passenger, bool access) {
    string line;
    vector<string> tokens;
    ifstream ac;
    ac.open("accessPassengers.txt");
    ofstream temp;
    temp.open("temp.txt");

    while (getline(ac, line)) {
        split(line, tokens, ' ');
        if(tokens[0] == passenger.getName()) {
            line = tokens[0] + " ";
            if (access) {
                line += '1';
            } else {
                line += '0';
            }
        }

        temp << line << endl;
    }

    temp.close();
    ac.close();
    remove("accessPassengers.txt");
    rename("temp.txt", "accessPassengers.txt");
}

void MobileApp::accessToTakeOrder(Driver driver, bool access) {
    string line;
    vector<string> tokens;
    ifstream ac;
    ac.open("accessDrivers.txt");
    ofstream temp;
    temp.open("temp.txt");

    while (getline(ac, line)) {
        split(line, tokens, ' ');
        if(tokens[0] == driver.getName()) {
            line = tokens[0] + " ";
            if (access) {
                line += '1';
            } else {
                line += '0';
            }
        }

        temp << line << endl;
    }

    temp.close();
    ac.close();
    remove("accessDrivers.txt");
    rename("temp.txt", "accessDrivers.txt");
}

void MobileApp::checkDriverAccess(Driver driver) {
    if (!driver.getAccess()) {
        throw "Driver doesn't has access!";
    }
}

void MobileApp::checkPassengerAccess(Passenger passenger) {
    if (!passenger.getAccess()) {
        throw "Passenger was blocked by admin!";
    }
}

void MobileApp::writeOrderToHistory(Driver driver, Passenger passenger, vector<string> &currentOrder) {
    string line;
    string thisOrder = "," + currentOrder[1] + " " + currentOrder[2] + " cash} ";

    vector<string> tokens;
    ifstream users;
    users.open("users.txt");
    ofstream temp;
    temp.open("temp.txt");

    while (getline(users, line)) {
        split(line, tokens, ' ');
        //Change history for passenger
        if (tokens[1] == "1" && tokens[2] == passenger.getName()) {
            string order;
            for (int i = 0; i < 4; ++i) {
                order += tokens[i] + " ";
            }
            for (int i = 4; i < tokens.size(); ++i) {
                order += tokens[i] + " ";
                if (tokens[i].find('}') != string::npos) {
                    order.erase(order.end()-2, order.end());
                    order += thisOrder;
                }
            }
            line = order;
        }

        if (tokens[1] == "2" && tokens[2] == driver.getName()) {
            string order;
            for (int i = 0; i < 4; ++i) {
                order += tokens[i] + " ";
            }
            for (int i = 4; i < tokens.size(); ++i) {
                order += tokens[i] + " ";
                if (tokens[i].find('}') != string::npos) {
                    order.erase(order.end()-2, order.end());
                    order += thisOrder;
                }
            }
            line = order;
        }

        temp << line << endl;
    }

    temp.close();
    users.close();
    remove("users.txt");
    rename("temp.txt", "users.txt");
}

bool MobileApp::checkAdminAuth(Admin admin) {
    for (vector<string> ad: adminsInSystem) {
        if (ad[2] == admin.getName()) {
            return true;
        }
    }
    return false;
}
