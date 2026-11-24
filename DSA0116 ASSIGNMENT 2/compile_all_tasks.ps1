$ErrorActionPreference = "Stop"
$root = $PSScriptRoot
$tasks = Get-ChildItem -Path $root -Directory -Filter "Task??" | Sort-Object Name

foreach ($task in $tasks) {
    $source = Get-ChildItem -Path $task.FullName -Filter "*.cpp" | Select-Object -First 1
    if (-not $source) { throw "No C++ source file found in $($task.Name)" }

    $exe = Join-Path $task.FullName ($task.Name + ".exe")
    $log = Join-Path $task.FullName ($task.Name + "_Run_Output.txt")

    Write-Host "`n[$($task.Name)] Compiling $($source.Name)" -ForegroundColor Cyan
    & g++ -std=c++17 -Wall -Wextra $source.FullName -o $exe
    if ($LASTEXITCODE -ne 0) { throw "Compilation failed for $($task.Name)" }

    Write-Host "[$($task.Name)] Running program" -ForegroundColor Green
    & $exe 2>&1 | Tee-Object -FilePath $log
    if ($LASTEXITCODE -ne 0) { Write-Warning "$($task.Name) returned exit code $LASTEXITCODE" }
    Write-Host "Saved output to $log" -ForegroundColor DarkGreen
}
Write-Host "`nAll seven assignment programs have been compiled and executed." -ForegroundColor Green
