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
        cout << "Родитель " << name << " рассказывает о своих детях:" << endl;
        for (Student* child : children) {
            cout << "Имя: " << child->getName() << ", возраст: " << child->getAge();
            if (mood == "Good") {
                cout << ", успеваемость: " << (child->isExcellentStudent() ? "отличная" : "не очень") << endl;
            }
            else {
                cout << ", настроение у родителя не очень хорошее" << endl;
            }
        }
    }

    void tellAboutRandomChild() const {
        if (children.empty()) {
            cout << "У родителя нет детей." << endl;
            return;
        }
        cout << "Родитель " << name << " рассказывает о случайном своем ребенке:" << endl;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, children.size() - 1);
        int index = dis(gen);
        Student* randomChild = children[index];
        cout << "Имя: " << randomChild->getName() << ", возраст: " << randomChild->getAge();
        if (mood == "Good") {
            cout << ", успеваемость: " << (randomChild->isExcellentStudent() ? "отличная" : "не очень") << endl;
        }
        else {
            cout << ", настроение у родителя не очень хорошее" << endl;
        }
    }

    void tellAboutAllChildrenSummary() const {
        cout << "Родитель " << name << " рассказывает обо всех своих детях в общем:" << endl;
        if (children.empty()) {
            cout << "У родителя нет детей." << endl;
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
        cout << "Средняя успеваемость детей: " << (averageGrade >= 4.5 ? "отличная" : "не очень") << endl;
        if (mood != "Good") {
            cout << "Настроение у родителя не очень хорошее" << endl;
        }
    }

    void tellAboutChild(const string& childName) const {
        cout << "Родитель " << name << " рассказывает о своем ребенке:" << endl;
        bool found = false;
        for (Student* child : children) {
            if (child->getName() == childName) {
                cout << "Имя: " << child->getName() << ", возраст: " << child->getAge();
                if (mood == "Good") {
                    cout << ", успеваемость: " << (child->isExcellentStudent() ? "отличная" : "не очень") << endl;
                }
                else {
                    cout << ", настроение у родителя не очень хорошее" << endl;
                }
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "У родителя нет ребенка с именем " << childName << endl;
        }
    }
};

int main() {
    Parent parent("Иванова Анна Петровна", 40);
    parent.setMood("Good");

    Student child1("Иванов Иван", 15);
    child1.addGrade(5);
    child1.addGrade(4);
    parent.addChild(child1);

    Student child2("Иванова Мария", 13);
    child2.addGrade(3);
    child2.addGrade(4);
    parent.addChild(child2);

    cout << "Содержание рассказов о детях родителя в зависимости от настроения и успеваемости:" << endl;
    parent.tellAboutAllChildren();
    parent.tellAboutRandomChild();
    parent.tellAboutAllChildrenSummary();
    parent.tellAboutChild("Иванов Иван");
    parent.tellAboutChild("Петров Петр");

    return 0;
}