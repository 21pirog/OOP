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

class GoodBadTeacher : public Human {
public:
    GoodBadTeacher(const string& n, int a) : Human(n, a), eng(rd()), dist(0, 1) {}
    random_device rd;
    default_random_engine eng;
    uniform_int_distribution<int> dist;

    void addGrade(Student& student) {
        student.addGrade(grade);

    }
private:
    int grade = (dist(eng) == 0 ? 2 : 5);
    std::string name;
};

class Lesson {
private:
    string name;
    vector<Teacher*> teachers;
    vector<Student*> students;

public:
    Lesson(const string& lessonName) : name(lessonName) {}

    void addTeacher(Teacher& teacher) {
        teachers.push_back(&teacher);
    }

    void addStudent(Student& student) {
        students.push_back(&student);
    }

    void conductLesson() {
        for (Teacher* teacher : teachers) {
            for (Student* student : students) {
                teacher->gradeStudent(*student);
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Student student1("Иванов", 20);
    Student student2("Петров", 21);

    student1.addGrade(5);
    student1.addGrade(5);
    student2.addGrade(2);
    student2.addGrade(2);

    Teacher teacher("Петрова Марина Геннадьевна", 35); 
    teacher.setMood("Bad");

    for (int i = 1; i < 8; ++i) {
        teacher.gradeStudent(student1);
        teacher.gradeStudent(student2);
        cout << teacher.getMood() << endl;
    }

    cout << "После проведения занятия:" << endl;
    cout << "Студент " << student1.getName() << " получил следующие оценки: ";
    for (int grade : student1.getGrades()) {
        cout << grade << " ";
    }
    cout << endl;

    cout << "Студент " << student2.getName() << " получил следующие оценки: ";
    for (int grade : student2.getGrades()) {
        cout << grade << " ";
    }
    cout << endl;

    return 0;
}
