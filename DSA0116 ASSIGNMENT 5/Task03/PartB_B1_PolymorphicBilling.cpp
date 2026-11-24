#include "HospitalBilling.hpp"

#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

int main() {
    using namespace hospital;
    std::vector<std::unique_ptr<Bill>> bills;
    bills.push_back(std::make_unique<OutPatientBill>("Ravi", 500, 1200));
    bills.push_back(std::make_unique<InPatientBill>("Meena", 3, 2500, 40000));
    bills.push_back(std::make_unique<DayCareBill>("Asha", 22000));
    bills.push_back(std::make_unique<EmergencyBill>("Bala", 2000, 3, 1500));

    SelfPay selfPay;
    Insurance insurance(50000, 10);
    GovernmentScheme government;
    std::vector<const Payer*> payers = {&selfPay, &insurance, &government};

    std::cout << std::fixed << std::setprecision(2);
    double billedTotal = 0;
    for (const auto& bill : bills) {
        billedTotal += bill->total();
        std::cout << bill->type() << ' ' << bill->patientName()
                  << " | bill Rs " << bill->total() << '\n';
        for (const Payer* payer : payers) {
            std::cout << "  " << payer->name() << " covers Rs "
                      << payer->amountCovered(*bill) << '\n';
        }
    }
    std::cout << "Hospital billed total: Rs " << billedTotal << '\n';
}
