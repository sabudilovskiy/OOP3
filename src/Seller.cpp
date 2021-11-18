//
// Created by MRV on 18.11.2021.
//

#include "Seller.h"
#include "Organization.h"

void Seller::change_popularity(int index, double cof) {
    if (0 <= index && index < number_items){
        cur_popularity[index] += cur_popularity[index] * cof;
        if (cur_involvement > cur_popularity) cur_involvement = cur_popularity;
    }
}

void Seller::change_popularity_all(double cof) {
    for (int index = 0; index < number_items; index++){
        cur_popularity[index] += cur_popularity[index] * cof;
        if (cur_involvement > cur_popularity) cur_involvement = cur_popularity;
    }
}

int Seller::get_employee() const {
    return employee;
}

std::string Seller::check_close() {
    double cur_balance = balance - 175*employee;
    for (int index = 0; index < number_items; index++){
        balance+=items[index].get_base_price()*balance_items[index]*0.5;
    }
    return "����� ������ ����������� � ������ �������� ��-�� ���������� � ������� ������ �� �������� �� �������������: " + to_string(
            my_round(cur_balance, 2));
}

std::string Seller::close() {
    double cur_balance = balance - 175*employee;
    for (int index = 0; index < number_items; index++){
        balance+=items[index].get_base_price()*balance_items[index]*0.5;
    }
    if (cur_balance > 0){
        while (number_items>0){
            remove_item(0);
        }
        dismiss_employees(employee);
        owner->recieve_money(cur_balance);
        balance = 0;
        return "����������� ���������� ���� ������. ������� ����� �������� �� ����� ��������: " + to_string(
                my_round(cur_balance, 2)) + "$";
    }
    else{
        if (owner->get_balance() + cur_balance > 0){
            receive_money(owner->take_money(cur_balance));
            while (number_items>0){
                remove_item(0);
            }
            dismiss_employees(employee);
            return "����������� ���������� ���� ������. ��� �������� ������ ����������� ���� ��������� " + to_string(
                    my_round(cur_balance, 2)) + "$";
        }
        else{
            return "��� �� ������� ����� ��� �������� ������ �����������.";
        }
    }
}

const std::string &Seller::get_name() const {
    return name;
}

void Seller::set_name(const std::string &name) {
    Seller::name = name;
}

std::string Seller::switch_autorefill() {
    auto_refill = !auto_refill;
    std::string temp  = (!auto_refill)?"�": "";
    return "�������������� ������ �" + temp + "�������. ";
}

std::string Seller::get_info_about_item(int index) {
    std::string answer;
    if (0 <= index && index < number_items){
        answer = "��� � " + to_string(index + 1) + items[index].get_name()+ "\n";
        answer += "������������: " + to_string(my_round(cur_popularity[index],2));
        answer += " �������������: " + to_string(my_round(cur_involvement[index],2)) + "\n";
        answer += " ������� ���� : " + to_string(price[index]);
        answer += " ������� ����" + to_string(items[index].get_base_price());
    }
    return answer;
}

std::string Seller::get_info_about_items() {
    std::string answer;
    for (int index = 0; index < number_items; index++) answer += get_info_about_item(index) + '\n';
    return answer;
}

int Seller::get_number_items() const {
    return number_items;
}

double Seller::get_balance() const {
    return balance;
}

std::string Seller::refill(int index) {
    if (0<=index && index < number_items){
        double need = (capacity[index] - balance_items[index]) * items[index].get_base_price();
        if (balance > need) {
            balance_items[index] = capacity[index];
            return items[index].get_name() + " �� ��������� ������� ������. ��������� " + std::to_string(need) + "$";
        }
        else return "� ��� ��� ������������ ���������� �����. ��������� �� ����� " + std::to_string(need) + "$ �� ����� �����������.";
    }
    else return "������ ������ ���.";
}

std::string Seller::check_refill(int index) {
    std::string answer;
    if (0<=index && index < number_items){
        double need = (capacity[index] - balance_items[index]) * items[index].get_base_price();
        answer = "�� ���������� ������ ������� ��������� " + to_string(my_round(need, 2)) + "$. �� ����� ��������: " + to_string(
                my_round(balance,2));
    }
    return answer;
}

std::string Seller::check_refill_all() {
    std::string answer;
    double need = 0;
    for (int index = 0; index < number_items; index++) need += (capacity[index] - balance_items[index]) * items[index].get_base_price();
    answer = "�� ���������� ���� ������� ��������� " + to_string(my_round(need, 2)) + "$. �� ����� ��������: " + to_string(my_round(balance,2));
    return answer;
}

std::string Seller::refill_all() {
    double need = 0;
    for (int index = 0; index < number_items; index++) need += (capacity[index] - balance_items[index]) * items[index].get_base_price();
    if (balance >= need){
        for (int index = 0; index < number_items; index++) balance_items[index] = capacity[index];
        balance-=need;
        return "�� ��������� ������ " + name + " �� " + to_string(need) + "$";
    }
    else return "� ��� ������������ ����� ��� ���������� ������� " + name + ". ��������� �� ����� " + to_string(need) + "$" + " �� ����� �����������.";
}

std::string Seller::check_remove_item(int index) {
    std::string answer;
    if (0 <= index && index < number_items){
        double plus = balance_items[index] * items[index].get_base_price() * 0.5;
        answer = "�� ���������� �� " + items[index].get_name() + " � ������������ � ������ ���������� �� �������� ���������  " + to_string(balance_items[index]) + "����� �������, �� �������� " + to_string(
                my_round(plus, 2))  + "$";

    }
    else {
        answer = "������������ ����� ������. ";
    }
    return answer;
}

std::string Seller::hire_employees(int number) {
    if (number * 300 <= balance){
        employee += number;
        balance -= number * 300;
        return "�� ������� ������ �����������. ��������� �� ����������� : " + to_string(number*300) + "$ ";
    }
    else return "�� �� ������ ��������� ���� ������ �����������: ��������� �� ����� " + to_string(number*300) + "$ �� ����� �����������";
}

std::string Seller::check_hire_employees(int number) {
    std::string answer = "������ " + to_string(number) + " ����������� ����� " + to_string(number*300) + "$. ���������� �������� ������� �����������: " + to_string(25*number) + " $";
    return answer;
}

std::string Seller::receive_money(double money) {
    if (money > 0){
        double from_owner = owner->take_money(money);
        balance += from_owner;
        if (from_owner > 0){
            return "�� ������� �������� ������ �� ����� �������� �� ���� �����������";
        }
        else return "������������ ����� �� ����� ��������";
    }
    else return "������������ ����� ��� ��������";
}

std::string Seller::take_money(double money) {
    if (money > 0) {
        if (money <= balance){
            balance-=money;
            owner->recieve_money(money);
            return "�� ������� �������� ������ �� ����� ����������� �� ���� ��������";
        }
        else return "������������ ����� �� ����� ��������";
    }
    else return "������������ ����� ��� ��������";
}

double Seller::get_balance() {
    return balance;
}

std::string Seller::get_info_about_items_to_add(std::vector<Item> &base) {
    std::string answer;
    for (int index = 0; index < base.size(); index++){
        answer += base[index].get_info() + "\n";
    }
    return answer;
}

std::string Seller::change_price(int index, double new_price) {
    if (0 <= index && index < number_items){
        if (new_price>0){
            price[index] = new_price;
            return items[index].get_name() + " �� �������� ���� ������. ������ �� �������� �� " + to_string(new_price) + "$";
        }
        else return "������������ ����.";
    }
    else return "������ ������ �� ����������.";
}
