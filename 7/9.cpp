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
        std::cout << "–одитель " << name << " рассказывает о своих дет€х:" << std::endl;
        for (Student* child : children) {
            std::cout << "»м€: " << child->getName() << ", возраст: " << child->getAge();
            if (mood == "Good") {
                std::cout << ", успеваемость: " << (child->isExcellentStudent() ? "отлична€" : "не очень") << std::endl;
            }
            else {
                std::cout << ", настроение у родител€ не очень хорошее" << std::endl;
            }
        }
    }

    void tellAboutRandomChild() const {
        if (children.empty()) {
            std::cout << "” родител€ нет детей." << std::endl;
            return;
        }
        std::cout << "–одитель " << name << " рассказывает о случайном своем ребенке:" << std::endl;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, children.size() - 1);
        int index = dis(gen);
        Student* randomChild = children[index];
        std::cout << "»м€: " << randomChild->getName() << ", возраст: " << randomChild->getAge();
        if (mood == "Good") {
            std::cout << ", успеваемость: " << (randomChild->isExcellentStudent() ? "отлична€" : "не очень") << std::endl;
        }
        else {
            std::cout << ", настроение у родител€ не очень хорошее" << std::endl;
        }
    }

    void tellAboutAllChildrenSummary() const {
        std::cout << "–одитель " << name << " рассказывает обо всех своих дет€х в общем:" << std::endl;
        if (children.empty()) {
            std::cout << "” родител€ нет детей." << std::endl;
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
        std::cout << "—редн€€ успеваемость детей: " << (averageGrade >= 4.5 ? "отлична€" : "не очень") << std::endl;
        if (mood != "Good") {
            std::cout << "Ќастроение у родител€ не очень хорошее" << std::endl;
        }
    }

    virtual void tellAboutChild(const Student* student) const {
        std::cout << "–одитель " << name << " рассказывает о своем ребенке:" << std::endl;
        bool found = false;
        for (Student* child : children) {
            if (child->getName() == student->getName()) {
                std::cout << "»м€: " << child->getName() << ", возраст: " << child->getAge();
                if (mood == "Good") {
                    std::cout << ", успеваемость: " << (child->isExcellentStudent() ? "отлична€" : "не очень") << std::endl;
                }
                else {
                    std::cout << ", настроение у родител€ не очень хорошее" << std::endl;
                }
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "” родител€ нет ребенка с именем " << student->getName() << std::endl;
        }
    }
};

class Grandmother : public Parent {
public:
    Grandmother(const std::string& name) : Parent(name, 60) {}

private:
    void tellAboutChild(const Student* student) const override {
        std::cout << "Ѕабушка " << getName() << " рассказывает о ребенке " << student->getName() << ": ";
        std::cout << "ќн у мен€ умничка." << std::endl;
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
            std::cout << "—обрание по предмету: " << lesson.getName() << std::endl;

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
            std::cout << "ƒети без родителей на собрании:" << std::endl;
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