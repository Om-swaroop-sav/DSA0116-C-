#include <iostream>
using namespace std;

enum class Zone { Inner = 1, Middle, Outer };
constexpr long long INNER_FARE_PAISE = 1000;
constexpr long long MIDDLE_FARE_PAISE = 2000;
constexpr long long OUTER_FARE_PAISE = 3000;
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr long long MIN_BALANCE_PAISE = 5000;

int main() {
    Zone zone = Zone::Outer;
    long long fare = 0;
    switch (zone) {
        case Zone::Inner: fare = INNER_FARE_PAISE; break;
        case Zone::Middle: fare = MIDDLE_FARE_PAISE; break;
        case Zone::Outer: fare = OUTER_FARE_PAISE; break;
    }
    bool peak = true;
    if (peak) fare += fare * PEAK_SURCHARGE_PERCENT / 100;
    cout << "Outer zone peak fare: Rs " << fare / 100 << '.' << (fare % 100 < 10 ? "0" : "") << fare % 100 << '\n';
    cout << "Minimum balance in paise: " << MIN_BALANCE_PAISE << '\n';
}
