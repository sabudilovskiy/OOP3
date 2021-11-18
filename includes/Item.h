//
// Created by MRV on 16.11.2021.
//

#ifndef OOP3_ITEM_H
#define OOP3_ITEM_H

#include <utility>
#include <xstring>
class Item{
private:
    std::string name;
    double base_price;
    double base_involvement;
    double base_popularity;
    int capacity;
    int effectiveness;
public:
    Item(std::string name, double base_price, double base_involvement, double base_popularity, int capacity,
         int effectiveness);
    [[nodiscard]] const std::string &get_name() const;
    [[nodiscard]] double get_base_price() const;
    [[nodiscard]] double get_base_involvement() const;
    [[nodiscard]] double get_base_popularity() const;
    [[nodiscard]] int get_capacity() const;
    [[nodiscard]] int get_effectiveness() const;
    [[nodiscard]] std::string get_info();
};
#endif //OOP3_ITEM_H
