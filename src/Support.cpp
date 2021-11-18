//
// Created by MRV on 18.11.2021.
//
#include "Support.h"
#include <iostream>
#include <random>
#include <stdexcept>
int my_random(double a, double b) {
    if (b!=a){
        std::random_device rd;
        std::mt19937 mersenne(rd());
        double cof = DBL_MAX/(b-a);
        double random = (double)(mersenne()) / cof;
        random+=a;
        return random;
    }
    else return b;
}

int my_round(double a, unsigned int point) {
    return round(pow(10, point)*a)/pow(10, point);
}
