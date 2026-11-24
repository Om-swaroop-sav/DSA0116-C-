$ErrorActionPreference = "Stop"
$root = Split-Path -Parent $MyInvocation.MyCommand.Path
$build = Join-Path $root "build"
New-Item -ItemType Directory -Force -Path $build | Out-Null
$tasks = Get-ChildItem -Path $root -Directory | Where-Object { $_.Name -match '^Task[0-9]{2}$' } | Sort-Object Name
$failed = @()
foreach ($task in $tasks) {
  foreach ($src in Get-ChildItem -Path $task.FullName -Filter '*.cpp') {
    $exe = Join-Path $build ($task.Name + '.exe')
    Write-Host "Compiling $($task.Name)\$($src.Name)" -ForegroundColor Cyan
    & g++ -std=c++17 -Wall -Wextra $src.FullName -o $exe
    if ($LASTEXITCODE -ne 0) { $failed += $src.Name }
  }
}
if ($failed.Count -eq 0) { Write-Host "All task programs compiled successfully." -ForegroundColor Green }
else { Write-Host "Failed: $($failed -join ', ')" -ForegroundColor Red; exit 1 }
