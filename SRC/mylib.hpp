#pragma once
#include <iostream>

#ifndef MYLIB_HPP
#define MYLIB_HPP

using namespace std;

class vec2{
    public:
    int x, y;

    void print();
};

class vec2f{
    public:
    float x, y;

    void print();
};

#endif //MYLIB_HPP