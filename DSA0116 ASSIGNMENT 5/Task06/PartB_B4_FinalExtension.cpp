#include "HospitalBilling.hpp"

#include <iostream>
#include <memory>
#include <vector>

// Added bill type: existing Bill and bill classes remain unchanged.
class AmbulanceBill : public hospital::Bill {
    double distanceKm;
    double chargePerKm;
    double emergencySupport;
public:
    AmbulanceBill(const std::string& patient, double km, double rate, double support)
        : Bill(patient), distanceKm(km), chargePerKm(rate), emergencySupport(support) {
        if (km < 0 || rate < 0 || support < 0) throw hospital::BillingError("negative charge");
    }
    double total() const override { return distanceKm * chargePerKm + emergencySupport; }
    std::string type() const override { return "AMBULANCE"; }
};

// Added payer type: existing Payer implementations remain unchanged.
class CorporatePayer : public hospital::Payer {
    double discountPercent;
public:
    explicit CorporatePayer(double discount) : discountPercent(discount) {
        if (discount < 0 || discount > 100) throw hospital::ClaimError("invalid corporate discount");
    }
    std::string name() const override { return "CorporateTieUp"; }
    double amountCovered(const hospital::Bill& bill) const override {
        return bill.total() * (100.0 - discountPercent) / 100.0;
    }
};

int main() {
    using namespace hospital;
    std::vector<std::unique_ptr<Bill>> bills;
    bills.push_back(std::make_unique<OutPatientBill>("Ravi", 500, 1200));
    bills.push_back(std::make_unique<InPatientBill>("Meena", 3, 2500, 40000));
    bills.push_back(std::make_unique<AmbulanceBill>("Asha", 18, 35, 500));

    CorporatePayer corporate(12.5);
    SelfPay self;
    double total = 0;
    for (const auto& bill : bills) {
        total += bill->total();
        std::cout << bill->type() << ' ' << bill->patientName() << " total=" << bill->total()
                  << " | self=" << self.amountCovered(*bill)
                  << " | corporate=" << corporate.amountCovered(*bill) << '\n';
    }
    std::cout << "Total bill amount: " << total << '\n';

    // Exception path runs while RAII-owned bill objects are alive.
    try {
        OutPatientBill bad("Test", -1, 10);
        (void)bad;
    } catch (const BillingError& error) {
        std::cout << "Caught expected billing exception: " << error.what() << '\n';
    }
}
