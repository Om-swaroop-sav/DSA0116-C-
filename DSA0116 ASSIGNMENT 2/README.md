# Assignment 2 - CO2 (C++)

This submission follows the assignment requirement to keep one folder for each task. Each task folder contains the C++ source file, the matching execution screenshot renamed by task number, and a text output log.

## Folder structure

- `Assignment2_CO2_Report.docx` - Word report with the source code first and the matching execution screenshot after each task.
- `Task01/` through `Task07/` - one folder per question, each containing its `.cpp` source, `TaskXX_Output.png`, and `TaskXX_Execution.txt`.
- `TASK_SCREENSHOT_MAPPING.txt` - confirms which screenshot belongs to each task.
- `compile_all_tasks.ps1` - Windows PowerShell script to compile and execute all seven tasks.

## Compiler and run instructions

The Windows environment shown in the supplied VS Code screenshots uses MSYS2 GCC 16.2.0. The source files use C++17.

To compile and run one task from PowerShell at this folder's root, for example Task 1:

```powershell
g++ -std=c++17 -Wall -Wextra .\Task01\Task01_Q1_CallByValueReferencePointer.cpp -o .\Task01\Task01.exe
.\Task01\Task01.exe
```

To compile and execute all seven tasks in order, run:

```powershell
Set-ExecutionPolicy -Scope Process Bypass
.\compile_all_tasks.ps1
```

## Validation

All seven submitted source files were compiled and executed during package preparation using GCC 14.2.0 with `-std=c++17 -Wall -Wextra`. The included text logs show the corresponding program output. Runtime measurements may vary by machine and compiler settings. GCC 16.2.0 on Windows may warn that the by-value parameter `a` in Task 1 is set but not otherwise used; this is intentional for demonstrating that a by-value parameter changes only its local copy.

## Student details

Name: Om Swaroop Pannuru

Register Number: ____________________

GitHub Repository Link: ____________________
