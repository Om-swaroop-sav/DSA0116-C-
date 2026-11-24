#include <iostream>
#include <string>
using namespace std;

class Passenger {
public:
    int id;
    string name, category;
    void display() const {
        cout << "Passenger: " << name << " (ID " << id << "), " << category << '\n';
    }
};

class SmartCard {
private:
    long long balance; // paise
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

class FareTable {
public:
    long long calculate(int zone, bool peak) const {
        const long long fares[] = {1000, 2000, 3000};
        if (zone < 1 || zone > 3) return -1;
        long long fare = fares[zone - 1];
        if (peak) fare += fare * 20 / 100;
        return fare;
    }
};

int main() {
    Passenger p{101, "Sample Passenger", "Regular"};
    SmartCard card(10000);
    FareTable table;
    int zone = 3, hour = 18; // demonstration: Outer zone, 6 PM
    bool peak = (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    long long fare = table.calculate(zone, peak);
    p.display();
    cout << "Fare: Rs " << fare / 100 << '.' << (fare % 100 < 10 ? "0" : "") << fare % 100 << '\n';
    cout << (card.deduct(fare) ? "Journey approved\n" : "Journey denied\n");
    cout << "Balance: Rs " << card.getBalance() / 100 << '\n';
}
