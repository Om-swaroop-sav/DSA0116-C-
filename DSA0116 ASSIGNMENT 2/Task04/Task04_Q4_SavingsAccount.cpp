#include <iomanip>
#include <iostream>
#include <string>

class SavingsAccount {
    struct Transaction {
        std::string description;
        double amount;
        double balanceAfter;
    };

    long long accountNumber;
    double balance;
    Transaction transactions[10];
    int count;

    void record(const std::string& description, double amount) {
        if (count == 10) {
            for (int i = 1; i < 10; ++i) transactions[i - 1] = transactions[i];
            --count;
        }
        transactions[count++] = {description, amount, balance};
    }

public:
    SavingsAccount(long long number, double openingBalance)
        : accountNumber(number), balance(openingBalance), count(0) {
        record("Opening balance", openingBalance);
    }

    void deposit(double amount) {
        if (amount <= 0) return;
        balance += amount;
        record("Deposit", amount);
    }

    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance) return false;
        balance -= amount;
        record("Withdrawal", -amount);
        return true;
    }

    void miniStatement() const {
        std::cout << "Mini-statement for account " << accountNumber << '\n';
        for (int i = 0; i < count; ++i) {
            std::cout << std::left << std::setw(18) << transactions[i].description
                      << " amount=" << std::right << std::setw(8) << transactions[i].amount
                      << " balance=" << transactions[i].balanceAfter << '\n';
        }
        std::cout << "Current balance: " << balance << '\n';
    }
};

int main() {
    std::cout << std::fixed << std::setprecision(2);
    SavingsAccount account(202611001, 5000.00);
    account.deposit(750);
    account.withdraw(300);
    for (int i = 1; i <= 10; ++i) account.deposit(i * 10.0); // oldest entries are discarded
    account.miniStatement();
}
