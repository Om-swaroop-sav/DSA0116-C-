#ifndef HOSPITAL_BILLING_HPP
#define HOSPITAL_BILLING_HPP

#include <algorithm>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>

namespace hospital {

class BillingError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class ClaimError : public BillingError {
public:
    using BillingError::BillingError;
};

class PackageError : public BillingError {
public:
    using BillingError::BillingError;
};

class Bill {
protected:
    std::string patient;
    explicit Bill(std::string patientName) : patient(std::move(patientName)) {
        if (patient.empty()) throw BillingError("missing patient record");
    }
public:
    virtual ~Bill() noexcept = default;
    virtual double total() const = 0;
    virtual std::string type() const = 0;
    const std::string& patientName() const noexcept { return patient; }
};

class OutPatientBill : public Bill {
    double consultation;
    double tests;
public:
    OutPatientBill(const std::string& p, double consultationFee, double testFee)
        : Bill(p), consultation(consultationFee), tests(testFee) {
        if (consultation < 0 || tests < 0) throw BillingError("negative charge");
    }
    double total() const override { return consultation + tests; }
    std::string type() const override { return "OP"; }
};

class InPatientBill : public Bill {
    int days;
    double perDay;
    double proceduresAndMedicines;
public:
    InPatientBill(const std::string& p, int stayDays, double roomRate, double otherCharges)
        : Bill(p), days(stayDays), perDay(roomRate), proceduresAndMedicines(otherCharges) {
        if (days < 0 || perDay < 0 || proceduresAndMedicines < 0)
            throw BillingError("negative charge");
    }
    double total() const override { return days * perDay + proceduresAndMedicines; }
    std::string type() const override { return "IP"; }
};

class DayCareBill : public Bill {
    double packagePrice;
public:
    DayCareBill(const std::string& p, double price) : Bill(p), packagePrice(price) {
        if (packagePrice < 0) throw BillingError("negative charge");
    }
    double total() const override { return packagePrice; }
    std::string type() const override { return "DAYCARE"; }
};

class EmergencyBill : public Bill {
    double baseCharge;
    int emergencyHours;
    double hourlyCharge;
public:
    EmergencyBill(const std::string& p, double base, int hours, double hourly)
        : Bill(p), baseCharge(base), emergencyHours(hours), hourlyCharge(hourly) {
        if (base < 0 || hours < 0 || hourly < 0) throw BillingError("negative charge");
    }
    double total() const override { return baseCharge + emergencyHours * hourlyCharge; }
    std::string type() const override { return "EMERGENCY"; }
};

class Payer {
public:
    virtual ~Payer() noexcept = default;
    virtual std::string name() const = 0;
    virtual double amountCovered(const Bill& bill) const = 0;
};

class SelfPay : public Payer {
public:
    std::string name() const override { return "SelfPay"; }
    double amountCovered(const Bill& bill) const override { return bill.total(); }
};

class Insurance : public Payer {
    double coverLimit;
    double coPaymentPercent;
public:
    Insurance(double limit, double coPayment)
        : coverLimit(limit), coPaymentPercent(coPayment) {
        if (limit < 0 || coPayment < 0 || coPayment > 100)
            throw ClaimError("invalid insurance policy");
    }
    std::string name() const override { return "Insurance"; }
    double amountCovered(const Bill& bill) const override {
        return std::min(coverLimit, bill.total() * (100.0 - coPaymentPercent) / 100.0);
    }
};

class GovernmentScheme : public Payer {
    std::unordered_map<std::string, double> packageRates;
public:
    GovernmentScheme() : packageRates{{"OP", 1500}, {"IP", 40000},
                                        {"DAYCARE", 25000}, {"EMERGENCY", 12000}} {}
    std::string name() const override { return "GovernmentScheme"; }
    double amountCovered(const Bill& bill) const override {
        const auto found = packageRates.find(bill.type());
        if (found == packageRates.end()) throw PackageError("unknown package code");
        return std::min(bill.total(), found->second);
    }
};

} // namespace hospital
#endif
