#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Human {
protected:
    string name;
    int age;

public:
    Human() : name(""), age(0) {}

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
    Student() {}

    Student(const string& name, int age) : Human(name, age) {}

    void addGrade(int grade) {
        grades.push_back(grade);
    }

    bool isExcellentStudent() const {
        return calculateAverageGrade() >= 4.5;
    }

    const string& getName() const {
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
};

class Teacher : public Human {
public:
    Teacher() {}

    Teacher(const string& name, int age) : Human(name, age) {}

    void gradeStudent(Student& student, int grade) {
        student.addGrade(grade);
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Student student1;
    student1.setName("Иванов");
    student1.setAge(20);

    Student student2;
    student2.setName("Петров");
    student2.setAge(21);

    Teacher teacher;
    teacher.setName("Петрова Марина Геннадьевна");
    teacher.setAge(35);

    teacher.gradeStudent(student1, 5);
    teacher.gradeStudent(student1, 3);

    teacher.gradeStudent(student2, 5);
    teacher.gradeStudent(student2, 4);

    std::cout << "Студент 1: " << student1.getName() << ", возраст " << student1.getAge() << " является отличником: " << (student1.isExcellentStudent() ? "Да" : "Нет") << std::endl;
    std::cout << "Студент 2: " << student2.getName() << ", возраст " << student2.getAge() << " является отличником: " << (student2.isExcellentStudent() ? "Да" : "Нет") << std::endl;

    return 0;
}
