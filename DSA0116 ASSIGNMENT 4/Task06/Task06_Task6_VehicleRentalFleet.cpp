#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Vehicle {
    std::string registration;
    double dailyRate;
    bool rented = false;
public:
    Vehicle(std::string reg, double rate) : registration(std::move(reg)), dailyRate(rate) {}
    virtual ~Vehicle() = default;
    virtual std::string type() const = 0;
    double baseDailyRate() const { return dailyRate; }
    virtual double dailyCharge() const { return dailyRate; }
    virtual void printDetails() const {
        std::cout << type() << " " << registration << " | daily charge Rs " << dailyCharge();
    }
    bool rent() {
        if (rented) return false;
        rented = true;
        return true;
    }
    double returnVehicle(int daysUsed, int lateDays) {
        if (!rented) return 0.0;
        rented = false;
        return daysUsed * dailyCharge() + (lateDays > 0 ? lateDays * 50.0 : 0.0);
    }
};

class Bicycle : public Vehicle {
public:
    Bicycle(const std::string& reg, double rate) : Vehicle(reg, rate) {}
    std::string type() const override { return "Bicycle"; }
};

class MotorVehicle : public Vehicle {
    double fuelOrChargeLevel;
    std::string serviceDueDate;
public:
    MotorVehicle(const std::string& reg, double rate, double level, std::string due)
        : Vehicle(reg, rate), fuelOrChargeLevel(level), serviceDueDate(std::move(due)) {}
    void printMotorDetails() const {
        std::cout << " | fuel/charge level " << fuelOrChargeLevel
                  << " | service due " << serviceDueDate;
    }
};

class TwoWheeler : public MotorVehicle {
public:
    TwoWheeler(const std::string& reg, double rate, double fuel, const std::string& due)
        : MotorVehicle(reg, rate, fuel, due) {}
    std::string type() const override { return "Two-wheeler"; }
};

class Car : public MotorVehicle {
    int seats;
public:
    Car(const std::string& reg, double rate, double fuel, const std::string& due, int capacity)
        : MotorVehicle(reg, rate, fuel, due), seats(capacity) {}
    std::string type() const override { return "Car"; }
    void printDetails() const override {
        Vehicle::printDetails();
        std::cout << " | seats " << seats;
        printMotorDetails();
    }
};

class ElectricCar : public Car {
    double batteryCapacityKwh;
    double kwhUsedPerDay;
    double pricePerKwh;
public:
    ElectricCar(const std::string& reg, double rate, double battery, double used,
                double unitPrice, const std::string& due, int seats)
        : Car(reg, rate, battery, due, seats), batteryCapacityKwh(battery),
          kwhUsedPerDay(used), pricePerKwh(unitPrice) {}
    std::string type() const override { return "Electric car"; }
    double dailyCharge() const override { return baseDailyRate() + kwhUsedPerDay * pricePerKwh; }
    void printDetails() const override {
        Vehicle::printDetails();
        std::cout << " | battery " << batteryCapacityKwh << " kWh | charged per kWh";
    }
};

// New vehicle type added without changing Vehicle or the existing derived classes.
class ElectricBus : public MotorVehicle {
    int passengerCapacity;
    double kwhPerDay;
    double ratePerKwh;
public:
    ElectricBus(const std::string& reg, double rate, double battery, const std::string& due,
                int passengers, double consumption, double unitRate)
        : MotorVehicle(reg, rate, battery, due), passengerCapacity(passengers),
          kwhPerDay(consumption), ratePerKwh(unitRate) {}
    std::string type() const override { return "Electric bus"; }
    double dailyCharge() const override { return 1200.0 + kwhPerDay * ratePerKwh; }
    void printDetails() const override {
        Vehicle::printDetails();
        std::cout << " | passenger capacity " << passengerCapacity
                  << " | electric consumption " << kwhPerDay << " kWh/day";
    }
};

int main() {
    std::vector<std::unique_ptr<Vehicle>> fleet;
    fleet.push_back(std::make_unique<Bicycle>("TN01-BI-101", 100));
    fleet.push_back(std::make_unique<TwoWheeler>("TN01-TW-202", 450, 80, "2027-03-01"));
    fleet.push_back(std::make_unique<Car>("TN01-CAR-303", 1500, 60, "2027-04-15", 5));
    fleet.push_back(std::make_unique<ElectricCar>("TN01-EV-404", 1700, 60, 18, 9, "2027-05-20", 5));
    fleet.push_back(std::make_unique<ElectricBus>("TN01-EB-505", 2200, 250, "2027-06-10", 30, 80, 8));

    for (std::size_t i = 0; i < fleet.size(); ++i) {
        fleet[i]->printDetails();
        if (fleet[i]->rent()) {
            const int daysUsed = static_cast<int>(i) + 1;
            const int lateDays = (i == 2) ? 2 : 0;
            std::cout << " | rent accepted | return total Rs "
                      << fleet[i]->returnVehicle(daysUsed, lateDays) << '\n';
        } else {
            std::cout << " | already rented\n";
        }
    }
}
