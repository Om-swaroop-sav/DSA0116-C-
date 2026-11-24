#include <chrono>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Time {
    int totalSeconds;
public:
    Time(int hours = 0, int minutes = 0, int seconds = 0)
        : totalSeconds(hours * 3600 + minutes * 60 + seconds) {}

    Time& operator++() { ++totalSeconds; return *this; }
    Time operator++(int) { Time old = *this; ++totalSeconds; return old; }
    bool operator==(const Time& other) const { return totalSeconds == other.totalSeconds; }
    bool operator<(const Time& other) const { return totalSeconds < other.totalSeconds; }

    void print() const {
        const int h = totalSeconds / 3600;
        const int m = (totalSeconds / 60) % 60;
        const int s = totalSeconds % 60;
        std::cout << h << ':' << (m < 10 ? "0" : "") << m
                  << ':' << (s < 10 ? "0" : "") << s;
    }
};

class Playlist {
    std::vector<std::string> tracks;
public:
    Playlist(std::initializer_list<std::string> items) : tracks(items) {}
    std::string& operator[](int index) {
        if (index < 0 || index >= static_cast<int>(tracks.size()))
            throw std::out_of_range("playlist index out of range");
        return tracks[static_cast<std::size_t>(index)];
    }
    const std::string& operator[](int index) const {
        if (index < 0 || index >= static_cast<int>(tracks.size()))
            throw std::out_of_range("playlist index out of range");
        return tracks[static_cast<std::size_t>(index)];
    }
    int size() const { return static_cast<int>(tracks.size()); }
};

struct Counter {
    int v;
    Counter& operator++() { ++v; return *this; }
    Counter operator++(int) { Counter old = *this; ++v; return old; }
};

int main() {
    Time t(0, 59, 59);
    Time old = t++;
    Time afterPrefix = ++t;
    std::cout << "Postfix returned: "; old.print();
    std::cout << " | after postfix then prefix: "; afterPrefix.print(); std::cout << '\n';

    Time rollover(0, 59, 59);
    ++rollover;
    std::cout << "Rollover: "; rollover.print(); std::cout << '\n';

    Playlist playlist{"Intro", "Algorithms", "Conclusion"};
    playlist[1] = "Data Structures";
    std::cout << "Track 1: " << playlist[1] << '\n';
    const Playlist& readOnlyPlaylist = playlist;
    std::cout << "Const track 0: " << readOnlyPlaylist[0] << '\n';
    for (int invalidIndex : {-1, playlist.size()}) {
        try { std::cout << playlist[invalidIndex] << '\n'; }
        catch (const std::out_of_range& error) { std::cout << "Range check: " << error.what() << '\n'; }
    }

    // Predict-the-output program supplied in the assignment.
    Counter c{5};
    Counter a = c++;
    Counter b = ++c;
    std::cout << "Counter prediction program: " << a.v << ' ' << b.v << ' ' << c.v << '\n';

    constexpr int iterations = 10000000;
    Time prefixTimer, postfixTimer;
    auto prefixStart = std::chrono::steady_clock::now();
    for (int i = 0; i < iterations; ++i) ++prefixTimer;
    auto prefixFinish = std::chrono::steady_clock::now();
    for (int i = 0; i < iterations; ++i) postfixTimer++;
    auto postfixFinish = std::chrono::steady_clock::now();
    std::cout << "10,000,000 increments (ms): prefix="
              << std::chrono::duration_cast<std::chrono::milliseconds>(prefixFinish - prefixStart).count()
              << ", postfix="
              << std::chrono::duration_cast<std::chrono::milliseconds>(postfixFinish - prefixFinish).count()
              << '\n';
}
