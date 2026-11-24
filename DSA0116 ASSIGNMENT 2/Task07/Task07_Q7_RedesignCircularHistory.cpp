#include <array>
#include <chrono>
#include <iostream>

class ShiftingHistory {
    static constexpr int CAPACITY = 50;
    std::array<int, CAPACITY> values{};
    int count = 0;
public:
    void add(int value) {
        if (count < CAPACITY) values[count++] = value;
        else {
            for (int i = 1; i < CAPACITY; ++i) values[i - 1] = values[i];
            values[CAPACITY - 1] = value;
        }
    }
    int latest() const { return count == 0 ? -1 : values[count - 1]; }
};

class CircularHistory {
    static constexpr int CAPACITY = 50;
    std::array<int, CAPACITY> values{};
    int next = 0;
    int count = 0;
public:
    void add(int value) {
        values[next] = value;
        next = (next + 1) % CAPACITY;
        if (count < CAPACITY) ++count;
    }
    int latest() const { return count == 0 ? -1 : values[(next + CAPACITY - 1) % CAPACITY]; }
};

int main() {
    constexpr int operations = 2000000;
    ShiftingHistory original;
    CircularHistory redesigned;

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < operations; ++i) original.add(i);
    auto middle = std::chrono::steady_clock::now();
    for (int i = 0; i < operations; ++i) redesigned.add(i);
    auto finish = std::chrono::steady_clock::now();

    const auto originalMs = std::chrono::duration_cast<std::chrono::milliseconds>(middle - start).count();
    const auto redesignedMs = std::chrono::duration_cast<std::chrono::milliseconds>(finish - middle).count();
    std::cout << "Original shifting history latest: " << original.latest() << '\n';
    std::cout << "Redesigned circular history latest: " << redesigned.latest() << '\n';
    std::cout << "Insertions: " << operations << '\n';
    std::cout << "Timing (ms): shifting=" << originalMs << ", circular=" << redesignedMs << '\n';
}
