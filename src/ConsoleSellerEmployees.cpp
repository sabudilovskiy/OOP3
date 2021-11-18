//
// Created by MRV on 18.11.2021.
//

#include "ConsoleSellerEmployees.h"
#include <iostream>
ConsoleSellerEmployees::ConsoleSellerEmployees(Seller *seller) : seller(seller){}

void ConsoleSellerEmployees::start() {
    std::cout << "�� ���������� ������������� ����������� " + seller->get_name() + "\n";
    std::string input_text;
    std::string error = "����� ������������ ����� �������, ��������� ����: ";
    input_text = "������� ����� �������: \n";
    input_text += "0) ��������� � ���������� ������������\n";
    input_text += "1) ������ � ����������� ���������� �����������\n";
    input_text += "2) ������� �����������\n";
    input_text += "3) ������ � ����������� ���� �����������\n";
    input_text += "4) ������ �����������\n";
    while (current_command!=EXIT){
        current_command = input<int>([](int x){return EXIT<=x&&x<=HIRE;}, [](std::string str){return std::stoi(str);}, input_text, error);
        std::cout<<execute_command();
    }
}

std::string ConsoleSellerEmployees::execute_command() {
    int argument;
    switch (current_command){
        case EXIT:
            return "";
        case CHECK_DISMISS:
            argument = input<int>([](int x){return x>=-1;}, [](std::string str){return stoi(str);}, "������� ���������� �����������, ����������� ���������� ������� �� �� ������ ������ (-1 ��� �������� �����): ", "�������� ������, ��������� ����: ");
            if (argument != -1) return seller->check_dismiss_employees(argument);
            else return "";
        case DISMISS:
            argument = input<int>([](int x){return x>=-1;}, [](std::string str){return stoi(str);}, "������� ���������� �����������, ������� �� �� ������ ������� (-1 ��� �������� �����): ", "�������� ������, ��������� ����: ");
            if (argument != -1) return seller->dismiss_employees(argument);
            else return "";
        case CHECK_HIRE:
            argument = input<int>([](int x){return x>=-1;}, [](std::string str){return stoi(str);}, "������� ���������� �����������, ����������� ���� ������� �� �� ������ ������ (-1 ��� �������� �����): ", "�������� ������, ��������� ����: ");
            if (argument != -1) return seller->check_hire_employees(argument);
            else return "";
        case HIRE:
            argument = input<int>([](int x){return x>=-1;}, [](std::string str){return stoi(str);}, "������� ���������� �����������, ������� �� �� ������ ������ (-1 ��� �������� �����): ", "�������� ������, ��������� ����: ");
            if (argument != -1) return seller->hire_employees(argument);
            else return "";
    }
    return "";
}
