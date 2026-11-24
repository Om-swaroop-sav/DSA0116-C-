#include <iostream>
#include <string>
#include <utility>

class Address {
    std::string city;
    int pin;
public:
    Address(std::string place = "Unknown", int postal = 0)
        : city(std::move(place)), pin(postal) { std::cout << "Address+ "; }
    ~Address() { std::cout << "Address- "; }
    std::string str() const { return city + "-" + std::to_string(pin); }
};

class Course {
    std::string title;
public:
    explicit Course(std::string name) : title(std::move(name)) { std::cout << "Course+ "; }
    ~Course() { std::cout << "Course- "; }
};

class Person {
protected:
    std::string name;
    int age;
    Address home;
public:
    Person(const std::string& n, int a, const std::string& city, int pin)
        : name(n), age(a), home(city, pin) { std::cout << "Person+ "; }
    virtual ~Person() { std::cout << "Person- "; }
};

class Student : virtual public Person {
    long long regNo;
    Course course;
public:
    Student(const std::string& n, int a, const std::string& city, int pin,
            long long registration, const std::string& courseName)
        : Person(n, a, city, pin), regNo(registration), course(courseName) {
        std::cout << "Student+ ";
    }
    ~Student() override { std::cout << "Student- "; }
    void print() const {
        std::cout << "\n" << regNo << ' ' << name << " (" << age << ") " << home.str() << '\n';
    }
};

class Staff : virtual public Person {
    std::string department;
public:
    Staff(const std::string& n, int a, const std::string& city, int pin, std::string dept)
        : Person(n, a, city, pin), department(std::move(dept)) { std::cout << "Staff+ "; }
    ~Staff() override { std::cout << "Staff- "; }
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(const std::string& n, int a, const std::string& city, int pin,
                      long long reg, const std::string& courseName, std::string dept)
        : Person(n, a, city, pin),
          Student(n, a, city, pin, reg, courseName),
          Staff(n, a, city, pin, std::move(dept)) { std::cout << "TA+ "; }
    ~TeachingAssistant() override { std::cout << "TA- "; }
};


class CompleteAddress {
    std::string city;
    int pin;
public:
    CompleteAddress(const std::string& place, int postal) : city(place), pin(postal) {}
    std::string str() const { return city + "-" + std::to_string(pin); }
};

class CompletePerson {
protected:
    std::string name;
    int age;
public:
    CompletePerson(const std::string& n, int a) : name(n), age(a) {}
};

class CompleteStudent : public CompletePerson {
    long long regNo;
    CompleteAddress home;
public:
    CompleteStudent(const std::string& n, int a, long long registration,
                    const std::string& city, int pin)
        : CompletePerson(n, a), regNo(registration), home(city, pin) {}
    void print() const {
        std::cout << regNo << ' ' << name << " (" << age << ") " << home.str() << '\n';
    }
};

struct Engine { Engine() { std::cout << "Engine "; } ~Engine() { std::cout << "~Engine "; } };
struct VehicleBase { VehicleBase() { std::cout << "Vehicle "; } ~VehicleBase() { std::cout << "~Vehicle "; } };
struct Car : VehicleBase {
    Engine engine;
    Car() { std::cout << "Car "; }
    ~Car() { std::cout << "~Car "; }
};

int main() {
    std::cout << "Car construction/destruction order: ";
    {
        Car car;
        std::cout << "| ";
    }
    std::cout << "\n\nComplete-the-code output: ";
    CompleteStudent completeStudent("Kavya", 19, 192311001, "Salem", 636001);
    completeStudent.print();
    std::cout << "Student member-class demonstration:\n";
    {
        Student student("Kavya", 19, "Salem", 636001, 192311001, "C++ OOP");
        student.print();
    }
    std::cout << "\nTeaching assistant virtual-base construction order:\n";
    {
        TeachingAssistant assistant("Ravi", 20, "Chennai", 600001, 192311010, "AI", "CSE");
        std::cout << "\nLeaving scope\n";
    }
}
