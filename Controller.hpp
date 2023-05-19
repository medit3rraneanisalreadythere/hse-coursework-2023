#ifndef DSV_CONTROLLER_H
#define DSV_CONTROLLER_H


#include "Model.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

class Controller
{
    Model newModel;

public:
    bool updated = false;
    bool end = false;
    std::vector< std::tuple< int, char, int, int > > getter; // r = red, b = black, n = null

    Controller()
    {
        std::cout << "\nThis is Data Structure Vizualization project.\n";
        std::cout << "\nProgram options:\n";
        std::cout << "    type \"insert number\" to insert new node (e.g. insert 19);\n";
        std::cout << "    type \"remove number\" to remove existing node (e.g. remove 19);\n";
        std::cout << "    type \"clear\" to cut down the tree.\n";
        std::cout << "    type \"close\" to exit.\n";
        std::cout << "Note: numbers are standart integer (from -999999 to 999999).\n\n";
    }

    void read();
};


#endif //DSV_CONTROLLER_H