#include "Shop.h"

Shop::Shop(Organization *owner, std::string name) {
    this->owner = owner;
    this->name = name;
}

std::string Shop::add_item(Item item) {
    std::string answer;
    if (number_items < employee*5 && balance >= 100){
        items.push_back(item);
        price.push_back(item.get_base_price());
        cur_involvement.push_back(item.get_base_involvement());
        cur_popularity.push_back(item.get_base_popularity());
        capacity.push_back(item.get_capacity());
        balance_items.push_back(0);
        balance-=100;
        number_items++;
        answer = "�� ��������� ����������� �� 100$.";
    }
    else if (number_items < employee*5 && balance < 100){
        answer = "�� �� ������ ��������� ����������� ��������: ��������� ����� �� ����� �������� �� ����� 100$";
    }
    else{
        answer = "�� �� ������ ��������� ����������� ��������: �������� ����� ��������� ���� " + std::to_string(employee*5) + " �������.";
    }
    return answer;

}

std::string Shop::check_add_item() {
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

std::string Shop::buy(int index, int count) {
    std::string answer;
    if (0 <= index && index <= number_items){
        answer+=items[index].get_name();
        if (count <= balance_items[index]){
            double income =  price[index] * count;
            balance += price[index] * count;
            balance_items[index] -= count;
            answer += " ������� ������ " + std::to_string(count) + " ��. �� ����������: " + to_string(my_round(income, 2)) + "$\n";
        }
        else {
            cur_popularity[index] -= my_random(0.0, 0.1*cur_popularity[index]);
            if (cur_involvement[index] > cur_popularity[index]) cur_involvement[index] = cur_popularity[index];
            answer += " ������� �� ������ ������ ����� ��-�� ��� ���������� � ����������� ����������. \n";
        }
    }
    else answer = "������ �� ����������. ";
    return answer;
}

std::string Shop::remove_item(int index) {
    std::string answer;
    if (0 <= index && index < number_items){
        answer = items[index].get_name() + " �� ����� ����� � ������. ";
        double refund = balance_items[index] * items[index].get_base_price() * 0.5;
        balance += refund;
        answer += " �� ������� ����� ������������� � �������� �������� ���������: " + to_string(my_round(refund, 2)) + "$";
        items.erase(items.cbegin() + index);
        cur_involvement.erase(cur_involvement.cbegin() + index);
        cur_popularity.erase(cur_popularity.cbegin() + index);
        price.erase(price.cbegin() + index);
        capacity.erase(capacity.cbegin() + index);
        balance_items.erase(balance_items.cbegin() + index);
        number_items--;
    }
    else answer = "��� ������ ������.";
    return answer;
}

std::string Shop::dismiss_employees(int number) {
    std::string answer;
    if (number > 0 && number <= employee){
        if ((employee - number) * 5 >= number_items){
            if (balance >= number * 175){
                employee-=number;
                balance-=number*175;
                answer = "�� ������� ����������� � ��������� ��������� ��������� � ������� " +
                         to_string(number*175) + "$";
            }
            else answer = "�� �� ������ ������� �����������, ��� ��� ��� ����� �� ������� ��������� � ������� " +
                         to_string(number*175) + "$";
        }
        else answer = "�� �� ������ ��������� ���� ������� �����������: � ����� ������ ��� �� ������ ���������� �� ������������ ������������.";
    }
    else answer = "������������ ���������� �����������. ";
    return answer;
}

std::string Shop::check_dismiss_employees(int number) {
    std::string answer;
    if (number > 0 && number <= employee) {
        if ((employee - number) * 5 >= number_items) {
            answer = "�� ������ ������� " + to_string(number) +
                     " �����������. ��� ������� ��������� ��������� ��������� � ������� " +
                     to_string(number*175) + "$";
        }
        else {
            answer = "�� �� ������ ��������� ���� ������� �����������: � ����� ������ ��� �� ������ ���������� �� ������������ ������������.";
        }
    }
    else {
        answer = "������������ ���������� �����������. ";
    }
    return answer;
}

std::string Shop::promote_all() {
    double cost = 0;
    std::string answer;
    for (int index = 0; index < number_items; index++)
    {
        cost += pow(cur_popularity[index] / items[index].get_base_popularity(), 1.5) * 100;
    }
    if (balance >= cost){
        for (int index = 0; index < number_items; index++){
            change_popularity(index, my_random(0.0, 1.0));
        }
        balance-=cost;
        answer  = "�� ������� ��������� �������� ���������� " + to_string(my_round(cost, 2)) +
                             "$ ��������� ������������ ���� �������. ";
    }
    else  answer  = "�� �� ������ �������� ��������� �������� ���������� " + to_string(my_round(cost, 2)) +
                    "$ , ��� ��� �� ����� �������� ������������ �����.";
    return answer;
}

std::string Shop::check_promote_all() {
    double cost = 0;
    for (int index = 0; index < number_items; index++) {
        cost += pow(cur_popularity[index] / items[index].get_base_popularity(), 1.5) * 100;
    }
    std::string answer = "�������������� �������� ����� " + to_string(my_round(cost, 2)) +
                         "$ ��������� ������������ ���� �������. ";
    return answer;
}

std::string Shop::promote_item(int index) {
    if (0 <= index && index < number_items){
        double cost = pow(cur_involvement[index] / items[index].get_base_involvement(), 1.5) * 100;
        if (cost <= balance){
            balance -= cost;
            change_involvement(index, my_random(0.0, 1.0));
            return "�� ������� ��������� �������� ���������� " + std::to_string(my_round(cost, 2));
        }
        else return "�� �� ������� ��������� ��������: ��������� ����� �� ����� �������� �� ����� " + std::to_string(my_round(cost, 2));
    }
    else return "����� ����� �� ����������. ";
}

std::string Shop::check_promote_item(int index) {
    std::string answer;
    if (0 <= index && index < number_items){
        double cost = pow(cur_involvement[index] / items[index].get_base_involvement(), 1.5) * 100;
        return "��������� ������� ��� ����� ������: " + to_string(my_round(cost, 2));
    }
    else return "������������ ����� ������. ";

}

std::string Shop::day() {
    std::string answer = "������� " + name + " ������ �� ������ ���: " + to_string(my_round(balance,2)) + "$\n";
    if (balance >= 0){
        for (int i = 8; i < 22; i++){
            answer += std::to_string(i) + ":00\n";
            for (int j = 0; j < number_items; j++){
                double x = price[j]/items[j].get_base_price();
                answer += buy(j, (int)((my_random(cur_involvement[j], cur_popularity[j])) * pow(2, log(1/(2*x-1)))));
            }
        }
    }
    balance -= employee * 25;
    answer += "�� ������ �������� ����������� ��������� " + to_string(employee*25) + "$\n";
    if (auto_refill) answer+=refill_all() + "\n";
    answer += "������ �� ����� ���: " + to_string(my_round(balance,2)) + "$\n";
    return answer;
}

std::string Shop::up_capacity(int index) {
    if (0 <= index && index < number_items){
        if (capacity[index] / items[index].get_capacity() == 1) {
            if (balance > 500){
                balance-=40;
                capacity[index] *= 2;
                return "�� ��������� ����������� ������ " + items[index].get_name();
            }
            else return "�� �� ������ ���� ��������� ���������� �����������: ��� ����� 500$";
        }
        else return "�� �� ������ ��������� ����������� ����� ������: ������� ����� ��������� ����������� ���� ����� ���� ���.";
    }
    else return "������������ ����� ������.";
}
