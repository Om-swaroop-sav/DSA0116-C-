#include <iostream>

void applyByValue(long long fee, int percent) {
    fee -= fee * percent / 100;
}

void applyByReference(long long& fee, int percent) {
    fee -= fee * percent / 100;
}

void applyByPointer(long long* fee, int percent) {
    if (fee != nullptr) {
        *fee -= *fee * percent / 100;
    }
}

void change(int a, int& b, int* c) {
    a += 10;
    b += 10;
    *c += 10;
}

int& bigger(int& p, int& q) {
    return (p > q) ? p : q;
}

void show(int x, int y = 5, int z = 10) {
    std::cout << x + y + z << ' ';
}

int main() {
    std::cout << "Hostel fee examples\n";
    long long valueFee = 45000;
    long long referenceFee = 45000;
    long long pointerFee = 45000;

    applyByValue(valueFee, 10);
    applyByReference(referenceFee, 10);
    applyByPointer(&pointerFee, 10);

    std::cout << "by value    : " << valueFee << '\n';
    std::cout << "by reference: " << referenceFee << '\n';
    std::cout << "by pointer  : " << pointerFee << "\n\n";

    std::cout << "Complete-the-code example\n";
    long long hostelFee = 45000;
    applyByValue(hostelFee, 10);
    std::cout << "after call by value   : " << hostelFee << '\n';
    applyByReference(hostelFee, 10);
    std::cout << "after call by reference: " << hostelFee << "\n\n";

    std::cout << "Predict-the-output example\n";
    int a = 1, b = 2, c = 3;
    change(a, b, &c);
    std::cout << a << ' ' << b << ' ' << c << '\n';
    bigger(a, c) = 100;
    std::cout << a << ' ' << c << '\n';
    show(1);
    show(1, 2);
    show(1, 2, 3);
    std::cout << '\n';
}
