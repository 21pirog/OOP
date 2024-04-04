#include<iostream>
#include <vector>
#include <ctime>

using namespace std;

class Pizza {

public:
    virtual void Cost() = 0;
    virtual double GetCost() {
        return 0.0;
    }
    virtual void Print_Info() = 0;
    virtual void Set_Size(int size_in) = 0;
    virtual void Add_Salt() = 0;
    virtual void Add_Cheese() = 0;

};

class Diabolo : public Pizza {
private:
    string Name;
    string Info;
    unsigned int Size;
    double cost;
    unsigned int price_factor = 3;
    unsigned int Salt_value;
    unsigned int Cheese_value;

public:
    Diabolo() { Name = "�������"; Info = "������ ����� � ������ � ��������� ���������. ������ ���������� ��������."; Size = 0; cost = 0; Salt_value = 0; Cheese_value = 0; }

    int getPriceFactor() const {
        return price_factor;
    }

    void Cost() override {
        switch (this->Size) {
        case 25:
            this->cost += 100 * getPriceFactor() + this->Cheese_value * 20 + this->Salt_value;
            break;
        case 30:
            this->cost += 150 * getPriceFactor() + this->Cheese_value * 20 + this->Salt_value;
            break;
        case 35:
            this->cost += 200 * getPriceFactor() + this->Cheese_value * 20 + this->Salt_value;
            break;
        case 40:
            this->cost += 300 * getPriceFactor() + this->Cheese_value * 20 + this->Salt_value;
            break;
        default:
            cout << "�������� ������ �����!\n";
            break;
        }
    }

    void Print_Info() {
        cout << "��������: " << this->Name << endl;
        cout << "����������: " << this->Info << endl;
        cout << "������: " << this->Size << endl;
        cout << "���. ���: " << this->Cheese_value << endl;
        cout << "���. ����: " << this->Salt_value << endl;
        cout << "����: " << this->cost << endl;
    }

    void Set_Size(int size_in) override {
        switch (size_in) {
        case 1:
            this->Size = 25;
            break;
        case 2:
            this->Size = 30;
            break;
        case 3:
            this->Size = 35;
            break;
        case 4:
            this->Size = 40;
            break;
        default:
            cout << "� ��� ��� ������ �������!\n";
            break;
        }
    }

    double GetCost() {
        return this->cost;
    }

    void Add_Cheese() override {
        unsigned int chesse_in = 0;
        cout << "������� �������� ���� ��������?\n";
        cin >> chesse_in;
        if (chesse_in > 0)
            this->Cheese_value = chesse_in;
    };

    void Add_Salt() override {
        unsigned int salt_in = 0;
        cout << "������� ����� ���� ��������?\n";
        cin >> salt_in;
        if (salt_in > 0)
            this->Salt_value = salt_in;
    };

};

class Pepperoni : public Pizza {
private:
    string Name;
    string Info;
    unsigned int Size;
    double cost;
    unsigned int price_factor = 4;
    unsigned int Salt_value;
    unsigned  Cheese_value;

public:
    Pepperoni() { Name = "���������"; Info = "��������� ��������� �� ������� �� ��������� �����. ��������, �� ����������"; Size = 0; cost = 0; Salt_value = 0; Cheese_value = 0; }

    void Print_Info() {
        cout << "��������: " << this->Name << endl;
        cout << "����������: " << this->Info << endl;
        cout << "������: " << this->Size << endl;
        cout << "���. ���: " << this->Cheese_value << endl;
        cout << "���. ����: " << this->Salt_value << endl;
        cout << "����: " << this->cost << endl;
    }

    int getPriceFactor() const {
        return price_factor;
    }

    void Set_Size(int size_in) override {
        switch (this->Size) {
        case 25:
            this->cost += 100 * getPriceFactor() + this->Cheese_value * 20 + this->Salt_value;
            break;
        case 30:
            this->cost += 150 * getPriceFactor() + this->Cheese_value * 20 + this->Salt_value;
            break;
        case 35:
            this->cost += 200 * getPriceFactor() + this->Cheese_value * 20 + this->Salt_value;
            break;
        case 40:
            this->cost += 300 * getPriceFactor() + this->Cheese_value * 20 + this->Salt_value;
            break;
        default:
            cout << "�������� ������ �����!\n";
            break;
        }
    }
    void Cost() override {
        switch (this->Size) {
        case 25:
            this->cost += 100 + this->Cheese_value * 20 + this->Salt_value;
            break;
        case 30:
            this->cost += 250 + this->Cheese_value * 20 + this->Salt_value;
            break;
        case 35:
            this->cost += 325 + this->Cheese_value * 20 + this->Salt_value;
            break;
        case 40:
            this->cost += 475 + this->Cheese_value * 20 + this->Salt_value;
            break;
        default:
            cout << "�������� ������ �����!\n";
            break;
        }
    }

    double GetCost() {
        return this->cost;
    }

    void Add_Cheese() override {
        unsigned int chesse_in = 0;
        cout << "������� �������� ���� ��������?\n";
        cin >> chesse_in;
        if (chesse_in > 0)
            this->Cheese_value = chesse_in;
    };

