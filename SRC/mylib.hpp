#pragma once
#include <iostream>

#ifndef MYLIB_HPP
#define MYLIB_HPP

using namespace std;

class vec2{
    public:
    int x, y;

    void print(){
        cout << x << " " << y << endl;
    }
};

class vec2f{
    public:
    float x, y;

    void print(){
        cout << x << " " << y << endl;
    }
};

#endif //MYLIB_HPP