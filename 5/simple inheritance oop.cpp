#include <iostream>
#include <string>
using namespace std;

class Human {
protected:
    string name;
    int age;

public:
    Human(const string& name, int age) : name(name), age(age) {}

    const string& getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    void setName(const string& _name) {
        name = _name;
    }

    void setAge(int _age) {
        age = _age;
    }
};

class Student : public Human {
private:
    string university;
    int course;

public:
    Student(const string& name, int age, const string& university, int course)
        : Human(name, age), university(university), course(course) {}

    const string& getUniversity() const {
        return university;
    }

    int getCourse() const {
        return course;
    }

    void setUniversity(const string& _university) {
        university = _university;
    }

    void setCourse(int _course) {
        course = _course;
    }
};

class Superhero : public Human {
private:
    string superpower;
    string comics;

public:
    Superhero(const string& name, int age, const string& superpower, const string& comics)
        : Human(name, age), superpower(superpower), comics(comics) {}

    const string& getSuperpower() const {
        return superpower;
    }
    const string& getComics() const {
        return comics;
    }

    void setSuperpower(const string& _superpower) {
        superpower = _superpower;
    }

    void setComics(const string& _comics) {
        comics = _comics;
    }
};

class Employee : public Human {
private:
    string qualification;

public:
    Employee(const string& name, int age, const string& qualification)
        : Human(name, age), qualification(qualification) {}

    const string& getQualification() const {
        return qualification;
    }

    void setQualification(const string& _qualification) {
        qualification = _qualification;
    }
};

class Club {
private:
    string name;
    string activity;

public:
    Club(const string& name, const string& activity)
        : name(name), activity(activity) {}

    const string& getClubName() const {
        return name;
    }

    const string& getActivity() const {
        return activity;
    }
    void setClubName(const string& _name) {
        name = _name;
    }

    void setActivity(const string& _activity) {
        activity = _activity;
    }
};

class Activist : public Club, public Student {
private:
    string project;

public:
    Activist(const string& name, int age, const string& university, int course,
        const string& qualification, const string& project)
        : Club(name, ""), Student(name, age, university, course), project(project) {} // Исправлен вызов конструктора родительского класса Club

    const string& getProject() const {
        return project;
    }

    void setProject(const string& _project) {
        project = _project;
    }
};

int main() {

    Student student("Alice", 20, "MGU", 2);
    Superhero superhero("Clark", 35, "Flight", "Superman");
    Employee employee("David", 25, "Lector");
    Activist activist("Bob", 30, "FEFU", 3, "Researcher", "IT science");
    cout << "Student: " << student.getName() << ", Age: " << student.getAge()
        << ", University: " << student.getUniversity() << ", Course: " << student.getCourse() << endl;

    cout << "Superhero: " << superhero.getName() << ", Age: " << superhero.getAge()
        << ", Superpower: " << superhero.getSuperpower() << ", Comics: " << superhero.getComics() << endl;

    cout << "Employee: " << employee.getName() << ", Age: " << employee.getAge()
        << ", Qualification: " << employee.getQualification() << endl;

    cout << "Activist: " << activist.getClubName() << ", Age: " << activist.getAge()
        << ", University: " << activist.getUniversity() << ", Course: " << activist.getCourse()
        << ", Project: " << activist.getProject() << endl;

    student.setUniversity("FEFU");
    student.setCourse(3);

    superhero.setSuperpower("SpiderSense");
    superhero.setComics("Spiderman");

    employee.setQualification("Manager");

    activist.setAge(35);
    activist.setProject("Mathematics");

    cout << "Student: " << student.getName() << ", Age: " << student.getAge()
        << ", University: " << student.getUniversity() << ", Course: " << student.getCourse() << endl;

    cout << "Superhero: " << superhero.getName() << ", Age: " << superhero.getAge()
        << ", Superpower: " << superhero.getSuperpower() << ", Comics: " << superhero.getComics() << endl;

    cout << "Employee: " << employee.getName() << ", Age: " << employee.getAge()
        << ", Qualification: " << employee.getQualification() << endl;

    cout << "Activist: " << activist.getClubName() << ", Age: " << activist.getAge()
        << ", University: " << activist.getUniversity() << ", Course: " << activist.getCourse()
        << ", Project: " << activist.getProject() << endl;

    return 0;
}
