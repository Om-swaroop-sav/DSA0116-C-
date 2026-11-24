#include <iomanip>
#include <iostream>

struct Parcel {
    double weightKg;
    bool express;
    bool insured;
};

double charge(int weightGrams, bool express = false, bool insured = false) {
    const double base = 40.0 + 0.08 * weightGrams;
    return base + (express ? 50.0 : 0.0) + (insured ? 20.0 : 0.0);
}

double charge(double weightKg, bool express = false, bool insured = false) {
    const double base = 40.0 + 80.0 * weightKg;
    return base + (express ? 50.0 : 0.0) + (insured ? 20.0 : 0.0);
}

double charge(const Parcel& parcel) {
    return charge(parcel.weightKg, parcel.express, parcel.insured);
}

int main() {
    std::cout << std::fixed << std::setprecision(2);
    Parcel parcel{2.5, true, false};

    // Six calls; overload choice is determined by the argument type.
    std::cout << "charge(2)       [int grams] : " << charge(2) << '\n';
    std::cout << "charge(2.0f)    [float promotes to double kg] : " << charge(2.0f) << '\n';
    std::cout << "charge(2.0)     [double kg] : " << charge(2.0) << '\n';
    std::cout << "charge(2500)    [int grams, express] : " << charge(2500, true) << '\n';
    std::cout << "charge(1.5, false, true) [double kg] : " << charge(1.5, false, true) << '\n';
    std::cout << "charge(parcel)  [Parcel] : " << charge(parcel) << '\n';
}
