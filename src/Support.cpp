//
// Created by MRV on 18.11.2021.
//
#include "Support.h"
#include <iostream>
#include <random>
#include <stdexcept>
double my_random(double a, double b) {
    if (b!=a){
        std::random_device rd;
        std::mt19937_64 mersenne(rd());
        std::uniform_real_distribution<double> uid(a, b);
        double random = uid(mersenne);
        return random;
    }
    else return b;
}

int my_round(double a, unsigned int point) {
    return round(pow(10, point)*a)/pow(10, point);
}
