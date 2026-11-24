#include <iostream>
#include <array>
#include <string>
using namespace std;

enum class Zone { Inner, Middle, Outer, Airport };
constexpr array<long long, 4> FARES = {1000, 2000, 3000, 6000};
constexpr long long MIN_BALANCE = 5000;

class Pass {
private:
    bool active;
    bool allowed[4];
public:
    Pass(bool enabled, int firstZone, int secondZone) : active(enabled), allowed{false, false, false, false} {
        if (firstZone >= 0 && firstZone < 4) allowed[firstZone] = true;
        if (secondZone >= 0 && secondZone < 4) allowed[secondZone] = true;
    }
    bool covers(int zone) const {
        return active && zone >= 0 && zone < 4 && allowed[zone];
    }
};

long long calculateFare(int zone, bool peak, bool weekend) {
    if (zone < 0 || zone >= 4) return -1;
    long long fare = FARES[zone];
    if (weekend) {
        fare -= fare * 10 / 100; // Weekend discount replaces peak surcharge
    } else if (peak) {
        fare += fare * 20 / 100;
    }
    return fare;
}

int main() {
    // Example: zone indexes 0=Inner, 1=Middle, 2=Outer, 3=Airport.
    Pass monthlyPass(true, 0, 2); // Unlimited travel in Inner and Outer.
    int zone = 3;                 // Airport
    bool peak = true, weekend = false;
    long long fare = calculateFare(zone, peak, weekend);
    cout << "Airport peak fare: Rs " << fare / 100 << '.'
         << (fare % 100 < 10 ? "0" : "") << fare % 100 << '\n';

    int selectedZone = 2;
    if (monthlyPass.covers(selectedZone))
        cout << "Monthly pass covers Outer zone: no fare charged.\n";
    else
        cout << "Monthly pass does not cover selected zone.\n";

    long long weekendFare = calculateFare(3, true, true);
    cout << "Airport weekend fare (no peak surcharge): Rs "
         << weekendFare / 100 << '.' << (weekendFare % 100 < 10 ? "0" : "")
         << weekendFare % 100 << '\n';
    cout << "Minimum balance rule: Rs " << MIN_BALANCE / 100 << '\n';
}
