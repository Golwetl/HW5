//
// Created by Angel on 24.04.2021.
//

#include "Device.h"

Device::Device(string name, string macAddress) {
    this->name = move(name);
    this->macAddress = move(macAddress);
}

string Device::getMac() {
    return macAddress;
}

bool Device::operator==(Device other) {
    if(other.macAddress == macAddress) return true;
    return false;
}

string Device::getName() {
    return name;
}
