# Assignment 5 – CO5: Reliable Software with Runtime Polymorphism and Exceptions

Student: Om Swaroop Pannuru
Register Number: [enter register number]
Compiler: GCC / g++ (C++17)
Compile flags: `-std=c++17 -Wall -Wextra`

## Folder layout
- `PartA_Design_Notes.md`: the supplied A1–A5 hierarchy, vtable, exception and recovery design notes.
- `HospitalBilling.hpp`: shared billing and payer interfaces used by Part B programs. A copy is present in each dependent task folder for standalone compilation.
- `Task01`: A2 runtime-binding prediction program and screenshot.
- `Task02`: A5 stack-unwinding prediction program and screenshot.
- `Task03`: B1 completed TODO program and complete polymorphic billing program, with two screenshots.
- `Task04`: B2 completed TODO program and exception/error-condition experiment, with two screenshots.
- `Task05`: B3 performance comparison program and screenshot.
- `Task06`: B4 final extension program and screenshot.
- `build`: executables generated when compiling in this environment.

## Compile and run
From a task folder, compile using:

```powershell
g++ -std=c++17 -Wall -Wextra <source.cpp> -o program.exe
.\program.exe
```

For programs that include `HospitalBilling.hpp`, keep the header in the same folder. See the `*_Compile.txt` and `*_Execution.txt` files for per-program logs.

## Important submission note
The supplied assignment PDF requires Part A design artifacts (UML/vtable diagrams, exception hierarchy, pseudocode, design reasoning and complexity analysis) as well as Part B implementation, timings and sanitizer evidence. `PartA_Design_Notes.md` contains the design notes supplied with the code. The screenshots are the supplied VS Code captures. Actual performance timings are machine-dependent; use the values from your own compiler/system in the final written analysis. Add your register number and GitHub URL before submission.
