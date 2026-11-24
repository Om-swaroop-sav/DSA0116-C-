#include <iostream>
#include <array>
using namespace std;

enum class Zone { Inner, Middle, Outer };
constexpr array<long long, 3> FARES = {1000, 2000, 3000};
constexpr long long MIN_BALANCE = 5000;

long long baseFare(Zone z) {
    return FARES.at(static_cast<size_t>(z));
}

int main() {
    cout << "Recommended design:\n";
    cout << "- Store money as integer paise using long long.\n";
    cout << "- Keep SmartCard balance private.\n";
    cout << "- Keep fare values in one table of constants.\n";
    cout << "- Validate zone, time and minimum remaining balance.\n";
    cout << "- For a fare revision, update the fare table in one place.\n";
    cout << "Example Outer base fare: " << baseFare(Zone::Outer) << " paise\n";
    cout << "Minimum remaining balance: " << MIN_BALANCE << " paise\n";
    cout << "Each fare lookup and balance check is O(1).\n";
}
