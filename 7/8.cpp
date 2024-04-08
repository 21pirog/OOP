#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>

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
    Teacher(const string& n, int a) : Human(n, a), mood("Good"), eng(rd()), dist(0, 1), gradesCount(0) {}

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

    bool hasTeacher(const Teacher& teacher) const {
        return find(teachers.begin(), teachers.end(), &teacher) != teachers.end();
    }

    const vector<Student*>& getStudents() const {
        return students;
    }

    void conductLesson() {
        for (Teacher* teacher : teachers) {
            for (Student* student : students) {
                teacher->gradeStudent(*student);
            }
        }
    }

    const string& getName() const {
        return name;
    }
};

class Parent : public Human {
private:
    string mood;
    vector<Student*> children;

public:
    Parent(const string& n, int a) : Human(n, a), mood("Good") {}

    bool hasChild(const Student& student) const {
        return find(children.begin(), children.end(), &student) != children.end();
    }

    void setMood(const string& newMood) {
        mood = newMood;
    }

    void addChild(Student& child) {
        children.push_back(&child);
    }

    const vector<Student*>& getChildren() const {
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

class Meeting {
public:
    Meeting(const string& name) : name(name) {}

    void addParticipant(Teacher& teacher) {
        teachers.push_back(&teacher);
    }

    void addParticipant(Parent& parent) {
        parents.push_back(&parent);
    }

    void discussLessonsAndChildren() {
        for (Lesson& lesson : lessons) {
            cout << "�������� �� ��������: " << lesson.getName() << endl;

            for (Teacher* teacher : teachers) {
                if (lesson.hasTeacher(*teacher)) {
                    for (Student* student : lesson.getStudents()) {
                        Parent* parent = findParentOfStudent(*student);
                        if (parent) {
                            parent->tellAboutChild(student->getName());
                        }
                        else {
                            childrenWithoutParents.push_back(student);
                        }
                    }
                }
            }
        }

        if (!childrenWithoutParents.empty()) {
            cout << "���� ��� ��������� �� ��������:" << endl;
            for (const Student* student : childrenWithoutParents) {
                cout << student->getName() << endl;
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
        return 0;
    }

private:
    string name;
    vector<Teacher*> teachers;
    vector<Parent*> parents;
    vector<Lesson> lessons;
    vector<const Student*> childrenWithoutParents;
};

int main() {

    Student marina("������� ������", 15);
    Student mikhail("������ ������", 14);
    Student dmitriy("��������� �������", 16);

    marina.addGrade(5);
    mikhail.addGrade(4);
    dmitriy.addGrade(5);

    Parent anna("������� ����", 40);
    anna.addChild(marina);
    anna.addChild(mikhail);

    Parent oleg("��������� ����", 42);
    oleg.addChild(dmitriy);


    Teacher galina("������ ����������", 35);
    galina.setMood("Bad");

    Teacher boris("����� ����������", 45);
    boris.setMood("Good");

    Teacher petr("���� �����������", 50);
    petr.setMood("Good");


    Lesson math("����������");
    math.addTeacher(galina);
    math.addStudent(marina);
    math.addStudent(mikhail);
    math.addStudent(dmitriy);

    Lesson art("���");
    art.addTeacher(boris);
    art.addStudent(marina);
    art.addStudent(mikhail);
    art.addStudent(dmitriy);

    Lesson pe("�����������");
    pe.addTeacher(petr);
    pe.addStudent(marina);
    pe.addStudent(mikhail);
    pe.addStudent(dmitriy);

    math.conductLesson();
    art.conductLesson();
    pe.conductLesson();

    cout << "������ ������� �������� �� ������� ��������:" << endl;
    cout << "������� ������:" << endl;
    cout << "- ����������: " << marina.getGrades()[0] << endl;
    cout << "- ���: " << marina.getGrades()[1] << endl;
    cout << "- �����������: " << marina.getGrades()[2] << endl;

    cout << "������ ������:" << endl;
    cout << "- ����������: " << mikhail.getGrades()[0] << endl;
    cout << "- ���: " << mikhail.getGrades()[1] << endl;
    cout << "- �����������: " << mikhail.getGrades()[2] << endl;

    cout << "��������� �������:" << endl;
    cout << "- ����������: " << dmitriy.getGrades()[0] << endl;
    cout << "- ���: " << dmitriy.getGrades()[1] << endl;
    cout << "- �����������: " << dmitriy.getGrades()[2] << endl;


    Meeting meeting("������������ ��������");


    meeting.addParticipant(galina);
    meeting.addParticipant(boris);

    meeting.addParticipant(anna);


    meeting.addLesson(math);
    meeting.addLesson(art);

    meeting.discussLessonsAndChildren();

    return 0;
}
