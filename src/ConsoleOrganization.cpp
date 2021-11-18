//
// Created by MRV on 18.11.2021.
//
#include "ConsoleOrganization.h"
#include <iostream>

std::string ConsoleOrganization::execute_command() {
    std::string answer;
    std::string name;
    int index;
    switch (current_command) {
        case EXIT:
            return "";
        case CREATE_SHOP:
            std::cout << "������� �������� ��������(-1 ��� �������� �����):";
            std::cin >> name;
            if (name!="-1") return organization->create_shop(name);
            else return "";
        case CREATE_CARGO:
            std::cout << "������� �������� ������(-1 ��� �������� �����): ";
            std::cin >> name;
            if (name!="-1") return organization->create_cargo(name);
            else return "";
        case REMOVE_SELLER:
            index = input<int>(
                    [](int x) -> bool {return x>=-1;},
                    [](std::string x) -> int {return std::stoi(x);} ,
                    std::string( "�������, ����������, ����� �������������� �����������(-1 ��� �������� �����): "),
                    std::string("�������� ������, �������, ����������, ���������� �����: "));
            if (index != -1){
                return organization->remove_seller(index);
            }
            else return std::string("�� ������ �� ������������� �����������.");
        case CHECK_REMOVE_SELLER:
            index = input<int>(
                    [](int x) -> bool {return x>=-1;},
                    [](std::string x) -> int {return std::stoi(x);} ,
                    std::string( "�������, ����������, ����� ����������� ��� �������� �� ����������� ��� ����������(-1 ��� �������� �����): "),
                    std::string("�������� ������, �������, ����������, ���������� �����: "));
            if (index != -1){
                return organization->remove_seller(index);
            }
            else return std::string("�� ������ �� ��������� ����������� �� ����������� ����������.");
        case GET_INFO:
             return "������ ��������: " + std::to_string(organization->get_balance()) + "\n" + organization->get_info() + "\n";
        case MANAGE_SELLER:
            index = input<int>(
                    [](int x) -> bool {return x>=-1;},
                    [](std::string x) -> int {return std::stoi(x);} ,
                    std::string( "�������, ����������, ����� ����������� ��� ���������� ��(-1 ��� �������� �����:) "),
                    std::string("�������� ������, �������, ����������, ���������� �����: "));
            if (index>=0 && index < organization->get_own_numbers()) organization->start_seller_console(index, base);
            else if (index!=-1) return "������������ ����� �����������";
            else return "";
        case NEXT_DAY:
            return organization->day();
        default:
            return "������.";
    }
}
void ConsoleOrganization::start() {
    std::string input_text = "�������, ����������, ����� ����, ��� �� ������ �������: \n0)��������� ���� \n1)������� �������\n2)������� �����\n3)������������� �����������\n4)��������� ����������� �� ����������� ����������\n5)�������� ������ �� ������� �� ������ �����������\n6)��������� ������������\n7)������ ��������� ����\n";
    std::string error_text = "�������� ������, �������, ����������, ���������� �����: ";
    while (current_command != EXIT){
        current_command = input<int>(
                [](int x) -> bool {return EXIT<=x&&x<=NEXT_DAY;},
                [](std::string x) -> int {return std::stoi(x);} ,
                input_text,
                error_text);
        std::cout << execute_command();
    }
}
