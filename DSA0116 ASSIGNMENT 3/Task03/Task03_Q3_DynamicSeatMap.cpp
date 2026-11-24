#include <iostream>
#include <string>
#include <utility>

class AuditoriumEvent {
    std::string eventName;
    int rows;
    int seatsPerRow;
    char** seats;
    int booked;
public:
    AuditoriumEvent(const std::string& name, int rowCount, int seatCount)
        : eventName(name), rows(rowCount > 0 ? rowCount : 0),
          seatsPerRow(seatCount > 0 ? seatCount : 0), seats(nullptr), booked(0) {
        if (rows > 0 && seatsPerRow > 0) {
            seats = new char*[rows]{};
            try {
                for (int r = 0; r < rows; ++r) {
                    seats[r] = new char[seatsPerRow];
                    for (int s = 0; s < seatsPerRow; ++s) seats[r][s] = 'O';
                }
            } catch (...) {
                for (int r = 0; r < rows; ++r) delete[] seats[r];
                delete[] seats;
                seats = nullptr;
                throw;
            }
        }
        std::cout << "Created event: " << eventName << '\n';
    }

    AuditoriumEvent(const AuditoriumEvent&) = delete;
    AuditoriumEvent& operator=(const AuditoriumEvent&) = delete;

    ~AuditoriumEvent() {
        for (int r = 0; r < rows; ++r) delete[] seats[r];
        delete[] seats;
        std::cout << "Closed event: " << eventName << " | seats booked: " << booked << '\n';
    }

    bool book(int row, int seat) {
        if (!valid(row, seat) || seats[row][seat] == 'X') return false;
        seats[row][seat] = 'X';
        ++booked;
        return true;
    }

    bool cancel(int row, int seat) {
        if (!valid(row, seat) || seats[row][seat] == 'O') return false;
        seats[row][seat] = 'O';
        --booked;
        return true;
    }

    void printMap() const {
        std::cout << eventName << " seat map:\n";
        for (int r = 0; r < rows; ++r) {
            for (int s = 0; s < seatsPerRow; ++s) std::cout << seats[r][s] << ' ';
            std::cout << '\n';
        }
    }
private:
    bool valid(int row, int seat) const {
        return seats != nullptr && row >= 0 && row < rows && seat >= 0 && seat < seatsPerRow;
    }
};

struct Logger {
    std::string name;
    explicit Logger(const std::string& value) : name(value) { std::cout << '+' << name << ' '; }
    Logger(const Logger& other) : name(other.name + "c") { std::cout << "copy" << name << ' '; }
    ~Logger() { std::cout << '-' << name << ' '; }
};
void use(Logger) { std::cout << "use "; }

int main() {
    {
        AuditoriumEvent stackEvent("College Fest", 2, 3);
        stackEvent.book(0, 0);
        stackEvent.book(1, 2);
        stackEvent.cancel(0, 0);
        stackEvent.printMap();
    }
    {
        AuditoriumEvent zeroRows("Online Event", 0, 20);
        zeroRows.printMap();
    }
    AuditoriumEvent* heapEvent = new AuditoriumEvent("Workshop", 1, 2);
    heapEvent->book(0, 1);
    delete heapEvent;

    for (const auto& dimensions : {std::pair<int, int>{10, 20}, {100, 200}, {1000, 2000}}) {
        AuditoriumEvent measured("Memory test", dimensions.first, dimensions.second);
        const std::size_t approximateBytes = static_cast<std::size_t>(dimensions.first) *
            static_cast<std::size_t>(dimensions.second) +
            static_cast<std::size_t>(dimensions.first) * sizeof(char*);
        std::cout << "Approximate seat-map bytes for " << dimensions.first << 'x'
                  << dimensions.second << ": " << approximateBytes << '\n';
    }

    // Predict-the-output program supplied in the assignment.
    Logger a("A");
    {
        Logger b("B");
    }
    use(a);
    Logger* p = new Logger("P");
    delete p;
    std::cout << "end\n";
}
