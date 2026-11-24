#include <chrono>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

class Prescription {
    int n;
    std::string* medicines;
    inline static int copyCount = 0;
public:
    explicit Prescription(int count)
        : n(count < 0 ? 0 : count), medicines(n == 0 ? nullptr : new std::string[n]) {}

    Prescription(const Prescription& other)
        : n(other.n), medicines(n == 0 ? nullptr : new std::string[n]) {
        for (int i = 0; i < n; ++i) medicines[i] = other.medicines[i];
        ++copyCount;
        std::cout << "[deep copy] ";
    }

    Prescription& operator=(const Prescription& other) {
        if (this != &other) {
            std::string* newMedicines = other.n == 0 ? nullptr : new std::string[other.n];
            for (int i = 0; i < other.n; ++i) newMedicines[i] = other.medicines[i];
            delete[] medicines;
            medicines = newMedicines;
            n = other.n;
            ++copyCount;
        }
        return *this;
    }

    ~Prescription() { delete[] medicines; }

    void set(int i, const std::string& medicine) {
        if (i < 0 || i >= n) throw std::out_of_range("medicine index out of range");
        medicines[i] = medicine;
    }

    std::string get(int i) const {
        if (i < 0 || i >= n) throw std::out_of_range("medicine index out of range");
        return medicines[i];
    }

    int size() const { return n; }
    static int copiesMade() { return copyCount; }
};

void inspectByValue(Prescription prescription) {
    if (prescription.size() > 0) std::cout << "value parameter: " << prescription.get(0) << '\n';
}

void inspectByConstReference(const Prescription& prescription) {
    if (prescription.size() > 0) std::cout << "const reference parameter: " << prescription.get(0) << '\n';
}

int main() {
    Prescription p(2);
    p.set(0, "Paracetamol");
    p.set(1, "ORS");

    Prescription q = p;
    q.set(1, "Cetirizine");
    Prescription r(1);
    r = p;
    p.set(0, "Ibuprofen");
    std::cout << p.get(0) << ' ' << p.get(1) << " | "
              << q.get(0) << ' ' << q.get(1) << " | "
              << r.get(0) << ' ' << r.get(1) << '\n';

    inspectByValue(p);
    inspectByConstReference(p);
    r = r; // self-assignment is safely ignored
    std::cout << "Deep-copy operations counted: " << Prescription::copiesMade() << '\n';

    for (int medicineCount : {10, 1000, 100000}) {
        Prescription large(medicineCount);
        for (int i = 0; i < medicineCount; ++i)
            large.set(i, "Medicine-" + std::to_string(i));
        auto start = std::chrono::steady_clock::now();
        Prescription largeCopy = large;
        auto finish = std::chrono::steady_clock::now();
        std::cout << "Copied " << largeCopy.size() << " medicines in "
                  << std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count()
                  << " microseconds\n";
    }
}
