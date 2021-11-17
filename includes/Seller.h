//
// Created by MRV on 16.11.2021.
//
#ifndef OOP_3_SELLER_H
#define OOP_3_SELLER_H
#include "Item.h"
#include "Support.h"
#include "Organization.h"
#include "predeclare_classes.h"
#include <vector>
#include <string>
using std::to_string;
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
    //��������� �������� ������������� ������
    Seller();
    void change_popularity(int index, double cof){
        if (0 <= index && index < number_items){
            cur_popularity[index] += cur_popularity[index] * cof;
            if (cur_involvement > cur_popularity) cur_involvement = cur_popularity;
        }
    }
    void change_popularity_all(double cof){
        for (int index = 0; index < number_items; index++){
            cur_popularity[index] += cur_popularity[index] * cof;
            if (cur_involvement > cur_popularity) cur_involvement = cur_popularity;
        }
    }
public:
    int get_employee() const {
        return employee;
    }
    std::string check_close(){
        double cur_balance = balance - 175*employee;
        for (int index = 0; index < number_items; index++){
            balance+=items[index].get_base_price()*balance_items[index]*0.5;
        }
        return "����� ������ ����������� � ������ �������� ��-�� ���������� � ������� ������ �� �������� �� �������������: " + to_string(
                my_round(cur_balance, 2));
    }
    std::string close(){
        double cur_balance = balance - 175*employee;
        for (int index = 0; index < number_items; index++){
            balance+=items[index].get_base_price()*balance_items[index]*0.5;
        }
        if (cur_balance > 0){
            while (number_items>0){
                remove_item(0);
            }
            dismiss_employes(employee);
            owner->recieve_money(take_money(cur_balance));
            return "����������� ���������� ���� ������. ������� ����� �������� �� ����� ��������: " + to_string(
                    my_round(cur_balance, 2)) + "$";
        }
        else{
            if (owner->get_balance() + cur_balance > 0){
                recieve_money(owner->take_money(cur_balance));
                while (number_items>0){
                    remove_item(0);
                }
                dismiss_employes(employee);
                return "����������� ���������� ���� ������. ��� �������� ������ ����������� ���� ��������� " + to_string(
                        my_round(cur_balance, 2)) + "$";
            }
            else{
                return "��� �� ������� ����� ��� �������� ������ �����������.";
            }
        }
    }
    const std::string &get_name() const {
        return name;
    }
    void set_name(const std::string &name) {
        Seller::name = name;
    }
    void switch_autorefill(){
        auto_refill = !auto_refill;
    }
    virtual std::string get_info_about_item(int index){
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
    std::string get_info_about_items(){
        std::string answer;
        for (int index; index < number_items; index++) answer += get_info_about_item(index) + '\n';
        return answer;
    }
    [[nodiscard]] int get_number_items() const {
        return number_items;
    }
    [[nodiscard]] double get_balance() const {
        return balance;
    }
    virtual std::string add_item(Item item) = 0;
    virtual std::string check_add_item() = 0;
    virtual std::string buy(int index, int count) = 0;
    std::string refill(int index){
        if (0<=index && index < number_items){
            double need = (capacity[index] - balance_items[index]) * items[index].get_base_price();
            if (balance > need) {
                balance_items[index] = capacity[index];
            }
        }
    }
    std::string check_refill(int index){
        std::string answer;
        if (0<=index && index < number_items){
            double need = (capacity[index] - balance_items[index]) * items[index].get_base_price();
            answer = "�� ���������� ������ ������� ��������� " + to_string(my_round(need, 2)) + "$. �� ����� ��������: " + to_string(
                    my_round(balance,2));
        }
        return answer;
    }
    std::string check_refill_all(){
        std::string answer;
        double need = 0;
        for (int index = 0; index < number_items; index++) need += (capacity[index] - balance_items[index]) * items[index].get_base_price();
        answer = "�� ���������� ���� ������� ��������� " + to_string(my_round(need, 2)) + "$. �� ����� ��������: " + to_string(my_round(balance,2));
        return answer;
    }
    std::string refill_all(){
        double need = 0;
        for (int index = 0; index < number_items; index++) need += (capacity[index] - balance_items[index]) * items[index].get_base_price();
        if (balance >= need){
            for (int index = 0; index < number_items; index++) balance_items[index] = capacity[index];
            balance-=need;
            return "�� ��������� ������ " + name + " �� " + to_string(need) + "$";
        }
        else return "� ��� ������������ ����� ��� ���������� ������� " + name + ". ��������� �� ����� " + to_string(need) + "$" + " �� ����� �����������.";
    }
    virtual std::string remove_item(int index) = 0;
    std::string check_remove_item(int index) {
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
    std::string hire_employes(int number){
        if (number * 300 <= balance){
            employee += number;
            balance -= number * 300;
        }
    }
    static std::string check_hire_employes(int number){
        std::string answer = "������ " + to_string(number) + " ����������� ����� " + to_string(number*300) + "$. ���������� �������� ������� �����������: " + to_string(25*number) + " $";
        return answer;
    }
    virtual std::string dismiss_employes(int number) = 0;
    virtual std::string check_dismiss_employes(int number) = 0;
    virtual std::string promote_all() = 0;
    virtual std::string check_promote_all() = 0;
    virtual std::string promote_item(int index) = 0;
    virtual std::string check_promote_item(int index) = 0;
    virtual std::string day() = 0;
    std::string recieve_money(double money){
        balance += owner->take_money(money);
    }
    std::string take_money(double money){
        if (balance > money){
            owner->recieve_money(money);
        }
        else {
            owner->recieve_money(0);
        }
    }
    std::string get_balance() {
        return to_string(balance) + "$";
    }
};
#endif


