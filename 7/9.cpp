#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>

class Human {
protected:
    std::string name;
    int age;

public:
    Human(const std::string& n, int a) : name(n), age(a) {}

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
private:
    std::vector<int> grades;

public:
    Student(const std::string& n, int a) : Human(n, a) {}

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

    const std::vector<int>& getGrades() const {
        return grades;
    }
};

class Teacher : public Human {
private:
    std::string mood;
    std::random_device rd;
    std::default_random_engine eng;
    std::uniform_int_distribution<int> dist;
    int gradesCount;
public:
    Teacher(const std::string& n, int a) : Human(n, a), mood("Good"), eng(rd()), dist(0, 1), gradesCount(0) {}

    void setMood(const std::string& newMood) {
        mood = newMood;
    }

    std::string getMood() const {
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

class Lesson {
private:
    std::string name;
    std::vector<Teacher*> teachers;
    std::vector<Student*> students;

public:
    Lesson(const std::string& lessonName) : name(lessonName) {}

    void addTeacher(Teacher& teacher) {
        teachers.push_back(&teacher);
    }

    void addStudent(Student& student) {
        students.push_back(&student);
    }

    bool hasTeacher(const Teacher& teacher) const {
        return std::find(teachers.begin(), teachers.end(), &teacher) != teachers.end();
    }

    const std::vector<Student*>& getStudents() const {
        return students;
    }

    void conductLesson() {
        for (Teacher* teacher : teachers) {
            for (Student* student : students) {
                teacher->gradeStudent(*student);
            }
        }
    }

    const std::string& getName() const {
        return name;
    }
};

class Parent : public Human {
protected:
    std::string mood;
    std::vector<Student*> children;

public:
    Parent(const std::string& n, int a) : Human(n, a), mood("Good") {}

    bool hasChild(const Student& student) const {
        return std::find(children.begin(), children.end(), &student) != children.end();
    }

    void setMood(const std::string& newMood) {
        mood = newMood;
    }

    void addChild(Student& child) {
        children.push_back(&child);
    }

    const std::vector<Student*>& getChildren() const {
        return children;
    }

    bool childrenHaveGrades() const {
        for (const Student* child : children) {
            if (!child->getGrades().empty()) {
                return true;
            }
        }
        return false;
    }

    void tellAboutAllChildren() const {
        std::cout << "�������� " << name << " ������������ � ����� �����:" << std::endl;
        for (Student* child : children) {
            std::cout << "���: " << child->getName() << ", �������: " << child->getAge();
            if (mood == "Good") {
                std::cout << ", ������������: " << (child->isExcellentStudent() ? "��������" : "�� �����") << std::endl;
            }
            else {
                std::cout << ", ���������� � �������� �� ����� �������" << std::endl;
            }
        }
    }

    void tellAboutRandomChild() const {
        if (children.empty()) {
            std::cout << "� �������� ��� �����." << std::endl;
            return;
        }
        std::cout << "�������� " << name << " ������������ � ��������� ����� �������:" << std::endl;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, children.size() - 1);
        int index = dis(gen);
        Student* randomChild = children[index];
        std::cout << "���: " << randomChild->getName() << ", �������: " << randomChild->getAge();
        if (mood == "Good") {
            std::cout << ", ������������: " << (randomChild->isExcellentStudent() ? "��������" : "�� �����") << std::endl;
        }
        else {
            std::cout << ", ���������� � �������� �� ����� �������" << std::endl;
        }
    }

    void tellAboutAllChildrenSummary() const {
        std::cout << "�������� " << name << " ������������ ��� ���� ����� ����� � �����:" << std::endl;
        if (children.empty()) {
            std::cout << "� �������� ��� �����." << std::endl;
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
        std::cout << "������� ������������ �����: " << (averageGrade >= 4.5 ? "��������" : "�� �����") << std::endl;
        if (mood != "Good") {
            std::cout << "���������� � �������� �� ����� �������" << std::endl;
        }
    }

    virtual void tellAboutChild(const Student* student) const {
        std::cout << "�������� " << name << " ������������ � ����� �������:" << std::endl;
        bool found = false;
        for (Student* child : children) {
            if (child->getName() == student->getName()) {
                std::cout << "���: " << child->getName() << ", �������: " << child->getAge();
                if (mood == "Good") {
                    std::cout << ", ������������: " << (child->isExcellentStudent() ? "��������" : "�� �����") << std::endl;
                }
                else {
                    std::cout << ", ���������� � �������� �� ����� �������" << std::endl;
                }
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "� �������� ��� ������� � ������ " << student->getName() << std::endl;
        }
    }
};

class Grandmother : public Parent {
public:
    Grandmother(const std::string& name) : Parent(name, 60) {}

private:
    void tellAboutChild(const Student* student) const override {
        std::cout << "������� " << getName() << " ������������ � ������� " << student->getName() << ": ";
        std::cout << "�� � ���� �������." << std::endl;
    }
};

class Meeting {
public:
    Meeting(const std::string& name) : name(name) {}

    void addParticipant(Teacher& teacher) {
        teachers.push_back(&teacher);
    }

    void addParticipant(Parent& parent) {
        parents.push_back(&parent);
    }

    void discussLessonsAndChildren() {
        for (Lesson& lesson : lessons) {
            std::cout << "�������� �� ��������: " << lesson.getName() << std::endl;

            for (Teacher* teacher : teachers) {
                if (lesson.hasTeacher(*teacher)) {
                    for (Student* student : lesson.getStudents()) {
                        Parent* parent = findParentOfStudent(*student);
                        if (parent) {
                            parent->tellAboutChild(student);
                        }
                        else {
                            childrenWithoutParents.push_back(student);
                        }
                    }
                }
            }
        }

        if (!childrenWithoutParents.empty()) {
            std::cout << "���� ��� ��������� �� ��������:" << std::endl;
            for (const Student* student : childrenWithoutParents) {
                std::cout << student->getName() << std::endl;
            }
        }
    }

    void addLesson(const Lesson& lesson) {
        lessons.push_back(lesson);
    }

private:
    Parent* findParentOfStudent(const Student& student) {
        for (Parent* parent : parents) {
            if (parent->hasChild(student)) {
                return parent;
            }
        }
        return nullptr;
    }

private:
    std::string name;
    std::vector<Teacher*> teachers;
    std::vector<Parent*> parents;
    std::vector<Lesson> lessons;
    std::vector<const Student*> childrenWithoutParents;
};

int main() {
    return 0;
}