    void Add_Salt() override {
        unsigned int salt_in = 0;
        cout << "������� ����� ���� ��������?\n";
        cin >> salt_in;
        if (salt_in > 0)
            this->Salt_value = salt_in;
    };

};

class Margaritha : public Pizza {
private:
    string Name;
    string Info;
    unsigned int Size;
    double cost;
    unsigned int price_factor = 2;
    unsigned int Salt_value;
    unsigned int Cheese_value;

public:
    Margaritha() { Name = "���������"; Info = "������, ���������, ������� - ��������� ��� ���������. �������� ����: ��� ������� � ����� �������� ������."; Size = 0; cost = 0; Salt_value = 0; Cheese_value = 0; }

    int getPriceFactor() const {
        return price_factor;
    }

    void Print_Info() {
        cout << "��������: " << this->Name << endl;
        cout << "����������: " << this->Info << endl;
        cout << "������: " << this->Size << endl;
        cout << "���. ���: " << this->Cheese_value << endl;
        cout << "���. ����: " << this->Salt_value << endl;
        cout << "����: " << this->cost << endl;
    }

    void Set_Size(int size_in) override {
        switch (size_in) {
        case 1:
            this->Size = 25;
            break;
        case 2:
            this->Size = 30;
            break;
        case 3:
            this->Size = 35;
            break;
        case 4:
            this->Size = 40;
            break;
        default:
            cout << "� ��� ��� ������ �������!\n";
            break;
        }
    }

    void Cost() override {
        switch (this->Size) {
        case 25:
            this->cost += 100 * getPriceFactor() + this->Cheese_value * 20 + this->Salt_value;
            break;
        case 30:
            this->cost += 150 * getPriceFactor() + this->Cheese_value * 20 + this->Salt_value;
            break;
        case 35:
            this->cost += 200 * getPriceFactor() + this->Cheese_value * 20 + this->Salt_value;
            break;
        case 40:
            this->cost += 300 * getPriceFactor() + this->Cheese_value * 20 + this->Salt_value;
            break;
        default:
            cout << "�������� ������ �����!\n";
            break;
        }
    }

    double GetCost() {
        return this->cost;
    }

    void Add_Cheese() override {
        unsigned int chesse_in = 0;
        cout << "������� �������� ���� ��������?\n";
        cin >> chesse_in;
        if (chesse_in > 0)
            this->Cheese_value = chesse_in;
    };

    void Add_Salt() override {
        unsigned int salt_in = 0;
        cout << "������� ����� ���� ��������?\n";
        cin >> salt_in;
        if (salt_in > 0)
            this->Salt_value = salt_in;
    };

};

class Menu {

private:
    vector <Pizza*> Order_List;
public:

    void Print_Menu() {
        int in = 0;
        cout << "���� �������� 'Cacado' \n�������� ��������:\n";
        cout << "1)�������� ����� � �����\n";
        cout << "2)�������� ��� � ��������\n";
        cout << "3)����\n";
        cin >> in;
        cout << endl;
        while ((in > 3) and (in < 0)) {
            cin >> in;
            cout << endl;
        }


        switch (in) {
        case 1:
            Choose_Pizza();
            break;
        case 2:
            Print_Order();
            break;
        case 3:
            cout << "�� ���� ������ �� ������.." << endl;
            break;
        default:
            cout << "�������� ������ ��������!\n\n";
            Print_Menu();
        }
    };

    void Choose_Pizza() {
        int in = 0;
        Pizza* pizza = nullptr;
        cout << "�������� ����� �� ������:\n";
        cout << "1)�������\n";
        cout << "2)���������\n";
        cout << "3)���������\n";
        cout << "4)����\n\n";
        cin >> in;
        cout << endl;
        switch (in) {
        case 1:
            pizza = new Diabolo();
            break;
        case 2:
            pizza = new Pepperoni();
            break;
        case 3:
            pizza = new Margaritha();
            break;
        case 4:
            Print_Menu();
        }

        cout << "�������� ������ �����:\n";
        cout << "1)25\n";
        cout << "2)30\n";
        cout << "3)35\n";
        cout << "4)40\n\n";

        cin >> in;
        cout << endl;
        if (in > 0 and in < 5) {
            pizza->Set_Size(in);
            pizza->Add_Cheese();
            pizza->Add_Salt();
            pizza->Cost();
            this->Order_List.push_back(pizza);
            cout << endl;
            Print_Menu();
        }
        else {
            cout << "������� �� ����!";
            Print_Menu();
        };

    };

    void Print_Order() {
        cout << "��� ��� �����: \n\n";
        for (int i = 0; i < this->Order_List.size(); i++) {
            cout << "������� " << i + 1 << "\n\n";
            this->Order_List[i]->Print_Info();
            cout << endl;
        }
        Print_Sum();
    };

    void Print_Sum() {
        double Sum = 0.0;
        for (int i = 0; i < this->Order_List.size(); i++) {
            Sum += this->Order_List[i]->GetCost();
        }
        cout << "��� = " << Sum;
    }
};

int main() {

    Menu window;
    window.Print_Menu();
    return 0;
}