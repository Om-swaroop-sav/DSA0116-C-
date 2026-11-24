#include <array>
#include <chrono>
#include <iostream>

class Time {
    int h, m;
public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend inline int minutesBetween(const Time& a, const Time& b);
    friend inline bool earlier(const Time& a, const Time& b);
};

inline int minutesBetween(const Time& a, const Time& b) {
    const int first = a.h * 60 + a.m;
    const int second = b.h * 60 + b.m;
    return (first > second) ? first - second : second - first;
}

inline bool earlier(const Time& a, const Time& b) {
    return a.h * 60 + a.m < b.h * 60 + b.m;
}

#if defined(__GNUC__)
__attribute__((noinline))
#endif
int minutesBetweenNoInline(const Time& a, const Time& b) {
    return minutesBetween(a, b);
}

int main() {
    Time departure(9, 45), arrival(13, 10);
    std::cout << "Complete-the-code output: " << minutesBetween(departure, arrival)
              << ' ' << std::boolalpha << earlier(arrival, departure) << '\n';
    std::cout << "Same time: " << minutesBetween(departure, departure)
              << " | before noon check: " << earlier(Time(11, 50), Time(12, 10)) << '\n';

    std::array<Time, 4> schedule = {Time(8, 10), Time(9, 45), Time(13, 10), Time(18, 5)};
    volatile long long inlineSum = 0;
    volatile long long noInlineSum = 0;
    constexpr int iterations = 10000000;

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < iterations; ++i)
        inlineSum += minutesBetween(schedule[i % 4], schedule[(i + 1) % 4]);
    auto middle = std::chrono::steady_clock::now();
    for (int i = 0; i < iterations; ++i)
        noInlineSum += minutesBetweenNoInline(schedule[i % 4], schedule[(i + 1) % 4]);
    auto finish = std::chrono::steady_clock::now();

    const auto inlineMs = std::chrono::duration_cast<std::chrono::milliseconds>(middle - start).count();
    const auto noInlineMs = std::chrono::duration_cast<std::chrono::milliseconds>(finish - middle).count();
    std::cout << "10,000,000-call timing (ms): inline=" << inlineMs
              << ", noinline=" << noInlineMs << '\n';
    std::cout << "Checksums: " << inlineSum << ' ' << noInlineSum << '\n';
}
