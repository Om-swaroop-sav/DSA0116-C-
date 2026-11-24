#include <chrono>
#include <cstring>
#include <iostream>
#include <string>
#include <utility>

class Text {
    char* data;
    std::size_t length;
    inline static int copyCount = 0;
public:
    Text() : data(new char[1]{'\0'}), length(0) {}
    explicit Text(const char* value) : data(new char[std::strlen(value) + 1]), length(std::strlen(value)) {
        std::memcpy(data, value, length + 1);
    }
    Text(const Text& other) : data(new char[other.length + 1]), length(other.length) {
        std::memcpy(data, other.data, length + 1);
        ++copyCount;
    }
    Text& operator=(const Text& other) {
        if (this != &other) {
            char* replacement = new char[other.length + 1];
            std::memcpy(replacement, other.data, other.length + 1);
            delete[] data;
            data = replacement;
            length = other.length;
            ++copyCount;
        }
        return *this;
    }
    ~Text() { delete[] data; }

    Text& operator+=(const Text& other) {
        char* combined = new char[length + other.length + 1];
        std::memcpy(combined, data, length);
        std::memcpy(combined + length, other.data, other.length + 1);
        delete[] data;
        data = combined;
        length += other.length;
        return *this;
    }
    friend Text operator+(const Text& left, const Text& right) {
        Text result(left);
        result += right;
        return result;
    }
    bool operator==(const Text& other) const { return std::strcmp(data, other.data) == 0; }
    bool operator!=(const Text& other) const { return !(*this == other); }
    friend std::ostream& operator<<(std::ostream& output, const Text& value) {
        return output << value.data;
    }
    static int copiesMade() { return copyCount; }
};

int main() {
    Text a("Hello"), b(" "), c("World");
    Text combined = a + b + c;
    std::cout << "Concatenated: " << combined << '\n';
    std::cout << "Equality: " << std::boolalpha << (combined == Text("Hello World"))
              << " | inequality: " << (a != c) << '\n';
    a = a; // self-assignment must leave a unchanged
    Text empty;
    std::cout << "Empty message: [" << empty << "]\n";
    std::cout << "Copies observed: " << Text::copiesMade() << '\n';

    constexpr int iterations = 100000;
    Text repeated("x");
    auto customStart = std::chrono::steady_clock::now();
    for (int i = 0; i < iterations; ++i) repeated += Text("a");
    auto customEnd = std::chrono::steady_clock::now();

    std::string standard("x");
    auto standardStart = std::chrono::steady_clock::now();
    for (int i = 0; i < iterations; ++i) standard += 'a';
    auto standardEnd = std::chrono::steady_clock::now();

    std::cout << "Lengths: custom=" << iterations + 1 << ", std::string=" << standard.size() << '\n';
    std::cout << "100,000 appends (ms): custom="
              << std::chrono::duration_cast<std::chrono::milliseconds>(customEnd - customStart).count()
              << ", std::string="
              << std::chrono::duration_cast<std::chrono::milliseconds>(standardEnd - standardStart).count()
              << '\n';
}
