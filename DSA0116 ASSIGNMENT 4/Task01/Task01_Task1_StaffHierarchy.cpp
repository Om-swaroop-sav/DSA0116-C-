#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Staff {
    std::string name;
    int id;
    double basicPay;
protected:
    double allowanceRate = 0.42;
    const std::string& staffName() const { return name; }
    double basic() const { return basicPay; }
    double basicWithAllowance() const { return basicPay * (1.0 + allowanceRate); }
public:
    Staff(std::string staffName, int staffId, double basic)
        : name(std::move(staffName)), id(staffId), basicPay(basic) {}
    virtual ~Staff() = default;
    virtual double pay() const = 0;
    virtual const char* category() const = 0;
    void print() const {
        std::cout << category() << " | " << name << " | ID " << id << " | Pay Rs " << pay() << '\n';
    }
};

class Professor : public Staff {
    double researchAllowance;
public:
    Professor(std::string name, int id, double basic, double research)
        : Staff(std::move(name), id, basic), researchAllowance(research) {}
    double pay() const override { return basicWithAllowance() + researchAllowance; }
    const char* category() const override { return "Professor"; }
};

class LabAssistant : public Staff {
public:
    LabAssistant(std::string name, int id, double basic)
        : Staff(std::move(name), id, basic) {}
    double pay() const override { return basicWithAllowance(); }
    const char* category() const override { return "Lab Assistant"; }
};

class GuestFaculty : public Staff {
    double hours;
    double rate;
public:
    GuestFaculty(std::string name, int id, double workedHours, double hourlyRate)
        : Staff(std::move(name), id, 0), hours(workedHours), rate(hourlyRate) {}
    double pay() const override { return hours * rate; }
    const char* category() const override { return "Guest Faculty"; }
};

int main() {
    std::vector<std::unique_ptr<Staff>> payroll;
    payroll.push_back(std::make_unique<Professor>("Anita", 101, 60000, 5000));
    payroll.push_back(std::make_unique<LabAssistant>("Ramesh", 102, 30000));
    payroll.push_back(std::make_unique<GuestFaculty>("Meera", 103, 24, 900));

    double totalPayroll = 0;
    for (const auto& person : payroll) {
        person->print();
        totalPayroll += person->pay();
    }
    std::cout << "Total payroll: Rs " << totalPayroll << '\n';
}
