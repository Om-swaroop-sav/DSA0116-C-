#include <iostream>
using namespace std;

class SmartCard {
private:
    long long balance;
public:
    explicit SmartCard(long long initial) : balance(initial) {}
    bool canTravel(long long fare) const { return fare >= 0 && balance - fare >= 5000; }
    bool deduct(long long fare) {
        if (!canTravel(fare)) return false;
        balance -= fare;
        return true;
    }
    long long getBalance() const { return balance; }
};

int main() {
    SmartCard card(10000);
    if (card.deduct(3000)) cout << "OOP: journey approved\n";
    else cout << "OOP: journey denied\n";
    cout << "Balance: Rs " << card.getBalance() / 100 << '\n';
}
