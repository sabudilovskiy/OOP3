//
// Created by MRV on 18.11.2021.
//
#include "ConsoleSeller.h"
#include <iostream>
#include "ConsoleSellerEmployees.h"
#include "ConsoleSellerFinance.h"
#include "ConsoleSellerItems.h"
ConsoleSeller::ConsoleSeller(Seller *seller, std::vector<Item> &base) : seller(seller),base(base) {}
void ConsoleSeller::start() {
    std::cout << "�� ���������� ������������ " + seller->get_name() + "\n";
    std::string input_text;
    std::string error = "����� ������������ ����� �������, ��������� ����: ";
    input_text = "������� ����� �������: \n";
    input_text += "0) ��������� � ���������� ���������\n";
    input_text += "1) ������� � ���������� � ��������� ���������� � ���������� ��������� �����������\n";
    input_text += "2) ������� � ��������� ���������� �� ������������ � ���������� ��(���������� ����� �������, ������ � ������, ���������� �������)\n";
    input_text += "3) ������� � ���������� ����������\n";
    input_text += "4) �������� ��� ��������� ��������������\n";
    input_text += "5) ������������� �����������\n";
    while (current_command!=EXIT){
        current_command = input<int>([](int x){return EXIT<=x&&x<=RENAME;}, [](std::string str){return std::stoi(str);}, input_text, error);
        std::cout<<execute_command();
    }
}

std::string ConsoleSeller::execute_command() {
    int index;
    double argument;
    std::string name;
    switch (current_command) {
        case EXIT:
            return "";
        case FINANCE:
            ConsoleSellerFinance(seller).start();
            return "";
        case ITEMS:
            ConsoleSellerItems(seller, base).start();
            return "";
        case EMPLOYEES:
            ConsoleSellerEmployees(seller).start();
            return "";
        case SWITCH_AUTOREFILL:
            seller->switch_autorefill();
        case RENAME:
            std::cout << "������� ����� ��������: ";
            std::cin >> name;
            seller->set_name(name);
            return "�� ������� ������������� �����������.";
    }
}
