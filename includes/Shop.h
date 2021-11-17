//
// Created by MRV on 16.11.2021.
//

#ifndef SHOP_OOP3_H
#define SHOP_OOP3_H
#include "predeclare_classes.h"
#include "Item.h"
#include "Seller.h"
class Shop : public Seller{
public:
    Shop(Organization* owner, std::string name){
        this->owner = owner;
        this->name = name;
    }
    std::string add_item(Item item) override{
        if (number_items < employee*5 && balance >= 100){
            items.push_back(item);
            cur_involvement.push_back(item.get_base_involvement());
            cur_popularity.push_back(item.get_base_popularity());
            capacity.push_back(item.get_capacity());
            balance_items.push_back(0);
            balance-=100;
            number_items++;
        }
    }
    std::string check_add_item() override{
        std::string answer;
        if (number_items < employee*5 && balance >= 100){
            answer = "�� ������ ��������� ����������� �� 100$.";
        }
        else if (number_items < employee*5 && balance < 100){
            answer = "�� �� ������ ��������� ����������� ��������: ��������� ����� �� ����� �������� �� ����� 100$";
        }
        else{
            answer = "�� �� ������ ��������� ����������� ��������: �������� ����� ��������� ���� " + std::to_string(employee) + " �������.";
        }
        return answer;
    }
    std::string buy(int index, int count) override{
        std::string answer;
        if (0 <= index && index <= number_items){
            answer+=items[index].get_name();
            if (count <= balance_items[index]){
                balance += price[index] * count;
                balance_items[index] -= count;
                answer += " ������� ������ " + std::to_string(count) + " ��.\n";
            }
            else {
                cur_popularity[index] -= my_random(0, 0.1*cur_popularity[index]);
                if (cur_involvement[index] > cur_popularity[index]) cur_involvement[index] = cur_popularity[index];
                answer += " ������� �� ������ ������ ����� ��-�� ��� ����������. \n";
            }
        }
        else answer = "������ �� ����������. ";
        return answer;
    }
    std::string remove_item(int index) override{
        if (0 <= index && index < number_items){
            balance += balance_items[index] * items[index].get_base_price() * 0.5;
            items.erase(items.cbegin() + index);
            cur_involvement.erase(cur_involvement.cbegin() + index);
            cur_popularity.erase(cur_popularity.cbegin() + index);
            price.erase(price.cbegin() + index);
            capacity.erase(capacity.cbegin() + index);
            balance_items.erase(balance_items.cbegin() + index);
            number_items--;
        }
    }
    std::string dismiss_employes(int number) override{
        if (number > 0 && number <= employee){
            if ((employee - number) * 5 >= number_items){
                if (balance >= number * 175){
                    employee-=number;
                    balance-=number*175;
                }
            }
        }
    }
    std::string check_dismiss_employes(int number) override{
        std::string answer;
        if (number > 0 && number <= employee) {
            if ((employee - number) * 5 >= number_items) {
                answer = "�� ������ ������� " + to_string(number) +
                         " �����������. ��� ������� ��������� ��������� ��������� � ������� " +
                         to_string(number*75) + "$";
            }
            else {
                answer = "�� �� ������ ��������� ���� ������� �����������: � ����� ������ ��� �� ������ ���������� �� ������������ ������������.";
            }
        }
        else {
            answer = "������������ ���������� �����������. ";
        }
    }
    std::string promote_all() override{
        double cost = 0;
        for (int index; index < number_items; index++)
        {
            cost += pow(cur_popularity[index] / items[index].get_base_popularity(), 1.5) * 100;
        }
        if (balance >= cost){
            for (int index; index < number_items; index++){
                change_popularity(index, my_random(0, 1));
            }
            balance-=cost;
        }
    }
    std::string check_promote_all() override {
        double cost = 0;
        for (int index; index < number_items; index++) {
            cost += pow(cur_popularity[index] / items[index].get_base_popularity(), 1.5) * 100;
        }
        std::string answer = "�������������� �������� ����� " + to_string(my_round(cost, 2)) +
                      "$ ��������� ������������ ���� �������. ";
        return answer;
    }
    std::string promote_item(int index) override{
        if (0 <= index && index < number_items){
            double cost = pow(cur_popularity[index] / items[index].get_base_popularity(), 1.5) * 100;
            if (cost <= balance){
                balance -= cost;
                change_popularity(index, my_random(0, 1));
                return "�� ������� ��������� �������� ���������� " + std::to_string(my_round(cost, 2));
            }
            else return "�� �� ������� ��������� ��������: ��������� ����� �� ����� �������� �� ����� " + std::to_string(my_round(cost, 2));
        }
        else return "����� ����� �� ����������. ";
    }
    std::string check_promote_item(int index) override{
        std::string answer;
        if (0 <= index && index < number_items){
            double cost = pow(cur_popularity[index] / items[index].get_base_popularity(), 1.5) * 100;
            return "��������� ������� ��� ����� ������: " + to_string(my_round(cost, 2));
        }
        else return "������������ ����� ������. ";

    }
    std::string day() override{
        std::string answer;
        if (balance >= 0){
            for (int i = 8; i < 22; i++){
                for (int j = 0; j < number_items; j++){
                    double x = price[j]/items[j].get_base_price();
                    answer += buy(j, (int)((my_random(cur_involvement[j], cur_popularity[j])) * pow(2, log(1/(2*x-1)))));
                }
            }
        }
        balance -= employee * 25;
        answer += "�� ������ �������� ����������� ��������� " + to_string(employee*25) + "$\n";
        if (auto_refill) answer+=refill_all();
        return answer;
    }
};
#endif
