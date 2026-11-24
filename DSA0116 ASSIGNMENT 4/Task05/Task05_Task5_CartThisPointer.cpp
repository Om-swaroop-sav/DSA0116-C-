#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class Cart {
    std::string items[10];
    double prices[10]{};
    int n = 0;
    double discount = 0;
public:
    Cart& add(const std::string& item, double price) {
        if (n < 10 && price >= 0) {
            items[n] = item;
            prices[n] = price;
            ++n;
        }
        return *this;
    }

    Cart& setDiscount(double discount) {
        this->discount = discount;
        if (this->discount < 0) this->discount = 0;
        if (this->discount > 100) this->discount = 100;
        return *this;
    }

    double total() const {
        double sum = 0;
        for (int i = 0; i < n; ++i) sum += prices[i];
        return sum * (100 - discount) / 100;
    }
};

int main() {
    std::cout << std::fixed << std::setprecision(2);

    // (a) direct object use
    Cart direct;
    direct.add("Bread", 40);

    // (b) pointer with ->
    Cart* directPointer = &direct;
    directPointer->add("Milk", 50);

    // (c) reference
    Cart& reference = direct;
    reference.add("Eggs", 60);

    // (d) dynamically allocated object released with delete
    Cart* dynamicCart = new Cart;
    dynamicCart->add("Rice", 60).add("Dal", 120).setDiscount(10);
    std::cout << "Dynamic cart total: " << dynamicCart->total() << '\n';
    delete dynamicCart;

    // Complete-the-code example from the assignment.
    Cart c;
    c.add("Rice", 60).add("Dal", 120).setDiscount(10);
    Cart* p = &c;
    p->add("Oil", 180);
    std::cout << "Expected chained-cart output: " << p->total() << '\n';

    Cart customerA;
    Cart customerB;
    customerA.add("Laptop", 55000).setDiscount(5);
    customerB.add("Phone", 30000).add("Case", 500).setDiscount(2);
    Cart* activeCarts[] = {&customerA, &customerB, &c};
    Cart* highest = activeCarts[0];
    for (Cart* cart : activeCarts) {
        if (cart->total() > highest->total()) highest = cart;
    }
    std::cout << "Highest active cart total: " << highest->total() << '\n';
    std::cout << "Direct/reference cart total: " << reference.total() << '\n';
}
