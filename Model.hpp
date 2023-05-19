#ifndef DSV_MODEL_H
#define DSV_MODEL_H


#include "Tree.hpp"
#include <map>
#include <vector>
#include <utility>
#include <tuple>

class Model
{
    RedBlackTree<int> tree;
    std::map<int, int> presence;

public:
    bool insert(const int x);
    bool remove(const int x);
    void clear();
    void close();
    void print();

    std::vector< std::tuple< int, char, int, int > > data;
};


#endif //DSV_MODEL_H