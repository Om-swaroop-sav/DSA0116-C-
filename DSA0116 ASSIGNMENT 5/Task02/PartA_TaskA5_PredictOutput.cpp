#include <iostream>
#include <string>

struct Guard {
    std::string name;
    explicit Guard(const std::string& value) : name(value) {}
    ~Guard() { std::cout << '~' << name << ' '; }
};

void f() {
    Guard local("f");
    throw 42;
}

int main() {
    try {
        Guard mainGuard("main");
        f();
        std::cout << "not printed ";
    } catch (int value) {
        std::cout << "caught " << value;
    } catch (...) {
        std::cout << "other";
    }
    std::cout << '\n';
}
