#include <iostream>
#include <vector>
#include <string>
using namespace std;

constexpr long long MIN_BALANCE = 5000;
long long calculateFare(int zone, int hour) {
    const long long fares[] = {1000, 2000, 3000};
    if (zone < 1 || zone > 3 || hour < 0 || hour > 23) return -1;
    long long fare = fares[zone - 1];
    bool peak = (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    if (peak) fare += fare * 20 / 100;
    return fare;
}
int main() {
    struct Test { int zone, hour; long long balance; string label; };
    vector<Test> tests = {
        {1, 7, 10000, "Inner off-peak"},
        {2, 9, 10000, "Middle peak"},
        {3, 18, 10000, "Outer peak"},
        {3, 10, 10000, "10 AM boundary"},
        {3, 20, 10000, "8 PM boundary"},
        {2, 12, 7000, "Exactly Rs 50 remains"},
        {3, 12, 7000, "Insufficient balance"},
        {4, 12, 10000, "Invalid zone"}
    };

    for (const auto& t : tests) {
        long long fare = calculateFare(t.zone, t.hour);
        bool allowed = fare >= 0 && t.balance - fare >= MIN_BALANCE;
        cout << t.label << ": ";
        if (fare < 0) cout << "INVALID INPUT";
        else if (allowed) cout << "PASS - fare " << fare << " paise";
        else cout << "DENIED - minimum balance rule";
        cout << '\n';
    }
}
