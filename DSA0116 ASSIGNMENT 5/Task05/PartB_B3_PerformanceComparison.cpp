#include "HospitalBilling.hpp"

#include <array>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <variant>
#include <vector>

using Clock = std::chrono::steady_clock;

struct SwitchBill {
    enum class Kind { OutPatient, InPatient } kind;
    double first;
    double second;
    int days;
    double total() const {
        switch (kind) {
            case Kind::OutPatient: return first + second;
            case Kind::InPatient: return days * first + second;
        }
        return 0;
    }
};

using VariantBill = std::variant<hospital::OutPatientBill, hospital::InPatientBill>;

template <typename Function>
long long measureMs(Function function) {
    const auto start = Clock::now();
    function();
    const auto finish = Clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
}

bool returnCodeValid(double amount) noexcept { return amount >= 0.0 && amount <= 1000000.0; }
void exceptionValidate(double amount) {
    if (amount < 0.0) throw std::invalid_argument("negative");
    if (amount > 1000000.0) throw std::out_of_range("too large");
}

int main() {
    using namespace hospital;
    OutPatientBill op("sample", 500, 1200);
    InPatientBill ip("sample", 3, 2500, 40000);
    std::array<const Bill*, 2> virtualSamples = {&op, &ip};
    std::array<SwitchBill, 2> switchSamples = {{
        {SwitchBill::Kind::OutPatient, 500, 1200, 0},
        {SwitchBill::Kind::InPatient, 2500, 40000, 3}
    }};
    std::array<VariantBill, 2> variantSamples = {
        VariantBill{OutPatientBill("sample", 500, 1200)},
        VariantBill{InPatientBill("sample", 3, 2500, 40000)}
    };

    double smallVirtual = 0, smallSwitch = 0;
    for (int i = 0; i < 10; ++i) {
        smallVirtual += virtualSamples[static_cast<std::size_t>(i % 2)]->total();
        smallSwitch += switchSamples[static_cast<std::size_t>(i % 2)].total();
    }
    std::cout << "10-bill correctness: virtual=" << smallVirtual
              << ", switch=" << smallSwitch << '\n';

    for (int count : {1000, 1000000, 10000000}) {
        double virtualTotal = 0, switchTotal = 0, variantTotal = 0;
        const auto virtualMs = measureMs([&] {
            for (int i = 0; i < count; ++i)
                virtualTotal += virtualSamples[static_cast<std::size_t>(i % 2)]->total();
        });
        const auto switchMs = measureMs([&] {
            for (int i = 0; i < count; ++i)
                switchTotal += switchSamples[static_cast<std::size_t>(i % 2)].total();
        });
        const auto variantMs = measureMs([&] {
            for (int i = 0; i < count; ++i) {
                variantTotal += std::visit([](const auto& bill) { return bill.total(); },
                                           variantSamples[static_cast<std::size_t>(i % 2)]);
            }
        });
        std::cout << count << " bills | virtual=" << virtualMs << " ms | switch="
                  << switchMs << " ms | variant=" << variantMs << " ms"
                  << " | checksum=" << virtualTotal + switchTotal + variantTotal << '\n';
    }

    constexpr int validationCount = 1000000;
    for (int invalidPercent : {0, 1, 50}) {
        std::vector<double> amounts(validationCount, 500.0);
        const int invalidCount = validationCount * invalidPercent / 100;
        for (int i = 0; i < invalidCount; ++i) amounts[static_cast<std::size_t>(i)] = -5.0;
        int acceptedByCode = 0, acceptedByException = 0;
        const auto codeMs = measureMs([&] {
            for (double amount : amounts) acceptedByCode += returnCodeValid(amount) ? 1 : 0;
        });
        const auto exceptionMs = measureMs([&] {
            for (double amount : amounts) {
                try { exceptionValidate(amount); ++acceptedByException; }
                catch (const std::exception&) { }
            }
        });
        std::cout << "Validation invalid=" << invalidPercent << "% | return-code=" << codeMs
                  << " ms | exceptions=" << exceptionMs << " ms | accepted="
                  << acceptedByCode << '/' << acceptedByException << '\n';
    }
}
