#include <iostream>
#include <memory>
#include <vector>

class Account {
public:
    double rate() const { return 3.5; } // non-virtual example: compile-time binding
    virtual double virtualRate() const { return 3.5; }
    virtual ~Account() { std::cout << "Account destroyed\n"; }
};

class SeniorAccount : public Account {
    double* history;
public:
    SeniorAccount() : history(new double[100]{}) {}
    double rate() const { return 4.0; }
    double virtualRate() const override { return 4.0; }
    ~SeniorAccount() override {
        delete[] history;
        std::cout << "SeniorAccount history released\n";
    }
};

int main() {
    SeniorAccount senior;
    Account* pointer = &senior;
    Account slicedCopy = senior; // object slicing: only the Account base portion is copied
    std::cout << "Non-virtual rate: " << pointer->rate() << '\n';
    std::cout << "Virtual rate: " << pointer->virtualRate() << '\n';
    std::cout << "Sliced copy virtual rate: " << slicedCopy.virtualRate() << '\n';

    std::vector<std::unique_ptr<Account>> accounts;
    accounts.push_back(std::make_unique<Account>());
    accounts.push_back(std::make_unique<SeniorAccount>());
    for (const auto& account : accounts)
        std::cout << "Account rate: " << account->virtualRate() << '\n';
    std::cout << "Accounts will be released automatically by unique_ptr.\n";
}
