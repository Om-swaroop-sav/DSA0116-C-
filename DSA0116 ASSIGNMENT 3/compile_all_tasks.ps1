$ErrorActionPreference = "Stop"
$tasks = @(
  @{Folder="Task01"; Source="Task01_Q1_ConstructorsBook.cpp"; Exe="Task01.exe"},
  @{Folder="Task02"; Source="Task02_Q2_PrescriptionDeepCopy.cpp"; Exe="Task02.exe"},
  @{Folder="Task03"; Source="Task03_Q3_DynamicSeatMap.cpp"; Exe="Task03.exe"},
  @{Folder="Task04"; Source="Task04_Q4_MoneyOperatorOverloading.cpp"; Exe="Task04.exe"},
  @{Folder="Task05"; Source="Task05_Q5_TimeAndPlaylist.cpp"; Exe="Task05.exe"},
  @{Folder="Task06"; Source="Task06_Q6_TextRuleOfThree.cpp"; Exe="Task06.exe"},
  @{Folder="Task07"; Source="Task07_Q7_ComplexImpedance.cpp"; Exe="Task07.exe"}
)
foreach ($task in $tasks) {
  Write-Host "Compiling $($task.Folder)\$($task.Source)" -ForegroundColor Cyan
  Push-Location $task.Folder
  & g++ -std=c++17 -Wall -Wextra $task.Source -o $task.Exe
  if ($LASTEXITCODE -ne 0) { Pop-Location; throw "Compilation failed: $($task.Folder)" }
  Pop-Location
}
Write-Host "All 7 Assignment 3 programs compiled successfully." -ForegroundColor Green
