//
// Created by MRV on 16.11.2021.
//

#ifndef SUPPORT_OOP3_H
#define SUPPORT_OOP3_H
#include <iostream>
#include <random>
#include <stdexcept>
double my_random(double a, double b);
int my_round(double a, unsigned int point);
template<class T>
T input(bool (*verifer)(T), T (*converter)(std::string), const std::string& input, const std::string& _error) {
    std::string temp;
    std::cout << input;
    std::cin >> temp;
    try {
        T answer = converter(temp);
        if (verifer(answer)) return answer;
        throw std::invalid_argument("");
    }
    catch (std::invalid_argument) {
        while (true) {
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