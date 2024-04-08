#include <iostream>
#include <vector>
#include <string>
#include <random>
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
        return average > 4.5;
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

public:
    Teacher(const string& n, int a) : Human(n, a), mood("Good"), eng(rd()), dist(0, 1) {}

    void setMood(const string& newMood) {
        mood = newMood;
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
    }
};

int main() {
    Student student("Иванов", 20);
    Teacher teacher("Петрова Марина Геннадьевна", 35);

    teacher.setMood("Good");
    teacher.gradeStudent(student);

    cout << "Студент " << student.getName() << " получил следующие оценки: ";
    for (int grade : student.getGrades()) {
        cout << grade << " ";
    }
    cout << endl;

    return 0;
}