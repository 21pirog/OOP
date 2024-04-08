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

    void addGradeRandomly(Student& student) {
        int grade = dist(eng) + 2; // генерируем оценку от 2 до 5
        student.addGrade(grade);
    }
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

    Teacher teacher("Петрова Марина Геннадьевна", 35);

    student1.addGrade(5);
    student1.addGrade(5);
    student2.addGrade(2);
    student2.addGrade(2);

    teacher.setMood("Bad");
    Lesson lesson("Математика");
    lesson.addTeacher(teacher);
    lesson.addStudent(student1);
    lesson.addStudent(student2);

    lesson.conductLesson();

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