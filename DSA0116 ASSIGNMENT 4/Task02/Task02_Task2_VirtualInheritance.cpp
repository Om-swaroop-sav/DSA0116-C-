#include <iostream>
#include <string>

class Person {
protected:
    std::string name;
    int id;
    std::string phone;
public:
    Person(std::string personName = "Unknown", int personId = 0, std::string mobile = "N/A")
        : name(std::move(personName)), id(personId), phone(std::move(mobile)) {
        std::cout << "Person ";
    }
    virtual ~Person() = default;
};

class Student : virtual public Person {
protected:
    std::string programme;
    double cgpa;
public:
    Student(std::string n, int i, std::string p, std::string course, double grade)
        : Person(std::move(n), i, std::move(p)), programme(std::move(course)), cgpa(grade) {
        std::cout << "Student ";
    }
};

class Staff : virtual public Person {
protected:
    std::string department;
    double salary;
public:
    Staff(std::string n, int i, std::string p, std::string dept, double pay)
        : Person(std::move(n), i, std::move(p)), department(std::move(dept)), salary(pay) {
        std::cout << "Staff ";
    }
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(std::string n, int i, std::string p, std::string course,
                      double grade, std::string dept, double pay)
        : Person(std::move(n), i, std::move(p)),
          Student(name, id, phone, std::move(course), grade),
          Staff(name, id, phone, std::move(dept), pay) {
        std::cout << "TA\n";
    }
    void print() const {
        std::cout << name << " | " << id << " | " << phone << " | " << programme
                  << " | CGPA " << cgpa << " | " << department << " | salary " << salary << '\n';
    }
};

class ResearchScholar : public Student {
    double fellowship;
public:
    ResearchScholar(std::string n, int i, std::string p, std::string course,
                    double grade, double amount)
        : Person(std::move(n), i, std::move(p)),
          Student(name, id, phone, std::move(course), grade), fellowship(amount) {}
    void print() const {
        std::cout << name << " | programme " << programme << " | fellowship Rs " << fellowship << '\n';
    }
};

int main() {
    TeachingAssistant assistant("Kavya", 192311001, "9876543210", "CSE-AI", 8.7, "CSE", 18000);
    assistant.print();
    ResearchScholar scholar("Arun", 192311002, "9876500000", "AI Research", 9.1, 15000);
    scholar.print();
}
