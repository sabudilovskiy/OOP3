#include <iostream>
#include "Organization.h"
#include "Support.h"
#include <string>

class ConsoleOrganization{
    Organization* organization = nullptr;
    int current_command;
    enum commands{
        EXIT, CREATE_SHOP, CREATE_CARGO, REMOVE_SELLER, CHECK_REMOVE_SELLER, GET_INFO, NEXT_DAY
    };
public:
    ConsoleOrganization(Organization* organization):organization(organization);
    void start(){
        while (current_command != EXIT){
            current_command = input<int>(
                    [](int x) -> bool {return EXIT<=x&&x<=NEXT_DAY;},
                    [](std::string x) -> int {return std::stoi(x);} ,
                    std::string( "�������, ����������, ����� ����, ��� �� ������ �������: \n0) ��������� ����. \n1)������� �������\n2)������� �����\n3)������������� �����������\n4)��������� ������������ �� ����������� ����������\n5)�������� ������ �� ������� �� ������ �����������\n6)������ ��������� ����"),
                    std::string("�������� ������, �������, ����������, ���������� �����: "));
            std::cout << execute_command();
        }
    }
    std::string execute_command(){
        std::string answer;
        std::string name;
        int index;
        switch (current_command) {
            case EXIT:
                return "";
            case CREATE_SHOP:
                std::cout << "������� �������� ��������. ";
                std::cin >> name;
                return organization->create_shop(name);
            case CREATE_CARGO:
                std::cout << "������� �������� ��������. ";
                std::cin >> name;
                return organization->create_cargo(name);
            case REMOVE_SELLER:
                index = input<int>(
                        [](int x) -> bool {return x>=-1;},
                        [](std::string x) -> int {return std::stoi(x);} ,
                        std::string( "�������, ����������, ����� �������������� �����������(-1 ��� ������): "),
                        std::string("�������� ������, �������, ����������, ���������� �����: "));
                if (index != -1){
                    return organization->remove_seller(index);
                }
                else return std::string("�� ������ �� ������������� �����������.");
            case CHECK_REMOVE_SELLER:
                index = input<int>(
                        [](int x) -> bool {return x>=-1;},
                        [](std::string x) -> int {return std::stoi(x);} ,
                        std::string( "�������, ����������, ����� ����������� ��� �������� �� ����������� ��� ����������(-1 ��� ������): "),
                        std::string("�������� ������, �������, ����������, ���������� �����: "));
                if (index != -1){
                    return organization->remove_seller(index);
                }
                else return std::string("�� ������ �� ��������� ����������� �� ����������� ����������.");
            case GET_INFO:

            case NEXT_DAY:
                return organization->day();
            default:
                return "������.";
        }
    }
};
class ConsoleSeller{

};


int main(){
    Organization* test;
    test->day();
}