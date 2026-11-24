#include <iostream>
#include <iomanip>
#include <climits>
using namespace std;

int main() {
    const long long journeys[] = {20000LL, 500000LL, 3000000LL};
    const long long farePaise = 3000; // Rs 30 per journey
    const double fareRupees = 30.0;

    for (long long n : journeys) {
        long long exactPaise = n * farePaise;
        double doubleTotal = n * fareRupees;
        cout << "Journeys: " << n << '\n';
        cout << "long long total: Rs " << exactPaise / 100 << '\n';
        cout << fixed << setprecision(2);
        cout << "double total: Rs " << doubleTotal << '\n';
        cout << "Fits in int paise: " << boolalpha
             << (exactPaise <= INT_MAX) << "\n\n";
    }
    cout << "Integer paise gives exact currency arithmetic; long long supports these totals.\n";
}
