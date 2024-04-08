#include <iostream>
#include <vector>
#include <string>

class Human {
protected:
    std::string name;
    int age;

public:
    Human() : name(""), age(0) {}

    const std::string& getName() const {
        return name;
    }

    void setName(const std::string& newName) {
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
public:
    Student() {}

    void addGrade(int grade) {
        grades.push_back(grade);
    }

    bool isExcellentStudent() const {
        return calculateAverageGrade() >= 4.5;
    }

    const std::string& getName() const {
        return name;
    }

private:
    double calculateAverageGrade() const {
        if (grades.empty()) {
            return 0.0;
        }

        double sum = 0.0;
        for (int grade : grades) {
            sum += grade;
        }

        return sum / grades.size();
    }

private:
    std::vector<int> grades;
};

int main() {
    setlocale(LC_ALL, "Russian");

    Student student1;
    student1.setName("Иванов");
    student1.setAge(20);
    student1.addGrade(5);
    student1.addGrade(4);
    student1.addGrade(4);

    Student student2;
    student2.setName("Петров");
    student2.setAge(21);
    student2.addGrade(5);
    student2.addGrade(5);
    student2.addGrade(4);

    std::cout << "Студент 1: " << student1.getName() << ", возраст " << student1.getAge() << " является отличником: " << (student1.isExcellentStudent() ? "Да" : "Нет") << std::endl;
    std::cout << "Студент 2: " << student2.getName() << ", возраст " << student2.getAge() << " является отличником: " << (student2.isExcellentStudent() ? "Да" : "Нет") << std::endl;

    return 0;
}
