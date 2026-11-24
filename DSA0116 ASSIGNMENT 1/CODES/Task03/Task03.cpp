#include <iostream>
#include <climits>
#include <limits>
using namespace std;

int main() {
    cout << "Type sizes on this compiler (bytes)\n";
    cout << "bool: " << sizeof(bool) << '\n';
    cout << "char: " << sizeof(char) << '\n';
    cout << "int: " << sizeof(int) << '\n';
    cout << "long long: " << sizeof(long long) << '\n';
    cout << "float: " << sizeof(float) << '\n';
    cout << "double: " << sizeof(double) << '\n';
    cout << "INT_MAX: " << INT_MAX << '\n';
    cout << "LLONG_MAX: " << LLONG_MAX << '\n';

    long long threeMillionOuterFares = 3000000LL * 3000LL; // paise, before surcharge
    cout << "3,000,000 Outer fares in paise: " << threeMillionOuterFares << '\n';
    cout << "Equivalent rupees: Rs " << threeMillionOuterFares / 100 << '\n';
    cout << "Use integer paise to avoid floating-point currency rounding.\n";
}
