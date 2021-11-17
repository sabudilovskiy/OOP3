//
// Created by MRV on 16.11.2021.
//

#ifndef ORGANIZATION_OOP3_H
#define ORGANIZATION_OOP3_H
#include <vector>
#include <string>
#include "predeclare_classes.h"
#include "Shop.h"
#include "Cargo.h"
class Organization{
    double balance = 0;
    std::vector<Seller*> own;
    int own_numbers = 0;
public:
    double get_balance() const {
        return balance;
    }
    double take_money(double money){
        if (money > 0){
            if (money < balance){
                balance-=money;
                return money;
            }
            else return 0;
        } else return 0;
    }
    std::string recieve_money(double money){
        if (money>0){
            balance+=money;
            return "�������� �������� �������� �� ���� " + std::to_string(money) + "$";
        }
        else{
            return "�������� �������� �� �������� ����� �� ���� ����.";
        }
    }
    std::string create_shop(std::string name){
        if (balance > 1000){
            own.push_back((Seller*)new Shop(this, name));
            balance -= 1000;
            return "�� ������� ������� " + name +"! �� �������� ������ ����������� � �������� �������.";
        }
        else return "� ��� ������������ ����� ��� �������� ��������. ��������� ����� �� ����� 1000$ �� �����.";
    }
    std::string create_cargo(std::string name){
        if (balance > 1000){
            own.push_back((Seller*)new Cargo(this, name));
            balance -= 1000;
            return "�� ������� ����� " + name +"! �� �������� ������ ����������� � �������� �������.";
        }
        else return "� ��� ������������ ����� ��� �������� ������. ��������� ����� �� ����� 1000$ �� �����.";
    }
    std::string remove_seller(int index){
        if (0 <= index && index < n){
            std::string temp = own[index]->close();
            if (own[index]->get_number_items == 0 && own[index]->get_employee() == 0 && own[index]->get_balance() == 0){
                delete own[index];
                own.erase(index);
            }
            return temp;
        }
        else return "��� ����������� � ����� �������. ";
    }
    std::string check_remove_seller(int index){
        if (0 <= index && index < n){
            return own[index]->check_close();
        }
        else return "��� ����������� � ����� �������. ";
    }
    std::string day(){
        std::string answer;
        for (int i = 0; i < n; i++) answer+=own[i]->day();
        return answer;
    }
    int get_own_numbers() const {
        return own_numbers;
    }
    std::string get_info(){
        std::string answer;

    }
};
#endif

