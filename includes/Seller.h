//
// Created by MRV on 16.11.2021.
//
#ifndef OOP_3_SELLER_H
#define OOP_3_SELLER_H
#include "Item.h"
#include "Support.h"
#include <vector>
#include <string>
using std::to_string;
class Organization;
class Seller{
protected:
    std::string name;
    Organization* owner;
    bool auto_refill = true;
    int employee = 0;
    double balance = 0;
    std::vector<Item> items;
    std::vector<double> cur_involvement;
    std::vector<double> cur_popularity;
    std::vector<double> price;
    std::vector<int> capacity;
    std::vector<int> balance_items;
    int number_items = 0;
    //запрещаем создание родительского класса
    Seller() = default;
    void change_popularity(int index, double cof);
    void change_involvement(int index, double cof);
    virtual std::string buy(int index, int count) = 0;
public:
    [[nodiscard]] int get_employee() const;
    std::string check_close();
    virtual std::string close();
    [[nodiscard]] const std::string &get_name() const;
    void set_name(const std::string &name);
    std::string switch_autorefill();
    virtual std::string get_info_about_item(int index);
    std::string get_info_about_items();
    std::string get_info_about_items_to_add(std::vector<Item> &base);
    [[nodiscard]] int get_number_items() const;
    [[nodiscard]] double get_balance() const;
    virtual std::string add_item(Item item) = 0;
    virtual std::string check_add_item() = 0;
    std::string change_price(int index, double new_price);
    std::string refill(int index);
    std::string check_refill(int index);
    std::string check_refill_all();
    std::string refill_all();
    virtual std::string remove_item(int index) = 0;
    std::string check_remove_item(int index);
    virtual std::string hire_employees(int number);
    virtual std::string check_hire_employees(int number);
    virtual std::string dismiss_employees(int number) = 0;
    virtual std::string check_dismiss_employees(int number) = 0;
    virtual std::string promote_all() = 0;
    virtual std::string check_promote_all() = 0;
    virtual std::string promote_item(int index) = 0;
    virtual std::string check_promote_item(int index) = 0;
    virtual std::string day() = 0;
    virtual std::string up_capacity(int index) = 0;
    std::string receive_money(double money);
    std::string take_money(double money);
    double get_balance();
};
#endif


