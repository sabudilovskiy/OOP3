//
// Created by MRV on 16.11.2021.
//

#ifndef OOP3_ITEM_H
#define OOP3_ITEM_H

#include <utility>
#include <xstring>
#include "predeclare_classes.h"
class Item{
private:
    std::string name;
    double base_price;
    double base_involvement;
    double base_popularity;
    int capacity;
    int need_employes;
public:
    Item(std::string name, double base_price, int base_min_popularity, int base_max_popularity, int capacity,
         int need_employes) : name(std::move(name)), base_price(base_price), base_involvement(base_min_popularity),
                              base_popularity(base_max_popularity), capacity(capacity),
                              need_employes(need_employes) {}
    [[nodiscard]] const std::string &get_name() const {
        return name;
    }
    [[nodiscard]] double get_base_price() const {
        return base_price;
    }
    [[nodiscard]] double get_base_involvement() const {
        return base_involvement;
    }
    [[nodiscard]] double get_base_popularity() const {
        return base_popularity;
    }
    [[nodiscard]] int get_capacity() const {
        return capacity;
    }
    [[nodiscard]] int get_one_employee() const {
        return need_employes;
    }
};
#endif //OOP3_ITEM_H
