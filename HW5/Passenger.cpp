//
// Created by Angel on 09.04.2021.
//

#include <fstream>
#include "Passenger.h"

size_t splitToToken(const std::string &txt, std::vector<std::string> &strs, char ch){
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

Passenger::Passenger(string name) {
    this->name = move(name);
}

string Passenger::getName() {
    return name;
}

bool Passenger::getAccess() {
    string line;
    vector<string> tokens;

    ifstream ac;
    ac.open("accessPassengers.txt");

    while (getline(ac, line)) {
        splitToToken(line, tokens, ' ');
        if (tokens[0] == name) {
            if (tokens[1] == "1") return true;
            if (tokens[1] == "0") return false;
        }
    }

    return false;
}
