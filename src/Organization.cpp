//
// Created by MRV on 18.11.2021.
//
#include <iostream>
#include "Organization.h"
#include "Seller.h"
#include "ConsoleSeller.h"
double Organization::get_balance() const {
    return balance;
}

double Organization::take_money(double money) {
    if (money > 0){
        if (money < balance){
            balance-=money;
            return money;
        }
        else return 0;
    } else return 0;
}

void Organization::recieve_money(double money) {
    if (money>0){
        balance+=money;
    }
}

std::string Organization::create_shop(std::string name) {
    if (balance > 1000){
        own.push_back((Seller*)new Shop(this, name));
        balance -= 1000;
        own_numbers++;
        return "Вы создали магазин " + name +"! Не забудьте нанять сотрудников и закупить товаров.";
    }
    else return "У вас недостаточно денег для создания магазина. Требуется иметь не менее 1000$ на счету.";
}

std::string Organization::create_cargo(std::string name) {
    if (balance > 1000){
        own.push_back((Seller*)new Cargo(this, name));
        balance -= 1000;
        own_numbers++;
        return "Вы создали склад " + name +"! Не забудьте нанять сотрудников и закупить товаров.";
    }
    else return "У вас недостаточно денег для создания склада. Требуется иметь не менее 1000$ на счету.";
}

std::string Organization::remove_seller(int index) {
    if (0 <= index && index < own_numbers){
        std::string temp = own[index]->close();
        if (own[index]->get_number_items() == 0 && own[index]->get_employee() == 0 && own[index]->get_balance() == 0){
            delete own[index];
            own.erase(own.cbegin() + index);
            own_numbers--;
        }
        return temp;
    }
    else return "Нет организации с таким номером. ";
}

std::string Organization::check_remove_seller(int index) {
    if (0 <= index && index < own_numbers){
        return own[index]->check_close();
    }
    else return "Нет организации с таким номером. ";
}

std::string Organization::day() {
    std::string answer;
    for (int i = 0; i < own_numbers; i++) answer+=own[i]->day();
    return answer;
}

int Organization::get_own_numbers() const {
    return own_numbers;
}

std::string Organization::get_info() {
    std::string answer;
    for (int index = 0; index < own_numbers; index++){
        answer += to_string(index) + ") " + own[index]->get_name() + " " + to_string(my_round(own[index]->get_balance(),2))+"$\n";
    }
    return answer;
}

void Organization::start_seller_console(int index, std::vector<Item> &base) {
    if (0<=index && index <= own_numbers) {
        ConsoleSeller console(own[index], base);
        console.start();
    }
    else std::cout << "Некорректный номер предприятия";
}

Organization::Organization(double balance) : balance(balance) {}

std::string Organization::get_balance_seller(int index) {
    if (0 <= index && index < own_numbers) return own[index]->get_name() + " " + std::to_string(my_round(own[index]->get_balance(), 2));
}
