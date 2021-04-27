//
// Created by Angel on 24.04.2021.
//

#include "Admin.h"

using namespace std;

Admin::Admin(string name) {
    this->name = move(name);
}

string Admin::getName() {
    return name;
}
