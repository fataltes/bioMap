//
// Created by Fatemeh Almodaresi on 2022-02-17.
//

#include "goMap.h"
#include <iostream>

void GoMap::initialize(const std::string& filename) {
    std::cout << "You called map for file name " << filename << "\n";
}

int goMapMain(const goMap::MapOpts& mapOpts) {
    std::cout << "creating an instance of GoMap class:\n";
    GoMap goMap;
    std::cout << "call method initialize from it:\n";
    goMap.initialize(mapOpts.inputFile);

    return EXIT_SUCCESS;
}