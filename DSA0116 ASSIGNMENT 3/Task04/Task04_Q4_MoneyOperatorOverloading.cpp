#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

class Money {
    long long paise;
public:
    Money(long long rupees = 0, int extraPaise = 0) : paise(rupees * 100 + extraPaise) {}
    explicit Money(long long totalPaise, bool) : paise(totalPaise) {}

    Money operator+(const Money& other) const { return Money(paise + other.paise, true); }
    Money operator-(const Money& other) const { return Money(paise - other.paise, true); }
    Money& operator+=(const Money& other) { paise += other.paise; return *this; }
    bool operator==(const Money& other) const { return paise == other.paise; }
    bool operator<(const Money& other) const { return paise < other.paise; }

    friend std::ostream& operator<<(std::ostream& output, const Money& amount) {
        const long long absolute = amount.paise < 0 ? -amount.paise : amount.paise;
        if (amount.paise < 0) output << "-";
        output << "Rs " << absolute / 100 << '.' << std::setw(2) << std::setfill('0') << absolute % 100;
        output << std::setfill(' ');
        return output;
    }

    friend std::istream& operator>>(std::istream& input, Money& amount) {
        long long rupees = 0;
        int p = 0;
        if (input >> rupees >> p) amount.paise = rupees * 100 + p;
        return input;
    }
};

int main() {
    Money a(120, 75), b(79, 25);
    Money c = a + b;
    std::cout << c << '\n' << std::boolalpha << (c == Money(200)) << '\n';

    Money carry = Money(0, 75) + Money(0, 50);
    std::cout << "Paise carry: " << carry << '\n';
    Money negative = Money(10, 0) - Money(12, 50);
    std::cout << "Negative result: " << negative << '\n';
    a += Money(1, 25);
    std::cout << "After += : " << a << " | a < b: " << (a < b) << '\n';

    std::istringstream input("25 50");
    Money entered;
    input >> entered;
    std::cout << "Stream input (rupees paise): " << entered << '\n';

    constexpr int additions = 1000000;
    Money exactTotal;
    auto exactStart = std::chrono::steady_clock::now();
    for (int i = 0; i < additions; ++i) exactTotal += Money(0, 1);
    auto exactFinish = std::chrono::steady_clock::now();
    double floatingTotal = 0.0;
    auto floatingStart = std::chrono::steady_clock::now();
    for (int i = 0; i < additions; ++i) floatingTotal += 0.01;
    auto floatingFinish = std::chrono::steady_clock::now();
    std::cout << "1,000,000 additions: Money="
              << std::chrono::duration_cast<std::chrono::milliseconds>(exactFinish - exactStart).count()
              << " ms, double="
              << std::chrono::duration_cast<std::chrono::milliseconds>(floatingFinish - floatingStart).count()
              << " ms | exact " << exactTotal << " | double " << floatingTotal << '\n';
}
