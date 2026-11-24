#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

int main() {
    int zone;
    cout << "Enter zone (1=Inner, 2=Middle, 3=Outer): ";
    if (!(cin >> zone)) {
        cout << "Invalid input: zone must be a number.\n";
        return 1;
    }

    int hour;
    cout << "Enter hour (0-23): ";
    if (!(cin >> hour)) {
        cout << "Invalid input: hour must be a number.\n";
        return 1;
    }

    if (zone < 1 || zone > 3 || hour < 0 || hour > 23) {
        cout << "Invalid zone or hour.\n";
        return 1;
    }

    const long long fares[] = {1000, 2000, 3000};
    long long fare = fares[zone - 1];
    bool peak = (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    if (peak) fare += fare * 20 / 100;

    cout << fixed << setprecision(2);
    cout << "Peak hour: " << boolalpha << peak << '\n';
    cout << "Fare: Rs " << static_cast<double>(fare) / 100.0 << '\n';
}
