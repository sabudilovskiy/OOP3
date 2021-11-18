#include <iostream>
#include <vector>
#include "Item.h"
#include "Support.h"
#include <string>
#include <Organization.h>
#include "ConsoleOrganization.h"
#include <Windows.h>
int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n = input<int>(
            [](int x) -> bool {return x>=0;},
            [](std::string x) -> int {return std::stoi(x);} ,
            "������� ����� ��������� � ���� �������: ",
            "�������� ������ ��� �����, ��������� ����: ");
    std::vector<Item> base;
    for (int i = 0; i < n; i++){
        std::cout << "������� �������� ������: ";
        std::string name;
        std::cin >> name;
        double price = input<double>(
                [](double x) -> bool {return x>=0;},
                [](std::string x) -> double {return std::stod(x);} ,
                std::string("������� ���� ������: "),
                std::string("�������� ������ ��� �����, ��������� ����: "));
        double involvement = input<double>(
                [](double x) -> bool {return x>=0;},
                [](std::string x) -> double {return std::stod(x);} ,
                std::string("������� ������������� ������: "),
                std::string("�������� ������ ��� �����, ��������� ����: "));
        double popularity = input<double>(
                [](double x) -> bool {return x>=0;},
                [](std::string x) -> double {return std::stod(x);} ,
                std::string("������� ������������ ������: "),
                std::string("�������� ������ ��� �����, ��������� ����: "));
        while (popularity < involvement){
            popularity = input<double>(
                    [](double x) -> bool {return x>=0;},
                    [](std::string x) -> double {return std::stod(x);} ,
                    std::string("������������ ������ ���� �� ������ �������������. ��������� ����: "),
                    std::string("�������� ������ ��� �����, ��������� ����: "));
        }
        int capacity = input<int>(
                [](int x) -> bool {return x>=0;},
                [](std::string x) -> int {return std::stoi(x);} ,
                std::string("������� ����������� ������: "),
                std::string("�������� ������ ��� �����, ��������� ����: "));
        int effectiveness = input<int>(
                [](int x) -> bool {return x>=0;},
                [](std::string x) -> int {return std::stoi(x);} ,
                std::string("������� ������������� ������: "),
                std::string("�������� ������ ��� �����, ��������� ����: "));
        base.emplace_back(name, price, involvement, popularity, capacity, effectiveness);
    }
    double start_capital = input<double>(
            [](double x) -> bool {return x>=0;},
            [](std::string x) -> double {return std::stod(x);} ,
            std::string("������� ��������� �������: "),
            std::string("�������� ������ ��� �����, ��������� ����: "));
    Organization* org = new Organization(start_capital);
    ConsoleOrganization(org, base).start();
}