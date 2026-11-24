#include <iostream>
#include <vector>

int& highestMark(int marks[], int count) {
    int highestIndex = 0;
    for (int i = 1; i < count; ++i) {
        if (marks[i] > marks[highestIndex]) highestIndex = i;
    }
    return marks[highestIndex];
}

const int& highestMarkReadOnly(const int marks[], int count) {
    int highestIndex = 0;
    for (int i = 1; i < count; ++i) {
        if (marks[i] > marks[highestIndex]) highestIndex = i;
    }
    return marks[highestIndex];
}

int highestMarkCopy(const int marks[], int count) {
    int highestIndex = 0;
    for (int i = 1; i < count; ++i) {
        if (marks[i] > marks[highestIndex]) highestIndex = i;
    }
    return marks[highestIndex];
}

// Deliberately unsafe example for study only; never call this function.
// Returning a reference to a local variable creates a dangling reference.
#if 0
int& danglingReference() {
    int localValue = 42;
    return localValue; // compiler warning; using the result is undefined behaviour
}
#endif

int main() {
    int marks[] = {78, 91, 85, 97, 88};
    const int count = static_cast<int>(sizeof(marks) / sizeof(marks[0]));

    std::cout << "Original highest mark: " << highestMarkReadOnly(marks, count) << '\n';
    highestMark(marks, count) += 2;
    std::cout << "After moderation (+2): " << highestMarkCopy(marks, count) << '\n';

    const int& readOnlyHighest = highestMarkReadOnly(marks, count);
    int copiedHighest = highestMarkCopy(marks, count);
    std::cout << "Const reference: " << readOnlyHighest
              << ", returned copy: " << copiedHighest << '\n';

    // An index remains useful after vector reallocation; a reference/pointer may not.
    std::vector<int> registerMarks = {70, 82, 96, 91};
    int highestIndex = 0;
    for (int i = 1; i < static_cast<int>(registerMarks.size()); ++i) {
        if (registerMarks[i] > registerMarks[highestIndex]) highestIndex = i;
    }
    std::cout << "Highest mark by index: " << registerMarks[highestIndex] << '\n';
    registerMarks.push_back(99); // use the index again after possible reallocation
    std::cout << "After vector growth, indexed value: " << registerMarks[highestIndex] << '\n';
}
