//
// Created by MRV on 18.11.2021.
//
#include "Cargo.h"

Cargo::Cargo(Organization *owner, const std::string &name) {
    this->owner = owner;
    this->name = name;
}

std::string Cargo::hire_employees(int number) {
    if (number * 600 <= balance){
        employee += number;
        balance -= number * 600;
        return "�� ������� ������ �����������. ��������� �� ��������� ������� : " + to_string(number*600) + "$ ";
    }
    else return "�� �� ������ ��������� ���� ������ �����������: ��������� �� ����� " + to_string(number*600) + "$ �� ����� �����������";
}

std::string Cargo::check_hire_employees(int number) {
    std::string answer = "������ " + to_string(number) + " ����������� ����� " + to_string(number*600) + "$. ���������� �������� ������� �����������: " + to_string(100*number) + " $";
    return answer;
}

std::string Cargo::add_item(Item item) {
    if (balance >= 200){
        items.push_back(item);
        price.push_back(item.get_base_price());
        cur_involvement.push_back(item.get_base_involvement());
        cur_popularity.push_back(item.get_base_popularity());
        capacity.push_back(item.get_capacity());
        balance_items.push_back(0);
        orders.push_back(0);
        balance-=200;
        number_items++;
        return "����� ������� ��������.";
    }
    else return "��� ���������� ������������ ��������� ����� �� ����� 200$ �� ����� ������.";
}

std::string Cargo::check_add_item() {
    std::string answer;
    if (balance >= 200){
        answer = "�� ������ ��������� ����������� �� 200$.";
    }
    else{
        answer = "�� �� ������ ��������� ����������� �� 200$: �� ����� ������ ��� ������������ ���������� �����.";
    }
    return answer;
}

std::string Cargo::buy(int index, int count) {
    if (0 <= index && index <= number_items){
        if (count <= balance_items[index] - orders[index]){
            balance_items[index] -= count;
            orders[index] += count;
            return items[index].get_name() + " ������� �������� " + to_string(count) + " ��. \n";
        }
        else {
            change_popularity(index, my_random(0.0, 0.1));
            return items[index].get_name() + " ������ �� ��������� � �������. ������� ������������. ";
        }
    }
    else return "������ ������ ���. ";
}

std::string Cargo::remove_item(int index) {
    if (0 <= index && index < number_items){
        std::string answer = items[index].get_name() + " ����� ������������. �� �������� " + to_string(my_round(balance_items[index] * items[index].get_base_price() * 0.5, 2));
        balance += balance_items[index] * items[index].get_base_price() * 0.5;
        items.erase(items.cbegin() + index);
        cur_involvement.erase(cur_involvement.cbegin() + index);
        cur_popularity.erase(cur_popularity.cbegin() + index);
        price.erase(price.cbegin()+ index);
        capacity.erase(capacity.cbegin()+ index);
        balance_items.erase(balance_items.cbegin()+ index);
        orders.erase(orders.cbegin() + index);
        number_items--;
        return answer;
    }
    else return "������ ������ ���. ";
}

std::string Cargo::dismiss_employees(int number) {
    if (number > 0 && number <= employee){
        if (balance >= number * 700){
            employee-=number;
            balance-=number*175;
            return "�� ������� ��������� �������. �� ��������� " + to_string(number*175) + "$ ���������. ";
        }
        else return "� ��� ��� �����, ����� ��������� ��������� �������. ��������� " + to_string(number*700) + "$ �� ����� ������. ";
    }
    else return "������������ ���������� �����������. ";
}

std::string Cargo::check_dismiss_employees(int number) {
    std::string answer;
    if (number > 0 && number <= employee) {
        answer = "�� ������ ������� " + to_string(number) +
                 " �����������. ��� ������� ��������� ��������� ��������� � ������� " +
                 to_string(number*700) + "$";
    }
    else {
        answer = "������������ ���������� �����������. ";
    }
    return answer;
}

std::string Cargo::promote_all() {
    double cost = 0;
    for (int index = 0; index < number_items; index++)
    {
        cost += pow(cur_popularity[index] / items[index].get_base_popularity(), 1.25) * 100;
    }
    if (balance >= cost){
        for (int index = 0; index < number_items; index++){
            change_popularity(index, my_random(0.0,1.0));
        }
        balance-=cost;
        return "�� ��������� " + to_string(cost) + " $ �� ������� ��������. ������������ ���� ������� �������. ";
    }
    else return "� ��� ��� ����� �� ���������� ��������� ��������. ��������� " + to_string(cost) +  "$";
}

