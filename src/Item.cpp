//
// Created by MRV on 18.11.2021.
//
#include <string>
#include "Item.h"
#include "Support.h"
Item::Item(std::string name, double base_price, double base_involvement, double base_popularity, int capacity,
           int effectiveness) : name(std::move(name)), base_price(base_price), base_involvement(base_involvement),
                                base_popularity(base_popularity), capacity(capacity),
                                effectiveness(effectiveness) {}

const std::string &Item::get_name() const {
    return name;
}

double Item::get_base_price() const {
    return base_price;
}

double Item::get_base_involvement() const {
    return base_involvement;
}

double Item::get_base_popularity() const {
    return base_popularity;
}

int Item::get_capacity() const {
    return capacity;
}

int Item::get_effectiveness() const {
    return effectiveness;
}

std::string Item::get_info() {
    return name + " ÁÖ: " + std::to_string(my_round(base_price, 2)) 
    +"$ ÁÂ: " + std::to_string(my_round(base_involvement, 2)) 
    + " ÁÏ: " + std::to_string(my_round(base_popularity, 2))
    + " Âì: " + std::to_string(capacity) +
    " Ýô: " + std::to_string(effectiveness);
}
