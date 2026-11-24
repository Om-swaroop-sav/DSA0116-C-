#include <iostream>
using namespace std;

long long balance = 10000; // paise: procedural example
bool canTravel(long long fare) { return fare >= 0 && balance - fare >= 5000; }
void deductFare(long long fare) {
    if (canTravel(fare)) balance -= fare;
}
int main() {
    long long fare = 3000;
    if (canTravel(fare)) {
        deductFare(fare);
        cout << "Procedural: journey approved\n";
    } else {
        cout << "Procedural: journey denied\n";
    }
    cout << "Balance: Rs " << balance / 100 << '\n';
}
