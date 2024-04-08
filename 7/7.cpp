#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
using namespace std;

class Human {
protected:
    string name;
    int age;

public:
    Human(const string& n, int a) : name(n), age(a) {}

    const string& getName() const {
        return name;
    }

    void setName(const string& newName) {
        name = newName;
    }

    int getAge() const {
        return age;
    }

    void setAge(int newAge) {
        age = newAge;
    }
};

class Student : public Human {
private:
    vector<int> grades;

public:
    Student(const string& n, int a) : Human(n, a) {}

    void addGrade(int grade) {
        grades.push_back(grade);
    }

    bool isExcellentStudent() const {
        if (grades.empty())
            return false;

        double average = 0.0;
        for (int grade : grades) {
            average += grade;
        }
        average /= grades.size();
        return average >= 4.5;
    }

    const vector<int>& getGrades() const {
        return grades;
    }
};

class Teacher : public Human {
private:
    string mood;
    random_device rd;
    default_random_engine eng;
    uniform_int_distribution<int> dist;
    int gradesCount;
public:
    Teacher(const string& n, int a) : Human(n, a), mood("Good"), eng(rd()), dist(0, 1) {}

    void setMood(const string& newMood) {
        mood = newMood;
    }

    string getMood() const {
        return mood;
    }
    void gradeStudent(Student& student) {
        int grade = 0;

        if (mood == "Good") {
            grade = student.isExcellentStudent() ? 5 : 4;
        }
        else if (mood == "Bad") {
            grade = student.isExcellentStudent() ? (dist(eng) == 0 ? 4 : 5) : (dist(eng) == 0 ? 2 : 3);
        }

        student.addGrade(grade);
        gradesCount++;

        if (gradesCount == 5) {
            gradesCount = 0;
            mood = (dist(eng) == 0 ? "Good" : "Bad");
        }
    }
};
class Parent : public Human {
private:
    string mood;
    vector<Student*> children;

public:
    Parent(const string& n, int a) : Human(n, a), mood("Good") {}

    void setMood(const string& newMood) {
        mood = newMood;
    }

    void addChild(Student& child) {
        children.push_back(&child);
    }

    void tellAboutAllChildren() const {
        cout << "�������� " << name << " ������������ � ����� �����:" << endl;
        for (Student* child : children) {
            cout << "���: " << child->getName() << ", �������: " << child->getAge();
            if (mood == "Good") {
                cout << ", ������������: " << (child->isExcellentStudent() ? "��������" : "�� �����") << endl;
            }
            else {
                cout << ", ���������� � �������� �� ����� �������" << endl;
            }
        }
    }

    void tellAboutRandomChild() const {
        if (children.empty()) {
            cout << "� �������� ��� �����." << endl;
            return;
        }
        cout << "�������� " << name << " ������������ � ��������� ����� �������:" << endl;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, children.size() - 1);
        int index = dis(gen);
        Student* randomChild = children[index];
        cout << "���: " << randomChild->getName() << ", �������: " << randomChild->getAge();
        if (mood == "Good") {
            cout << ", ������������: " << (randomChild->isExcellentStudent() ? "��������" : "�� �����") << endl;
        }
        else {
            cout << ", ���������� � �������� �� ����� �������" << endl;
        }
    }

    void tellAboutAllChildrenSummary() const {
        cout << "�������� " << name << " ������������ ��� ���� ����� ����� � �����:" << endl;
        if (children.empty()) {
            cout << "� �������� ��� �����." << endl;
            return;
        }
        double totalAverageGrade = 0.0;
        for (Student* child : children) {
            if (child->isExcellentStudent()) {
                totalAverageGrade += 5.0;
            }
            else {
                totalAverageGrade += 2.0;
            }
        }
        double averageGrade = totalAverageGrade / children.size();
        cout << "������� ������������ �����: " << (averageGrade >= 4.5 ? "��������" : "�� �����") << endl;
        if (mood != "Good") {
            cout << "���������� � �������� �� ����� �������" << endl;
        }
    }

    void tellAboutChild(const string& childName) const {
        cout << "�������� " << name << " ������������ � ����� �������:" << endl;
        bool found = false;
        for (Student* child : children) {
            if (child->getName() == childName) {
                cout << "���: " << child->getName() << ", �������: " << child->getAge();
                if (mood == "Good") {
                    cout << ", ������������: " << (child->isExcellentStudent() ? "��������" : "�� �����") << endl;
                }
                else {
                    cout << ", ���������� � �������� �� ����� �������" << endl;
                }
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "� �������� ��� ������� � ������ " << childName << endl;
        }
    }
};

int main() {
    Parent parent("������� ���� ��������", 40);
    parent.setMood("Good");

    Student child1("������ ����", 15);
    child1.addGrade(5);
    child1.addGrade(4);
    parent.addChild(child1);

    Student child2("������� �����", 13);
    child2.addGrade(3);
    child2.addGrade(4);
    parent.addChild(child2);

    cout << "���������� ��������� � ����� �������� � ����������� �� ���������� � ������������:" << endl;
    parent.tellAboutAllChildren();
    parent.tellAboutRandomChild();
    parent.tellAboutAllChildrenSummary();
    parent.tellAboutChild("������ ����");
    parent.tellAboutChild("������ ����");

    return 0;
}