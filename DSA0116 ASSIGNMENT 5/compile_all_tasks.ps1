$ErrorActionPreference = "Stop"
$root = Split-Path -Parent $MyInvocation.MyCommand.Path
$build = Join-Path $root "build"
New-Item -ItemType Directory -Force -Path $build | Out-Null
$folders = @("Task01","Task02","Task03","Task04","Task05","Task06")
$failed = @()
foreach ($folder in $folders) {
  $path = Join-Path $root $folder
  foreach ($src in Get-ChildItem -Path $path -Filter '*.cpp') {
    $exe = Join-Path $build ($folder + '_' + $src.BaseName + '.exe')
    Write-Host "Compiling $folder\$($src.Name)" -ForegroundColor Cyan
    & g++ -std=c++17 -Wall -Wextra $src.FullName -o $exe
    if ($LASTEXITCODE -ne 0) { $failed += "$folder\$($src.Name)" }
  }
}
if ($failed.Count -eq 0) { Write-Host "All Assignment 5 programs compiled successfully." -ForegroundColor Green }
else { Write-Host "Failed: $($failed -join ', ')" -ForegroundColor Red; exit 1 }