std::string Cargo::check_promote_all() {
    double cost = 0;
    for (int index = 0; index < number_items; index++) {
        cost += pow(cur_popularity[index] / items[index].get_base_popularity(), 1.25) * 100;
    }
    std::string answer = "�������������� �������� ����� " + to_string(my_round(cost, 2)) +
                         "$ ��������� ������������ ���� �������. ";
    return answer;
}

std::string Cargo::promote_item(int index) {
    if (0 <= index && index < number_items){
        double cost = pow(cur_involvement[index] / items[index].get_base_involvement(), 1.25) * 100;
        if (cost <= balance){
            balance -= cost;
            change_involvement(index, my_random(0.0,1.0));
            return "�� ������� ��������� �������� ���������� " + to_string(cost)+ "$";
        }
        else return "� ��� ��� ����� �� ���������� ��������� ��������. ��������� " + to_string(cost) + "$";
    }
    else return "��� ������ ������.";
}

std::string Cargo::check_promote_item(int index) {
    std::string answer;
    if (0 <= index && index < number_items){
        double cost = pow(cur_involvement[index] / items[index].get_base_popularity(), 1.25) * 100;
        answer = "��������� ������� ��� ����� ������: " + to_string(my_round(cost, 2));
    }
    else answer = "������������ ����� ������. ";
    return answer;
}

std::string Cargo::day() {
    std::string answer = "����� " + name + " ������ �� ������ ���: " + to_string(my_round(balance, 2)) +  "$\n";
    if (balance > 0){
        for (int i = 8; i < 20; i++){
            answer += to_string(i) + ":00\n";
            for (int j = 0; j < number_items; j++){
                double x = price[j]/items[j].get_base_price();
                answer += buy(j, (int)((my_random(cur_involvement[j], cur_popularity[j])) * pow(16, log(1/x)))) + '\n';
            }
        }
        int free_employee = employee;
        for (int j = 0; j < number_items; j++){
            int order = ceil((double)orders[j]/ items[j].get_effectiveness());
            if (free_employee >= order){
                double income = price[j]*orders[j];
                balance += income;
                free_employee-=order;
                answer += items[j].get_name() + " �������� ����� �� " + to_string(orders[j]) + "��. �� ����������: " + to_string(
                        my_round(income, 2));
            }
            else{
                int reject = order - free_employee;
                double income = free_employee * items[j].get_effectiveness() * price[j];
                balance += income;
                answer += items[j].get_name();
                if (free_employee > 0) answer += " �������� ����� �� " + to_string(free_employee * items[j].get_effectiveness()) + "��. �� ����������: " + to_string(
                            my_round(income, 2));
                change_popularity(j, my_random(-(double)(reject/order), 0.0));
                answer += " �� �������� ����� �� " + to_string(reject*items[j].get_effectiveness()) + "��" + '\n';
                free_employee = 0;
            }
            orders[j] = 0;
        }
    }
    balance-=employee*100;
    answer += "\n�� ������ �������� ����������� ��������� " + to_string(employee*100) + "$\n";
    if (auto_refill) answer+=refill_all() + "\n";
    answer += "������ �� ����� ���: " + std::to_string(balance) + "$";
    return answer;
}

std::string Cargo::get_info_about_item(int index) {
    std::string answer;
    if (0 <= index && index < number_items) {
        answer = Seller::get_info_about_item(index);
        answer += "\n���� �������� ������ ������ : " + std::to_string(items[index].get_effectiveness());
    }
    else answer = "��� ������ ������.";
    return answer;
}

std::string Cargo::close() {
    double cur_balance = balance - 700*employee;
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
                    my_round(abs(cur_balance), 2)) + "$";
        }
        else{
            return "��� �� ������� ����� ��� �������� ������ �����������.";
        }
    }
}

std::string Cargo::up_capacity(int index) {
    if (0 <= index && index < number_items){
        if (balance > 500){
            balance-=40;
            capacity[index] += items[index].get_capacity();
            return "�� ��������� ����������� ������ " + items[index].get_name();
        }
        else return "�� �� ������ ���� ��������� ���������� �����������: ��� ����� 500$";
    }
    else return "������������ ����� ������.";
}
