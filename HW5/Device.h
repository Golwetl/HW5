//
// Created by Angel on 24.04.2021.
//

#ifndef HOMEWORK4_DEVICE_H
#define HOMEWORK4_DEVICE_H

#include <string>

using namespace std;

class Device {
private:
    string macAddress;
    string name;
public:
    Device(string name, string macAddress);

    string getMac();
    string getName();

    bool operator==(Device other);
};


#endif //HOMEWORK4_DEVICE_H
