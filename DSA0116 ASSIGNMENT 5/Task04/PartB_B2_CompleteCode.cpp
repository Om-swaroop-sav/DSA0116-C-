#include <iostream>
#include <stdexcept>

class ClaimError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

double approve(double billed, double cover) {
    if (billed < 0 || cover < 0) throw std::invalid_argument("negative amount");
    if (billed > cover) throw ClaimError("exceeds cover");
    return billed;
}

double settle(double billed, double cover) {
    try {
        return approve(billed, cover);
    } catch (const ClaimError& error) {
        std::cout << "audit: " << error.what() << '\n';
        throw; // rethrows the same ClaimError object
    }
}

int main() {
    double cases[][2] = {{40000, 50000}, {60000, 50000}, {-1, 50000}};
    for (auto& testCase : cases) {
        try {
            const double paid = settle(testCase[0], testCase[1]);
            std::cout << "approved " << paid << '\n';
        } catch (const ClaimError& error) {
            std::cout << "claim rejected: " << error.what() << '\n';
        } catch (const std::exception& error) {
            std::cout << "error: " << error.what() << '\n';
        }
    }
}
