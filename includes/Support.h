//
// Created by MRV on 16.11.2021.
//
#include <random>
#include <stdexcept>
#ifndef SUPPORT_OOP3_H
#define SUPPORT_OOP3_H
int my_random(double a, double b){
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
int my_round(double a, unsigned int point){
    return round(pow(10, point)*a)/pow(10, point);
}

template<class T>
T input(bool (*verifer)(T), T (*converter)(std::string), std::string input, std::string _error)
{
    std::string temp;
    std::cout << input;
    std::cin >> temp;
    bool error = true;
    try {
        T answer = converter(temp);
        if (verifer(answer)) return answer;
    }
    catch (std::invalid_argument) {
        while (error) {
            std::cout << _error;
            std::cin >> temp;
            try {
                T answer = converter(temp);
                if (verifer(answer)) return answer;
            }
            catch (std::invalid_argument) {
            }
        }
    }
}
#endif