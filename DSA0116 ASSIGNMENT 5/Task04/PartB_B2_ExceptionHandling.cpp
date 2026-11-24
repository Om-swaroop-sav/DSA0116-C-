#include "HospitalBilling.hpp"

#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>
#include <string>
#include <vector>

class ResourceGuard {
    std::string label;
public:
    explicit ResourceGuard(std::string name) : label(std::move(name)) {
        std::cout << "acquired " << label << '\n';
    }
    ~ResourceGuard() noexcept { std::cout << "released " << label << '\n'; }
};

void validateTextNumber(const std::string& text) {
    std::size_t used = 0;
    const double parsed = std::stod(text, &used);
    if (used != text.size()) throw std::invalid_argument("text is not a complete number");
    if (parsed < 0) throw hospital::BillingError("negative charge");
}

void runErrorScenario() {
    using namespace hospital;
    ResourceGuard guard("temporary billing resource");
    try {
        validateTextNumber("not-a-number");
    } catch (const std::invalid_argument& error) {
        std::cout << "logged conversion error: " << error.what() << '\n';
        throw;
    }
}

int main() {
    using namespace hospital;
    // Negative charge.
    try { OutPatientBill invalid("Patient-A", -10, 20); }
    catch (const std::exception& error) { std::cout << "negative charge: " << error.what() << '\n'; }

    // Missing patient record.
    try { OutPatientBill missing("", 10, 20); }
    catch (const std::exception& error) { std::cout << "missing patient: " << error.what() << '\n'; }

    // Claim above cover, logged and rethrown.
    try {
        Insurance policy(50000, 10);
        OutPatientBill bill("Patient-B", 60000, 0);
        if (bill.total() > 50000) throw ClaimError("claim exceeds cover");
        (void)policy.amountCovered(bill);
    } catch (const ClaimError& error) {
        std::cout << "claim rejected: " << error.what() << '\n';
    }

    // Unknown government package.
    class UnknownBill : public Bill {
    public:
        UnknownBill() : Bill("Patient-C") {}
        double total() const override { return 100; }
        std::string type() const override { return "UNKNOWN"; }
    } unknown;
    try { GovernmentScheme scheme; (void)scheme.amountCovered(unknown); }
    catch (const PackageError& error) { std::cout << "package error: " << error.what() << '\n'; }

    // std::stod throws invalid_argument for text where a number is expected.
    try { validateTextNumber("abc"); }
    catch (const std::invalid_argument& error) { std::cout << "conversion error: " << error.what() << '\n'; }

    // An impossible array length is rejected and caught as a bad_alloc-derived exception.
    try {
        volatile std::size_t requested = std::numeric_limits<std::size_t>::max();
        const std::size_t impossible = requested;
        int* memory = new int[impossible]; // runtime-sized impossible request
        delete[] memory;
    } catch (const std::bad_alloc& error) {
        std::cout << "allocation failure caught: " << error.what() << '\n';
    }

    try { runErrorScenario(); }
    catch (...) { std::cout << "top-level catch(...) recovered; execution continues\n"; }
    std::cout << "Program remains active after handled errors.\n";
}
